#ifndef __MYAQL_FUNC__
#define __MYAQL_FUNC__

int mysql_insert(char *query);
int mysql_delete(char *query);
int mysql_query1(char *query,char **result);
int mysql_query2(char *query,char **result);

#endif
