#include "../include/head.h"

int mysql_query1(char *query,char **result)
{
	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	char *server = "localhost";
	char *user = "root";
	char *password = "1234567890";
	char *database = "network_disk";//要访问的数据库名称
	unsigned int queryRet;

    //初始化
	conn = mysql_init(NULL);
    if(!conn)
    {
        printf("MySQL init failed\n");
        return -1;
    }

    //连接数据库，看连接是否成功，只有成功才能进行后面的操作
	if(!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0))
	{
		printf("Error connecting to database: %s\n", mysql_error(conn));
		return -1;
	}
    else
    {
		printf("MySQL Connected...\n");
	}

    //把SQL语句传递给MySQL
	queryRet = mysql_query(conn, query);
	if(queryRet)
	{
		printf("Error making query: %s\n", mysql_error(conn));
	}
    else
    {
        //用mysql_num_rows可以得到查询的结果集有几行
        //要配合mysql_store_result使用
        //第一种判断方式
        res = mysql_store_result(conn);
        printf("mysql_num_rows = %lu\n", (unsigned long)mysql_num_rows(res));

        //第二种判断方式,两种方式不能一起使用
		/* res = mysql_use_result(conn); */
            
        row = mysql_fetch_row(res);
		if(NULL == row)
        {
            char *goal = (char *)calloc(20,1);
            strcpy(goal,"noexist");
            memcpy(result,&goal,20);
        }
        else
		{
            do
            {	
				/* printf("num=%d\n",mysql_num_fields(res));//列数 */
                //每次for循环打印一整行的内容
				for(queryRet = 0; queryRet < mysql_num_fields(res); ++queryRet)
				{
                    /* memset(*result, 0, 128); */
                    strcat(*result, row[queryRet]);
                    strcat(*result, " ");
                    printf("result = %s\n",*result);
                    //sprintf(*result,"%s ",row[queryRet]);
				}
            }while(NULL != (row = mysql_fetch_row(res)));
		}

		mysql_free_result(res);
	}

	mysql_close(conn);

	return 0;
}
