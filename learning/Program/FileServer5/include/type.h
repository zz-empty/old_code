#ifndef __TYPE_H__
#define __TYPE_H__

#define DATA_LEN 1024
#define MSG_BUF 1000
#define CMD_ARGC 5
#define CMD_LEN 30

//传输文件协议：小货车
typedef struct {
    int _data_len;//货车头，表示数据长度
    char _data[DATA_LEN];//火车车厢，表示数据
}Truck_t;

//传输消息类型
typedef struct {
    char _type; //消息类型（l-长命令，s-短命令，m-通知消息，d-具体数据
    char _from; //消息来源（c-来自客户端，s-来自服务器）
    char _buf[MSG_BUF];//数据（存命令）
}Msg_t, *pMsg_t;

//传输的自定义命令
typedef struct {
    int _argc;  //命令有几个参数
    char _cmd[CMD_ARGC][CMD_LEN]; //具体命令
}Cmd_t, *pCmd_t;

//用户信息节点
typedef struct {
    int _id;    //用户唯一标识符
    int _clifd; //用户套接字

}Client_t;

#endif
