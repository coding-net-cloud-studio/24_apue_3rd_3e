#include "apue.h"
#include <fcntl.h>

// 主函数,用于截断文件并重置其访问和修改时间
int main(int 参数个数, char *参数数组[])
{
    int             i, 文件描述符;   // i为循环变量,文件描述符用于存储打开文件的描述符
    struct stat     文件状态缓冲区;  // 用于存储文件的状态信息
    struct timespec 时间数组[2];     // 存储文件的访问和修改时间

    // 遍历命令行参数中的文件名
    for (i = 1; i < 参数个数; i++)
    {
        // 获取文件的状态信息
        if (stat(参数数组[i], &文件状态缓冲区) < 0)
        {                                           /* 获取当前时间 */
            err_ret("%s: stat 错误", 参数数组[i]);  // 如果出错,输出错误信息并继续处理下一个文件
            continue;
        }
        // 打开文件,并截断文件内容
        if ((文件描述符 = open(参数数组[i], O_RDWR | O_TRUNC)) < 0)
        {                                           /* 截断 */
            err_ret("%s: open 错误", 参数数组[i]);  // 如果出错,输出错误信息并继续处理下一个文件
            continue;
        }
        // 将文件的访问和修改时间存储到时间数组中
        时间数组[0] = 文件状态缓冲区.st_atim;
        时间数组[1] = 文件状态缓冲区.st_mtim;
        // 重置文件的访问和修改时间
        if (futimens(文件描述符, 时间数组) < 0)
            err_ret("%s: futimens 错误", 参数数组[i]);  // 如果出错,输出错误信息
        close(文件描述符);                              // 关闭文件描述符
    }
    exit(0);  // 程序正常退出
}
