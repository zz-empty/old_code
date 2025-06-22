#include "../include/head.h"

int mysql_delete(char *query)
{
	MYSQL *conn;

	char *server="localhost";
	char *user="root";
	char *password="密码";
	char *database="network_disk";
	int queryRet;

	conn = mysql_init(NULL);

	if(!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0))
	{
		printf("Error connecting to database: %s\n", mysql_error(conn));
	}
    else
    {
		printf("Connected...\n");
	}

	queryRet = mysql_query(conn, query);
	if(queryRet)
	{
		printf("Error making query:%s\n",mysql_error(conn));
	}
    else
    {
        unsigned long ret = mysql_affected_rows(conn);
        if(ret)
        {
            printf("delete success, delete row=%lu\n", ret);
        }
        else
        {
            printf("delete failed,mysql_affected_rows: %lu\n", ret);
        }
	}

	mysql_close(conn);

	return 0;
}
