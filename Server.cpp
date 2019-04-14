#include <cstdlib>
#include <iostream>
#include <string>
#include <deque>
#include <set>
#include <map>
#include <thread>
#include <boost/asio.hpp>
#include "message.h"
#include "message.pb.h"
#include "Logger.h"

const int MaxRoomSize = 4;
const char *OutPutFileName = "./Server.log";

using boost::asio::ip::tcp;

class session;
class room;
class server;

using session_ptr		= std::shared_ptr<session>; //客户端的智能指针
using session_set		= std::set<session_ptr>; //客户端实例集
using room_ptr				= std::shared_ptr<room>; //room的智能指针
using room_map			= std::map<int32_t, room_ptr>; //room实例集
using msg_deque			= std::deque<message>; //消息队列

//房间类，用于管理客户端的联系
class room : public std::enable_shared_from_this<room> {
public:
	static std::set<int32_t> roomId_set_; //房间号集合，用于防止房间号冲突

	room(int32_t id) 
		: roomId_(id),
		status_(true){

		auto ret_pair = roomId_set_.insert(id); //记录该房间号

		//房间号冲突,重新分配
		//例外 0 ，大厅不冲突
		while (!ret_pair.second) {
			ret_pair = roomId_set_.insert(std::rand() % 100 + 1); //随机分配房间号
		}
	}

	bool operator<(const room &r)const {
		return this->roomId_ < r.roomId_;
	}

	bool operator==(const room &r)const {
		return this->roomId_ == r.roomId_;
	}

	//客户端加入room
	void join(session_ptr sp) {
		session_set_.insert(sp);
	}

	//客户端离开room
	void leave(session_ptr sp) {
		session_set_.erase(sp);
	}

	//广播消息
	template <typename T>
	void deliver(session_ptr onlySend, session_ptr noSend, MessageType messageType, const T &msg) const;

	//返回房间人数
	size_t session_num() {
		return session_set_.size();
	}
	
	//返回房间Id
	int32_t id() const {
		return roomId_;
	}
	
	//返回客户端集合
	const session_set& sessions(){
		return session_set_;
	}
	
	//~
	void id(int32_t id)  {
		roomId_ = id;
	}
	
	//返回房间状态
	bool status () const {
		return status_;
	}

	//~
	void set_status(bool status) {
		status_ = status;
	}

private:
    	int32_t roomId_; //房间ID
	bool status_;    //房间当前状态 空闲true  已开始 false
	session_set session_set_;	//客户端集合
};

std::set<int32_t> room::roomId_set_; //房间号集合，用于防止房间号冲突

//客户端类，用于实例化客户端
class session : public std::enable_shared_from_this<session> {
public:
	session (boost::asio::io_service &io_service) 
		: socket_(io_service),
		roomId(0){
	}

	void start() {
		do_read_header();
	}

	tcp::socket& socket() {
		return socket_;
	}

	//把消息存放到消息队列
	template <typename T>
	void deliver(const MessageType &messageType, const T& msg) {
		message sendMsg;
		std::string serializeMsg;
		msg.SerializeToString(&serializeMsg);
		sendMsg.setMessage(messageType, serializeMsg);

		deliver(sendMsg);
	}


	//把消息存放到消息队列
	void deliver(const message &msg) {
		bool isWriteing = !write_msg_deque_.empty(); //正在发送消息...
		write_msg_deque_.push_back(msg);

		//如果不是在发送消息,就do_write
		if (!isWriteing)
			do_write();
	}

private:
	//读取信息包头
	void do_read_header() {
		auto self = shared_from_this();
		boost::asio::async_read(
			socket_, 
			boost::asio::buffer(read_msg_.data(), message::headerLength()),
			[self, this] (const boost::system::error_code &error, size_t /* length */ ) {
				if (!error) {
					read_msg_.decode(); //解析头部
					do_read_body();
				}
				else{
					Logger logger(OutPutFileName);
					logger << "	客户端(" << this <<  ")离开\n"
						<< "	" << error.value() << error.message() << "\n\n";
					leave_room(); //客户端断开时应该退出房间
				}
			});
	}

	//读取消息包内容
	void do_read_body() {
		auto self = shared_from_this();
		boost::asio::async_read(
			socket_, 
			boost::asio::buffer(read_msg_.body(), read_msg_.bodyLength()), 
			[self, this] (const boost::system::error_code &error, size_t /* length */) {
				if (!error) {
					handle_message(); //处理收到的消息

					do_read_header(); //继续监听消息的到来
				}
				else {
					Logger logger(OutPutFileName);
					logger.log("	读取数据包内容错误:");
					logger << "	" << error.value() << error.message() << "\n\n"; 
				}
			});
	}

	//处理收到的消息
	void handle_message() {
		switch (read_msg_.type())
		{
		case SERVER_MSG: //服务器相关信息
			dispose_server();
			break;
		case GAME_MSG: //游戏相关信息
			dispose_game();
			break;
		default:
			assert(false);
		}
	}

	//反序列化消息
	template<typename T>
	bool ParseMessage(T &msg){
		bool ok = msg.ParseFromString(
			std::string(
				read_msg_.body(),
				read_msg_.bodyLength()));

		return ok;
	}

	//创建新的room,并加入其中
	void create_room();

	//加入的某个房间
	void join_room(int32_t);

	//游戏开始
	void game_start();

	//离开房间
	void leave_room();

	//处理服务器相关处理
	void dispose_server();

	//处理游戏相关处理
	void dispose_game();

	//向客户端发送消息
	void do_write() {
		boost::asio::async_write(
			socket_,
			boost::asio::buffer(
				write_msg_deque_.front().data(), write_msg_deque_.front().length()),
			[this] (const boost::system::error_code &error, size_t /*length*/) {
				if (!error && write_msg_deque_.front().chack_header()) { //消息发送前应该检查...
					write_msg_deque_.pop_front(); //删除发送出去的消息
					if (!write_msg_deque_.empty()) {
						do_write(); //继续发送
					}
				}
				else {
					Logger logger(OutPutFileName);
					logger << "	发送消息错误:\n"
						<< "	" <<  error.value() << error.message() << "\n\n";
				}
			});
	}

	tcp::socket socket_;
	int32_t roomId; //当前所在房间的id
	message read_msg_; //读取存放空间
	msg_deque write_msg_deque_; //发送消息队列
};

template <typename T>
void room::deliver(session_ptr onlySend, session_ptr noSend, MessageType messageType, const T &msg) const {
	//要发送的消息
	message sendMsg;
	std::string serializeMsg;
	msg.SerializeToString(&serializeMsg);
	sendMsg.setMessage(messageType, serializeMsg); //设置消息类型

	//只发给某人
	if (onlySend) {
		onlySend->deliver(sendMsg);
	}
	else{
		for (const auto& v : session_set_) {
			//不广播给某人
			if (v != noSend) {
				v->deliver(sendMsg);
			}
		}
	}
	
}

//服务器类，用于接收客户端连接请求
class server {
public:
	static room_map room_map_;    //room集合
	static room hall_;		      //大厅
	static room_ptr& ROOM(int32_t id);          //返回特定id的房间

	server(boost::asio::io_service &io_service, tcp::endpoint endpoint) 
		: io_service_(io_service),
		acceptor_(io_service, endpoint){
	}

	//启动服务器
	void start() {
		room_map_[0] = static_cast<room_ptr>(&hall_); //添加大厅
		do_accept();
	}

	//返回在线人数
	static int32_t onLineSessionNum(){
		int32_t total = 0;
		for (const auto &pair : room_map_)
			total += pair.second->session_num();

		return total;
	}
private:
	//接收客户端的连接
	void do_accept() {
		//创建新的客户端实例
		session_ptr new_session = session_ptr(new session(io_service_));

		acceptor_.async_accept(
			new_session->socket(),
			[this, new_session] (const boost::system::error_code &error) {
				Logger logger(OutPutFileName);
				if (!error) {
					//hall_.join(new_session); //加入 大厅hall_
					 logger << "	客户端(" << new_session.get() 
						<< ")连接到服务器" << "\n\n";
					new_session->start();  //session开始接收消息
				}
				else {
					logger << "	创建连接错误:\n"
						<< "	" << error.value() << error.message() << "\n\n";
				}

				do_accept(); //继续接收连接
			});
	}

	boost::asio::io_service &io_service_;
	tcp::acceptor acceptor_;	  //用于接收客户端连接
};

room_map server::room_map_;    //room集合
room server::hall_(0); //大厅，房间号0

//返回特定id的房间
room_ptr& server::ROOM(int32_t id){
	auto iter = room_map_.find(id); //寻找房间
	assert(iter != room_map_.end());

	return iter->second;
}

void session::dispose_server() {

	ServerMsg serverMsg;
	if (!ParseMessage(serverMsg)) {
		Logger logger(OutPutFileName);
		logger << "serverMsg:消息解析失败" << "\n\n";
		return;
	}

	switch (serverMsg.msgtype()) {
	case CREATE_SERVER_MSG:  //创建room
	{
		create_room(); //创建房间

		//通知房间的客户端，更新房间信息
		ServerMsg serverMsg;
		serverMsg.set_msgtype(ServerMessageType::RENOVATE_ROOM_INFO_MSG);
		server::ROOM(roomId)->deliver(nullptr, nullptr, MessageType::SERVER_MSG, serverMsg);
	}
	break;
	case JOIN_SERVER_MSG:	 //加入room
		join_room(serverMsg.serverid());
		break;
	case LEAVE_SERVER_MSG:	 //离开room
		if  (roomId != 0) //在大厅不退出
			leave_room();
		break;
	case GET_ROOM_LIST_MSG: //获取房间信息列表
		{
			for (const auto &v : room::roomId_set_)
			{
				serverMsg.add_roomlist(v);
				serverMsg.add_roompeoplenum(server::ROOM(v)->session_num());
				serverMsg.add_roomstatus(server::ROOM(v)->status());
			}

			server::ROOM(roomId)->deliver(shared_from_this(), nullptr, MessageType::SERVER_MSG, serverMsg);
		}
		break;
	}
}

//游戏相关处理
void session::dispose_game() {

	GameMsg gameMsg;
	if (!ParseMessage(gameMsg)) {
		Logger logger(OutPutFileName);
		 logger << "gameMsg:消息解析失败" << "\n\n";
		return;
	}

	switch (gameMsg.msgtype())
	{
	case GAME_START_MSG:
	{
		game_start(); //游戏开始
	}
	break;
	case ATK_FOE_MSG:	//攻击对手
	{
		server::ROOM(roomId)->deliver(nullptr, shared_from_this(), MessageType::GAME_MSG, gameMsg);
	}
	break;
	case GAME_OVER_MSG: //游戏结束
	{
		//如果房间只剩两个人，宣布获胜
		if (server::ROOM(roomId)->session_num() == 2) {
			server::ROOM(roomId)->deliver(nullptr, shared_from_this(), MessageType::GAME_MSG, gameMsg);
		}

		leave_room();	//离开房间
	}
	break;
	case CHAT_MSG: //聊天消息
	{
		std::string::size_type n = gameMsg.chat().find(":");

		//命令类消息
		if (n != std::string::npos){
			//获取命令
			std::string  command = gameMsg.chat().substr(0, n);

			if (command == "verify"){
				//验证客户端
				if (gameMsg.chat().substr(n + 1) == "123"){
					server::hall_.join(shared_from_this()); //加入大厅
				}
			}
			if (command == "chat"){
				server::ROOM(roomId)->deliver(nullptr,  nullptr,  GAME_MSG, gameMsg);
			}
		}
	}
	break;
	}
	
}

//创建房间room
void session::create_room() {
	server::hall_.leave(shared_from_this()); //从大厅离开

	room_ptr tmp = std::make_shared<room>(room(std::rand() % 100 + 1)); //创建房间
	roomId = tmp->id(); //设置id
	server::room_map_[roomId] = tmp; //把该房间并入room_map_
	
	tmp->join(shared_from_this()); //加入该房间

	//向客户端通知，新创建的房间的房间号
	ServerMsg serverMsg;
	serverMsg.set_msgtype(ServerMessageType::CREATE_SERVER_MSG);
	serverMsg.set_serverid(roomId);
	server::ROOM(roomId)->deliver(shared_from_this(), nullptr, MessageType::SERVER_MSG, serverMsg);
}

//加入房间
void session::join_room(int32_t Id) {

	server::hall_.leave(shared_from_this()); //从大厅离开

	auto iter = server::room_map_.find(Id); //寻找房间
	//提示客户端没有该房间 或 房间人数已满 或 房间已经开始游戏
	if (iter == server::room_map_.end() 
		|| server::ROOM(Id)->session_num() == MaxRoomSize 
		|| server::ROOM(Id)->status() == false)
	{
		ServerMsg serverMsg;
		serverMsg.set_msgtype(ServerMessageType::JOIN_SERVER_MSG);
		deliver(MessageType::SERVER_MSG, serverMsg);
	}
	else{
		(*iter).second->join(shared_from_this()); //加入房间
		roomId = Id; //修改当前所在房间号

		//通知房间的客户端，更新房间信息
		ServerMsg serverMsg;
		serverMsg.set_msgtype(ServerMessageType::RENOVATE_ROOM_INFO_MSG);
		server::ROOM(roomId)->deliver(nullptr, nullptr, MessageType::SERVER_MSG, serverMsg);
	}
}

//开始游戏
void session::game_start() {
	//如果房间有n多人开始游戏
	if (server::ROOM(roomId)->session_num() >= 2) {
		Logger logger(OutPutFileName);
		for (const auto &who : server::ROOM(roomId)->sessions()){
			logger << who << " ";
		};
		logger << "一起玩游戏\n\n"; 		

		GameMsg gameMsg;
		gameMsg.set_msgtype(GameMessageType::GAME_START_MSG);

		server::ROOM(roomId)->set_status(false);
		server::ROOM(roomId)->deliver(nullptr, nullptr, MessageType::GAME_MSG, gameMsg);
	}
}

//离开房间
void session::leave_room() {
	//通知房间的客户端，更新房间信息
	ServerMsg serverMsg;
	serverMsg.set_msgtype(ServerMessageType::RENOVATE_ROOM_INFO_MSG);
	server::ROOM(roomId)->deliver(nullptr, nullptr, MessageType::SERVER_MSG, serverMsg);

	server::ROOM(roomId)->leave(shared_from_this());

	//如果不是在大厅中
	if (roomId != 0) {
		//如果房间人数等于 0 关闭房间
		if (server::ROOM(roomId)->session_num() == 0) {
			auto iter = server::room_map_.find(roomId); //获取要关闭的房间
			assert(iter != server::room_map_.end()); //获取不到，炸掉
			server::room_map_.erase(iter); //关闭房间

			//更新房间号集合
			room::roomId_set_.erase(roomId);
		}

		//返回大厅
		roomId = 0;
		server::hall_.join(shared_from_this());
	}
}

int main() {

	std::thread thread_log([](){
				for (;;){
					std::this_thread::sleep_for(std::chrono::minutes(10));

					Logger logger(OutPutFileName);
					logger << "在线人数:" << server::onLineSessionNum() << "\n\n"; 	
				}
			});

	try
	{       
		boost::asio::io_service io_service;
		server server_(io_service, tcp::endpoint(tcp::v4(), 9999));
		server_.start();

		io_service.run();  
		thread_log.join();	
	}
	catch (const std::exception &e)
	{
		Logger logger(OutPutFileName);
		logger << e.what() << "\n\n";
		thread_log.join();
	}
	
	return 0;
}
