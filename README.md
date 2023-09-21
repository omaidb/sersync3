# sersync3
sersync3文件和目录实时同步工具



# sersync2.5 stable final
最后更新时间：2011 年 10 月 26 日
1. 对于已经存在的目录filter过滤失效的bug
2. 增加inotify的debug信息



# sersync2.5Rc2

1. 为了改善监控效率，xfs文件系统，需在配置文件中开启xfs选项
2. 增加inotify createFile createFolder参数，可以根据项目需求做开关监控文件或文件夹
3. 以"."开头的文件夹不过滤
4. 可以自定义rsync基本参数
5. 可以自定义inotify权限监控等其他参数设置



# sersync2.5Rc1

1. 解决在xfs文件系统下无法递归监控目录的bug
2. 修改crontab中的rsync参数与实时同步时，参数不统一的bug



# sersync2.5beta4

1. crontab 无效的，严重bug修改。
2. Debug信息增加了inotify部分的调试信息。
3. 参数中增加－a －－timeout参数


# sersync2.5beta3
1. -e ssh参数的bug修改，在模块名处填写要同步的路径
2. rsync_fail_log.sh失败重传脚本配置


# sersync2.5beta2

1. 增加可配置-e ssh 与 --port自定义端口 rsync命令。
2. 增加command插件并可以配置插件过滤器，使插件只对满足正则的文件进行调用。


# sersync2.5beta1

1. 修改sersync2.4中，如果使用--password-file带密码同步，－r没有调用--password-file,对源与目的整体同步一遍bug
2. 将启动提示基本改为英文。
3. 可以使用delete标签指定是否对本地的delete事件进行监控。
4. rsync.fail.log.sh 会记录调用rsync错误号，便于以后改进。
5. 改掉本地host ip 与远程 remote ip 相同时候，不进行同步的限制。现在可以将本地与远程都设为127.0.0.1进行本机同步了，无须把其中一个设置为localhost.


# sersync2.4
修正重大 bug，当删除一次文件后，无法同步的错误，这个错误在低版本的sersync都存在，抱歉。

增加debug功能，可以开启debug看同步的文件<br />


# sersync2.3
修正同步文件名中存在‘$’ ‘(’ ‘)’等需要转义字符时发生错误的情况。<br />增加密码同步功能。<br />增加文件过滤功能，可以自定义任意条过滤规则。<br />诸如 要过滤`*`.php 或者dirname1/`*`之类的文件,只需在配置文件中填写该正则表达即可。<br />


# sersync2.2
>去除curl库，基本上编译只依赖标准库，暂时去除http插件的功能。