/*
 * @Author: 自然自在 omaidb@gmail.com
 * @Date: 2024-04-10 11:39:20
 * @LastEditors: 自然自在 omaidb@gmail.com
 * @LastEditTime: 2024-04-10 11:45:33
 * @FilePath: \undefinedd:\code\sersync3\main1.cpp
 * @Description: https://blog.csdn.net/omaidb/article/details/133091969
 */
#include <stdio.h>
#include "main.h"
// 引入多个头文件，用于文件同步服务和各种接口
#include "Daemon.h"
#include "CdnRefreshInterface.h"
#include "Inotify.h"
#include "Initialize.h"
#include "QueueFilter.h"
#include "QueueRetry.h"
#include "FileSynchronize.h"
#include "SocketInterface.h"
#include "CommandInterface.h"
// #include"HttpInterface.h" // HTTP接口已被注释掉，可能是因为当前版本不使用或尚未实现
#include "Interface.h"
#include "main.h"

// 定义DEBUG标志，用于控制调试输出
#define DEBUG 0
// IN_SYNC变量表示inotify监视参数：in_create 和 in_close_write
int IN_SYNC = 0;

// 声明用于不同级别调试的函数
void DebugStart(int level);

// 声明启动文件同步模块的函数
void FileSynchronizeStart(boost::shared_ptr<Initialize> init);

// 声明启动模块接口的函数
void ModuleInterfaceStart(string config_file_name, Interface *module);

// 全局智能指针对象，用于事件过滤队列
ptrQFilter qf(new QueueFilter);

// 全局智能指针对象，用于失败事件队列
ptrQRetry qr(new QueueRetry);

// 全局变量，用于设置调试等级
int debug_level = 0;

// 程序入口点：main函数
int main(int argc, char *argv[])
{
    // 根据DEBUG标志设置调试级别和输出
    // debug 开关 0关，3打印信息关开 2非线程 1主函数
    DebugStart(DEBUG);

    // 设置init智能指针，用于程序初始化
    boost::shared_ptr<Initialize> init(new Initialize(argc, argv));

    // 根据配置，可能启动守护进程
    if (init->exec_flag & OPEN_DAEMON)
    {
        Daemon_Start();
    }

    // 如果设置为"同步模块"，则启动文件同步服务
    if (init->module == "sersync")
    {
        FileSynchronizeStart(init);
    }
    // 如果设置为启动其他模块，启动对应的模块插件
    if (init->module == "other")
    {
        // 根据提供的命令行参数，查看需要执行哪个模块
        if (init->exec_flag & REFRESHCDN_MODULE)
        {
            cout << "启动刷新CDN模块" << endl;
            CdnRefreshInterface refresh;
            ModuleInterfaceStart(init->config_file_name, &refresh);
        }
        else if (init->exec_flag & SOCKET_MODULE)
        {
            cout << "启动SOCKET接口" << endl;
            SocketInterface socket;
            ModuleInterfaceStart(init->config_file_name, &socket);
        }
        else if (init->exec_flag & COMMAND_MODULE)
        {
            cout << "start command interface" << endl;
            CommandInterface command;
            ModuleInterfaceStart(init->config_file_name, &command);
        }

        // else if (init->exec_flag & HTTP_MODULE)
        //{
        //	cout << "启动HTTP接口" << endl;
        //	HttpInterface http;
        //	ModuleInterfaceStart( init->config_file_name, &http );
        // }
    }
    cout << "模块名称错误" << endl;
    exit(1);

} // end main

//=======================================================================
// 函数名：ModuleInterfaceStart
// 作者：zy(zhoukunta@qq.com)
// 日期：2009-01-24
// 功能：启动各个模块的接口
// 输入参数：config_file_name(string) - 配置文件名称
//           module(Interface*) - 指向多态基类的接口指针，用于调用多个模块
// 返回值：void
// 修改记录：
//=======================================================================
void ModuleInterfaceStart(string config_file_name, Interface *module)
{
    // 使用配置文件名调用模块的 XML 解析函数
    module->XmlParse(config_file_name);

    // 创建 inotify 对象，监控路径由 module 中的 m_watch 变量提供
    Inotify inotify(module->m_watch);

    // 进入无限循环，等待事件
    while (1)
    {
        // 获取事件，存放在事件队列 qf 中
        inotify.GetEvents(qf);

        // 当事件队列不为空时处理事件
        while (!qf->empty())
        {
            // 从事件队列中弹出一个事件并执行相应的操作
            Event e = qf->pop();
            module->Execute(e);
        }

        // 如果设置了调试级别，打印事件队列的信息
        if (debug_level & MAIN_INFO)
        {
            qf->printdeque();
        }
    }
}

//=======================================================================
// 函数名：FileSynchronizeStart
// 作者：zy(zhoukunta@qq.com)
// 日期：2009-01
// 功能：启动文件同步功能
// 输入参数：init(boost::shared_ptr<Initialize>) - 指向 Initialize 类对象的智能指针
// 返回值：void
// 修改记录：
//=======================================================================

void FileSynchronizeStart(boost::shared_ptr<Initialize> init)
{
    // 创建 FileSynchronize 对象，并将 init、qf、qr 作为参数传递
    boost::shared_ptr<FileSynchronize> syn(new FileSynchronize(init, qf, qr));

    // 输出运行消息及监控路径
    cout << "run the sersync: " << endl;
    cout << "watch path is: " << syn->watch << endl;

    // 创建 Inotify 对象，设置监控路径
    boost::shared_ptr<Inotify> inotify(new Inotify(syn->watch));

    // 进入无限循环，等待文件事件
    while (1)
    {
        // 获取事件，存放在事件队列 qf 中
        inotify->GetEvents(qf);

        // 触发同步线程
        syn->ThreadAwaken();

        // 如果设置了调试级别，打印两个队列的信息
        if (debug_level & MAIN_INFO)
        {
            qf->printdeque();
            qr->printdeque();
        }
    }
}

//=======================================================================
// 函数名：DebugStart
// 作者：zy(zhoukunta@qq.com)
// 日期：2009-01
// 功能：根据传入的参数级别，开启不同等级的调试信息
// 输入参数：level(int) - 调试级别，可取 1, 2, 3。其中 3 为开启所有调试信息，2 为除主函数外的子类调试信息，1 为仅开启主函数的调试信息
// 返回值：void
// 修改记录：
//=======================================================================
void DebugStart(int level)
{
    // 根据传入的调试级别设置全局的debug_level变量
    switch (level)
    {
    case 3:
        // 开启线程调试
        debug_level = debug_level | THREAD_DEBUG;
    case 2:
        // 开启子类调试
        debug_level = debug_level | SUB_CLASS;
    case 1:
        // 开启主函数信息调试
        debug_level = debug_level | MAIN_INFO;
        break;
    default:
        // 如果传入的级别不在1-3之间，则不开启调试
        debug_level = 0;
    }
}
