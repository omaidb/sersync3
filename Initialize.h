/*
 * @Author: error: error: git config user.name & please set dead value or install git && error: git config user.email & please set dead value or install git & please set dead value or install git
 * @Date: 2024-04-10 11:36:22
 * @LastEditors: error: error: git config user.name & please set dead value or install git && error: git config user.email & please set dead value or install git & please set dead value or install git
 * @LastEditTime: 2024-04-11 09:37:09
 * @FilePath: \sersync3\Initialize.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
/* 
 * File:   Initialize.h
 * Author: root
 *
 * Created on 2010年1月10日, 下午7:55
 */

// 防止头文件重复包含的预处理指令
#ifndef _INITIALIZE_H
#define	_INITIALIZE_H

// 引入标准输入输出库
#include<stdio.h>
// 引入Boost库的智能指针
#include<boost/shared_ptr.hpp>
// 引入C++标准库中的字符串类
#include<string>
// 引入C++标准库中的向量容器
#include<vector>
// 引入系统inotify监视文件系统事件的头文件
#include <sys/inotify.h>

// 定义各种功能模式的标志
#define OPEN_DAEMON         0x01            // 守护进程模式
#define RSYNC_ONCE          0x01<<1         // 一次性rsync同步
#define SYN_NUM             0x01<<2         // 同步数量模式
#define OTHER_CONFNAME      0x01<<3         // 其他配置名
#define EXECUTE_SCRIPT      0x01<<5         // 执行脚本模式
#define SERSYNC_MODULE      0x01<<6         // 服务器同步模块
#define REFRESHCDN_MODULE   0x01<<7         // CDN刷新模块
#define HTTP_MODULE         0x01<<8         // HTTP模块
#define SOCKET_MODULE       0x01<<9         // SOCKET通信模块
#define COMMAND_MODULE      0x01<<10        // 命令行模块

// 远程服务器结构，用于存储IP地址和模块名称
struct RemoteServer {
    std::string ip;       // IP地址
    std::string module;   // 模块名称

    // 构造函数，可以初始化为特定的IP和模块，也可以默认为空
    inline RemoteServer(std::string ip = "", std::string module = "") : ip(ip), module(module) {
    }
};

// 共享指针类型定义，方便管理RemoteServer对象的内存
typedef boost::shared_ptr<RemoteServer> ptrRmtServer;

// 初始化类定义
class Initialize {
public:
    int exec_flag;                // 执行标志
    int sync_num;                 // 同步数量
    std::string module;           // 当前模块
    std::string config_file_name; // 配置文件名
    std::string hostip;           // 主机IP
    static std::vector<std::string> filter; // 过滤器
    int port;                     // 端口号
    static bool debug;            // 调试标志
    bool deleteFlag;              // 删除标志
    static bool createFile;       // 文件创建标志
    static bool createFolder;     // 文件夹创建标志
    static bool xfs;              // xfs文件系统标志
    
public:
    // 带参数的构造函数，用于程序初始化
    Initialize(int argc, char *argv[]);
    // 设置inotify配置
    void ConfigInotify();
    // XML解析函数
    int XmlParse();
    // 从字符串的最后开始分割斜杠
    static std::string SplitLastSlash(std::string str);

protected:
    // 命令解析函数
    int CammandParse(int argc, char *argv[]);
};

// 共享指针类型定义，用于初始化类对象内存的管理
typedef boost::shared_ptr<Initialize> ptrInitialize;
#endif /* _INITIALIZE_H */
