#include <mysql/mysql.h>
#include <stdio.h>
#include <string.h>

int main(int argc,char* argv[])
{
    //输入：./update hero表中要更新的名字 哪个id
	if (argc != 3) {
		printf("error args\n");
		return -1;
	}

	MYSQL *conn;
	/* MYSQL_RES *res; */
	/* MYSQL_ROW row; */

	char server[] = "localhost";
	char user[] = "zzz";
	char password[] = "1111";
	char database[] = "Test";

	char query_tmp[200] = "update hero set name ='"; 
    char query[300] = "";
	sprintf(query, "%s%s%s%s", query_tmp, argv[1],"' where id =", argv[2]);
	int queryResult;

    //显式更新语句
	puts(query);

    //初始化MYSQL
	conn=mysql_init(NULL);

    //连接数据库
	if(!mysql_real_connect(conn,server,user,password,database,0,NULL,0)) {
		printf("Error connecting to database:%s\n",mysql_error(conn));
	}
    else {
		printf("Connected...\n");
	}

    //输入SQL语句
	queryResult = mysql_query(conn, query);
	if(queryResult) {
		printf("Error making query:%s\n",mysql_error(conn));
	}
    else {
        int ret = mysql_affected_rows(conn);
        if(ret) {
            printf("update success\n");
        }
        else {
            printf("update fail, mysql_affected_rows:%d\n", ret);
        }
	}

	mysql_close(conn);
	return 0;
}
