#include "mydb.h"
extern const char *OutPutFileName;

Mydb::Mydb() : res(nullptr){
    //初始化 并 连接数据库
    mysql_init(&connection_);
    if ( !mysql_real_connect(&connection_, "localhost", "lbt", "5656", "tetris", 3306, 0, CLIENT_FOUND_ROWS) ){
        Logger logger(OutPutFileName);
        logger << "     Database connect error!!!\n";
        logger << "     " << mysql_error(&connection_) << "\n\n";
        assert(false);
    }
    query("set names utf8"); //设置字符集
};

Mydb::~Mydb(){
    mysql_close(&connection_);
};

//一般查询
void Mydb::query(const char *que){
    if ( mysql_query(&connection_, que) ){
        assert(false);
    }
}

//插入数据
void Mydb::insert(const DataType &data){
    char que[80];
    snprintf(que, sizeof(que), "INSERT INTO score_list(username,score) VALUES(\"%s\", %d)", data.name, data.score);
    query(que);
}

//更新数据
void Mydb::update(const DataType &data){
    char que[80];
    snprintf(que, sizeof(que), "UPDATE score_list SET score=%d WHERE username='%s'", data.score, data.name);
    query(que);
}

//是否存在某人
bool Mydb::exist(const char *table, const char *name){
    char que[80];
    snprintf(que, sizeof(que), "SELECT * FROM %s WHERE username='%s'", table, name);
    query(que);
    if( (res = mysql_use_result(&connection_)) == nullptr)
        assert(false);

    row = mysql_fetch_row(res);

    bool ret = false;
    if (row > 0)
        ret = true;
    
    mysql_free_result(res);
    res = nullptr;
    return ret;
}

//获取一行数据
MYSQL_ROW Mydb::fetch_row(const char* que){
    if (res == nullptr){
        query(que);
        if ( (res = mysql_use_result(&connection_)) == nullptr){
            assert(false);
        }
        return fetch_row();
    }
    else{
        row = mysql_fetch_row(res);
        if (row){
            return row;
        }
        else{
            mysql_free_result(res);
            res = nullptr;
            return nullptr;
        }
    }
}