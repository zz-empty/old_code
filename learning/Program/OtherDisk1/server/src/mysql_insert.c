#include "../include/head.h"
#include "../include/mysql_func.h"

int mysql_insert(char *query)
{
	MYSQL *conn;
	char *server = "localhost";
	char *user = "root";
	char *password = "1234567890";
	char *database = "network_disk";//要访问的数据库名称
	
    int queryResult;
	conn = mysql_init(NULL);

	if(!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0))
	{
		printf("Error connecting to database: %s\n", mysql_error(conn));
	}
    else
    {
		printf("Connected...\n");
	}

	queryResult = mysql_query(conn, query);
	if(queryResult)
	{
		printf("Error making query:%s\n", mysql_error(conn));
	}
    else
    {
		printf("insert success\n");
	}
	mysql_close(conn);

	return 0;
}
