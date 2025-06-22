#include <mysql/mysql.h>
#include <string.h>
#include <stdio.h>

int main(int argc,char* argv[])
{
    MYSQL *conn;

    char server[] = "localhost";
    char user[] = "zzz";
    char password[] = "1111";
    char database[] = "Test";

    char query[200] = "delete from equipment where name='tiejian'";
    int queryRet;

    //初始化MYSQL
    conn = mysql_init(NULL);

    //连接数据库
    if(!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        printf("Error connecting to database: %s\n", mysql_error(conn));
    }
    else {
        printf("MYSQL Connected...\n");
    }

    //输入SQL语句
    queryRet = mysql_query(conn, query);
    if(queryRet) {
        printf("Error making query:%s\n",mysql_error(conn));
    }
    else {
        unsigned long ret = mysql_affected_rows(conn);
        if(ret) {
            printf("delete success, delete row=%lu\n", ret);
        }
        else {
            printf("delete failed, mysql_affected_rows: %lu\n", ret);
        }
    }

    mysql_close(conn);

    return 0;
}
