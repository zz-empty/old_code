#include "head.h"

int mysql_insert(char *query)
{
	MYSQL *conn;
	const char *server = "localhost";
	const char *user = "zzz";
	const char *password = "1111";
	const char *database = "Netdisk";//要访问的数据库名称
    int ret = -1;
	
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
        ret = 0;
	}
	mysql_close(conn);

	return ret;
}
