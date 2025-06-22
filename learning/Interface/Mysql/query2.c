#include <mysql/mysql.h>
#include <stdio.h>

int main(int argc, char * argv[])
{
    if(2 != argc) {
        printf("args error\n");
        return -1;
    }

    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    char host[] = "localhost";
    char user[] = "zzz";
    char passwd[] = "1111";
    char database[] = "Test";

    char query_tmp[200] = "select * from staff where name like '";
    char query[300] = "";
    sprintf(query, "%s%s%s", query_tmp, argv[1], "'");

    printf("%s\n", query);

    //初始化MYSQL
    conn = mysql_init(NULL);
    if(!conn) {
        printf("MYSQL init fail\n");
        return -1;
    }

    //连接数据库
    if(!mysql_real_connect(conn, host, user, passwd, database, 0, NULL, 0)) {
        printf("Error connecting to database: %s\n", mysql_error(conn));
        return -1;
    }
    else {
        printf("MySQL connected...\n");
    }

    //查询
    int queryRet = mysql_query(conn, query);
    if(queryRet) {
        printf("Error query: %s\n", mysql_error(conn));
        return -1;
    }
    else {
        res = mysql_store_result(conn);
        /* printf("mysql_affacted_rows: %lu\n", (unsigned long)mysql_affected_rows(conn)); */
        printf("mysql_num_rows: %lu\n", (unsigned long)mysql_num_rows(res));

        row = mysql_fetch_row(res);
        if(NULL == row) {
            printf("Don't query any data\n");
        }
        else {
            for(queryRet = 0; queryRet != (int)mysql_num_fields(res); ++queryRet) {
                printf("%13s ", row[queryRet]);
            }
            printf("\n");

            /* while(NULL != (row = mysql_fetch_row(res))) { */
            /*     for(queryRet = 0; queryRet != (int)mysql_num_fields(res); ++queryRet) { */
            /*         printf("%8s ", row[queryRet]); */
            /*     } */
            /*     printf("\n"); */
            /* } */
        }

        mysql_free_result(res);
    }

    mysql_close(conn);
    return 0;
}

