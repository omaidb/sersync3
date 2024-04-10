/* 
 * File:   main.h
 * Author: root
 * 
 * Description: 
 * 这个文件是主要的头文件，用于定义了一系列宏，
 * 用于设置调试级别，以及一个 debug_level 的全局变量声明。
 * 
 * Created on 2010年1月11日, 下午3:35
 */



#ifndef _MAIN_H
#define	_MAIN_H
// 主模块信息宏
#define MAIN_INFO 0x01
// 子类模块宏
#define SUB_CLASS 0x01<<1
// 线程调试宏
#define THREAD_DEBUG 0x01<<2
// 文件系统通知调试宏
#define INOTIFY_DEBUG 0x01<<3

// 定义最大大小常量
#define MAX_SIZE 1024
// 声明外部整数变量用于控制调试级别
extern int debug_level;
#endif	/* _MAIN_H */
