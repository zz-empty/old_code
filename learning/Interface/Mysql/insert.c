#include <mysql/mysql.h>
#include <string.h>
#include <stdio.h>

int main(int argc,char* argv[])
{
	MYSQL *conn;
	char server[] = "localhost";
	char user[] = "zzz";
	char password[] = "1111";
	char database[] = "Test";//要访问的数据库名称

    char query[200]="insert into hero (id, name, age) values (17, 'daji', 16)";
	int queryResult;

    //初始化MYSQL
	conn = mysql_init(NULL);

	if(!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
		printf("Error connecting to database: %s\n", mysql_error(conn));
	}
    else {
		printf("MYSQL Connected...\n");
	}

    //输入SQL语句
	queryResult = mysql_query(conn, query);
	if(queryResult) {
		printf("Error making query:%s\n", mysql_error(conn));
	}
    else {
		printf("insert success\n");
	}

	mysql_close(conn);
	return 0;
}

