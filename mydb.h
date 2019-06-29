#ifndef MYDB_H
#define MYDB_H
#include <cassert>
#include <string>
#include <memory>
#include <mysql/mysql.h>
#include "logger.h"

class Mydb{
public:
    Mydb();
    ~Mydb();

    struct DataType{
        const char *name;
        int score;
    };

public:
    //一般查询
    void query(const char *que);

    //插入数据
    void insert(const DataType &data);

    //更新数据
    void update(const DataType &data);

    //是否存在某人
    bool exist(const char *table, const char *name);

    //获取一行数据
    MYSQL_ROW fetch_row(const char* que = "SELECT * FROM score_list");

private:
    MYSQL connection_;
    MYSQL_RES *res;
    MYSQL_ROW row;
};

#endif