#include<pthread.h>
#include<stdio.h>
#include<unistd.h>

#define THREAD_COUNT 10
// pthread_mutex_t mutex;
// pthread_spinlock_t spinlock;//定义自旋锁

int increase(int *value,int add){
    int old;
    __asm__ volatile(
        "lock;xaddl %2,%1;"
        :"=a"(old)
        :"m"(*value),"a"(add)
        :"cc","memory"
    );

    return old;
}

void* thread_callback(void* arg){
    int* pcount=(int*)arg;
    int i=0;
    while(i++<100000000){
#if 0
        (*pcount)++;
#elif 0 
        //加了互斥锁
        pthread_mutex_lock(&mutex);
        (*pcount)++;
        pthread_mutex_unlock(&mutex);
#elif 0 
        //加了自旋锁
        pthread_spin_lock(&spinlock);
        (*pcount)++;
        pthread_spin_unlock(&spinlock);
#else
        increase(pcount,1);
#endif
        usleep(1);

    }
}

int main(){

    pthread_t threadid[THREAD_COUNT]={0};
    // pthread_mutex_init(&mutex,NULL);
    // pthread_spin_init(&spinlock,PTHREAD_PROCESS_SHARED);//自旋锁初始化（第二个参数是 进程共享）
    int count=0;
    for(int i=0;i<THREAD_COUNT;i++){
        pthread_create(&threadid[i],NULL,thread_callback,&count);
    }

    for(int i=0;i<100;i++){
        printf("count: %d\n",count);
        sleep(1);//单位秒
    }
}





