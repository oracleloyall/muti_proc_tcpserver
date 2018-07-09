an epoll multi-process tcp server
第一阶段：
muti process处理不同的链接
第二阶段：
每个进程引入无锁queue，单生产者，多消费者（整体架构上是多生产多消费结构）-》or 协程
第三阶段：
均衡分配连接（accept由主进程控制），进程亲和性绑定关系设置（https://www.cnblogs.com/wenqiang/p/6049978.html） taskset
1、对运行中的进程，文档上说可以用下面的命令，把CPU#1 #2 #3分配给PID为2345的进程：
# taskset -cp 1,2,3 2345
2、指定进程在某个cpu上运行：
# taskset -c 1 /etc/init.d/mysql start
第四阶段
工作进程异常捕获(已经做了)
第五阶段：
进一步性能优化（分支预判等）
