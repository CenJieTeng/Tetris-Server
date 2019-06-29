Server:mydb.o Server.o message.pb.o
	g++ -L=/usr/lib64/mysql -std=c++11 mydb.o Server.o message.pb.o -o Server -lboost_system -lprotobuf -lpthread -lmysqlclient -g

message.pb.o:message.pb.cc message.pb.h
	g++ -c -I/usr/local/include -std=c++11 message.pb.cc -o message.pb.o -g

Server.o:Server.cpp message.h  message.pb.h logger.h mydb.h
	g++ -c -std=c++11 Server.cpp -o Server.o -g

mydb.o:mydb.cpp mydb.h logger.h
	g++ -c -std=c++11 mydb.cpp -o mydb.o -g

clean:
	rm -rf Server mydb.o Server.o message.pb.o
