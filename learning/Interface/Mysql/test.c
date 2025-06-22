#include <func.h>

#define MAX_TOKEN 17
#define MSG_BUF 1000

typedef  struct{
    int id;//当msg_from判断为c的时候，表明该消息来自于客户端，可以通过此处的id结合数据库或者结合token进行登录判断
    char msg_type;//消息类型，l:长命令,s:短命令,m:通知信息,d:数据信息
    char msg_from;//c表示来自客户端,s表示来自服务器端
    char is_trust;//是否开启信任机制,1表示开启信任机制，0表示不开启信任机制
    char token[MAX_TOKEN];
    char buf[MSG_BUF];
}msg_t, *pMsg_t;

int main(int argc, char *argv[]) 
{
    msg_t msg;
    printf("sizeof(msg) = %ld\n", sizeof(msg));
    return 0;
}
