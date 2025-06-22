#include <unistd.h>
#include <stdio.h>
#include <shadow.h>
#include <crypt.h>
#include <string.h>

//从密文中获取盐值
void getsalt(char *salt, char *passwd)
{
    int i = 0;//定位第三个$符号后面的字符串
    int j = 0;//计算$的数量
    for (i = 0, j = 0; passwd[i] && j != 3; ++i) {
        if ('$' == passwd[i]) {
            j++;
        }
    }

    strncpy(salt, passwd, i - 1);
}

int main(int argc, char *argv[])
{
    //命令行参数：系统用户名
    if (2 != argc) {
        fprintf(stderr, "args error\n");
        return -1;
    }

    struct spwd *sp;//用来取文件中的密码
    char *passwd;//输入的密码
    char salt[512] = "";

    //输入密码
    passwd = getpass("请输入密码：");
    printf("passwd: %s\n", passwd);

    //获取用户信息
    sp = getspnam(argv[1]);
    if (NULL == sp) {
        fprintf(stderr, "用户名错误\n");
        return -1;
    }
    printf("Encrypted password: %s\n", sp->sp_pwdp);

    //拿到用户的盐值
    getsalt(salt, sp->sp_pwdp);
    printf("salt: %s\n", salt);

    //比对
    if (!strcmp(sp->sp_pwdp, crypt(passwd, salt))) {
        printf("登录成功！\n");
    }
    else {
        printf("登录失败！\n");
    }
    return 0;
}
