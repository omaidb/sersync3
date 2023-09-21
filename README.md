# 使用教程
https://blog.csdn.net/omaidb/article/details/133091969

<br/>

# sersync3
`sersync2.5`版本的最后更新时间是：`2011年10月26日`,

原作者 周洋 大佬已经不再继续更新；
个人使用中出现的一些问题，想自动动手解决：
1. 不支持单文件同步，仅支持目录同步

为了与原作者的`sersync2`区分，所以将该项目命名为`sersync3`.

<br/>


## 原作者简介
原作者周洋: 曾在 前金山公司周洋 + 花椒直播 任职

原作者周洋的新浪微博：[http://weibo.com/johntech](http://weibo.com/johntech)

原作者周洋的推特: [https://twitter.com/zhoukunta](https://twitter.com/zhoukunta)

原作者周洋的博客: [https://github.com/johntech-o/blog](https://github.com/johntech-o/blog)

<br/>

## 功能简介
原文链接：https://blog.csdn.net/omaidb/article/details/133091969

服务器之间同步文件和文件夹-使用 inotiy 和 rsync 与 c++ 服务器实时同步文件，服务器镜像解决方案.

sersync主要应用于服务器同步和网页镜像，基于boost1.41.0、inotify api、rsync命令开发。目前常见的同步方案使用inotify-tools + rsync，或者使用google开源项目Openduckbill（依赖inotify-tools），都是用脚本语言编写的。与上述两个项目相比，本项目具有以下优点： 

1. sersync是使用c++编写，而且对Linux系统文件系统产生的临时文件和重复的文件操作进行过滤（详细见附录，这个过滤脚本程序没有实现），所以在结合rsync同步的时候，节省了运行时耗和网络资源。因此更快。
2. sersync配置起来很简单，其中已经静态编译好2进制文件和xml配置文件，直接使用即可。
3. sersync使用多线程进行同步，尤其在同步较大文件时，能够保证多个服务器实时保持同步状态。
4. sersync有出错处理机制，通过失败队列对出错的文件重新同步，如果仍旧失败，则按设定时长对同步失败的文件重新同步。
5. sersync不仅可以实时同步，另外还自带crontab功能，只需在xml配置文件中开启，即可按需求隔一段时间整体同步一次。无需再额外配置crontab功能。
6. sersync有socket与http插件扩展，满足二次开发的需要。

<br/>


# sersync2.5 stable final
最后更新时间：2011 年 10 月 26 日
1. 对于已经存在的目录filter过滤失效的bug
2. 增加inotify的debug信息

<br/>

# sersync2.5Rc2

1. 为了改善监控效率，xfs文件系统，需在配置文件中开启xfs选项
2. 增加inotify createFile createFolder参数，可以根据项目需求做开关监控文件或文件夹
3. 以"."开头的文件夹不过滤
4. 可以自定义rsync基本参数
5. 可以自定义inotify权限监控等其他参数设置

<br/>

# sersync2.5Rc1

1. 解决在xfs文件系统下无法递归监控目录的bug
2. 修改crontab中的rsync参数与实时同步时，参数不统一的bug

<br/>

# sersync2.5beta4

1. crontab 无效的，严重bug修改。
2. Debug信息增加了inotify部分的调试信息。
3. 参数中增加－a －－timeout参数

<br/>

# sersync2.5beta3
1. -e ssh参数的bug修改，在模块名处填写要同步的路径
2. rsync_fail_log.sh失败重传脚本配置

<br/>

# sersync2.5beta2

1. 增加可配置-e ssh 与 --port自定义端口 rsync命令。
2. 增加command插件并可以配置插件过滤器，使插件只对满足正则的文件进行调用。

<br/>

# sersync2.5beta1

1. 修改sersync2.4中，如果使用--password-file带密码同步，－r没有调用--password-file,对源与目的整体同步一遍bug
2. 将启动提示基本改为英文。
3. 可以使用delete标签指定是否对本地的delete事件进行监控。
4. rsync.fail.log.sh 会记录调用rsync错误号，便于以后改进。
5. 改掉本地host ip 与远程 remote ip 相同时候，不进行同步的限制。现在可以将本地与远程都设为127.0.0.1进行本机同步了，无须把其中一个设置为localhost.

<br/>

# sersync2.4
修正重大 bug，当删除一次文件后，无法同步的错误，这个错误在低版本的sersync都存在，抱歉。

增加debug功能，可以开启debug看同步的文件<br />

<br/>

# sersync2.3
修正同步文件名中存在‘$’ ‘(’ ‘)’等需要转义字符时发生错误的情况。<br />增加密码同步功能。<br />增加文件过滤功能，可以自定义任意条过滤规则。<br />诸如 要过滤`*`.php 或者dirname1/`*`之类的文件,只需在配置文件中填写该正则表达即可。<br />

<br/>

# sersync2.2
>去除curl库，基本上编译只依赖标准库，暂时去除http插件的功能。