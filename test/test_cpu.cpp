#include <sched.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

/* sysconf( _SC_NPROCESSORS_CONF ) 查看cpu的个数；打印用%ld长整。
 * sysconf( _SC_NPROCESSORS_ONLN ) 查看在使用的cpu个数；打印用%ld长整 */
int main(int argc, char **argv)
{
    int cpus = 0;
    int  i = 0;
    cpu_set_t mask;
    cpu_set_t get;

    cpus = sysconf(_SC_NPROCESSORS_CONF);
    printf("cpus: %d\n", cpus);

    CPU_ZERO(&mask);    /* 初始化set集，将set置为空*/
    CPU_SET(0, &mask);  /* 依次将0、1、2、3号cpu加入到集合，前提是你的机器是多核处理器*/
    CPU_SET(1, &mask);
    CPU_SET(2, &mask);
    CPU_SET(3, &mask);

    /*设置cpu 亲和性（affinity）*/
    if (sched_setaffinity(0, sizeof(mask), &mask) == -1) {
        printf("Set CPU affinity failue, ERROR:%s\n", strerror(errno));
        return -1;
    }
    usleep(1000); /* 让当前的设置有足够时间生效*/

    /*查看当前进程的cpu 亲和性*/
    CPU_ZERO(&get);
    if (sched_getaffinity(0, sizeof(get), &get) == -1) {
        printf("get CPU affinity failue, ERROR:%s\n", strerror(errno));
        return -1;
    }

    /*查看运行在当前进程的cpu*/
    for(i = 0; i < cpus; i++) {

        if (CPU_ISSET(i, &get)) { /*查看cpu i 是否在get 集合当中*/
            printf("this process %d of running processor: %d\n", getpid(), i);
        }
    }
    sleep(3); //让程序停在这儿，方便top命令查看

    return 0;
}
