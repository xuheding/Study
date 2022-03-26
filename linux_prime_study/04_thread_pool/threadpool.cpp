#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<pthread.h>

//声明
struct nManager;

////***********链表操作的宏定义**************////
//头部插入
#define LIST_INSERT(item,list) do{  \
    item->prev=NULL;             \
    item->next=list;                \
    if((list)!=NULL) (list)->prev=item; \
    (list)=item;\
}while(0)

//删除节点（如果指只剩下一个节点的时候要特殊考虑）
#define LIST_REMOVE(item,list) do{    \
    if(item->prev!=NULL) item->prev->next=item->next; \
    if(item->next!=NULL) item->next->prev=item->prev; \
    if(list==item) list=item->next; \
    item->prev=item->next=NULL; \
}while(0)
////********************end******************////

struct nTask{
    void (*task_func)(nTask* task);//函数指针
    void *user_data;//处理的数据（要传入到上面的函数中去）

    //用双向链表来表示任务队列
    nTask *prev; 
    nTask *next;
}; 

struct nWorker{
    pthread_t threadId;
    nManager *manager;//有利于worker可以更改线程池
    int terminate;//是否中止

    nWorker *prev;
    nWorker *next;
};

//管理组件，也就是线程池
typedef struct nManager{
    nTask *tasks;//任务队列的首节点
    nWorker *workers;//执行队列的首节点

    pthread_mutex_t mutex;//互斥锁
    pthread_cond_t cond;//条件变量 (比如没有来任务的时候，worker需要做什么呢，所以需要这个变量)

}ThreadPool;

//callback!=task     
static void* nThreadPoolCallBack(void* arg){
    //worker一直在判断任务队列里面有没有任务（等待任务到来），一旦有任务，就会从任务队列取出任务来。
    nWorker* worker=(nWorker*)arg;

    //1.判断有无等待的任务(任务队列)，2.如果有任务就把任务分配给这个worker，3.执行任务

    while(true){//当任务不为空的时候，就会往下走，不然会一直等着任务来。
        pthread_mutex_lock(&worker->manager->mutex);//上锁
        while(worker->manager->tasks==NULL){
            if(worker->terminate) break;//中断（2处地方可以：1.等待的时候 2.有任务，还未分配任务的时候）
            pthread_cond_wait(&worker->manager->cond,&worker->manager->mutex);//等待
        }
        if(worker->terminate){
            pthread_mutex_unlock(&worker->manager->mutex);//中断的话记得解锁，不然会造成死锁
            break;
        } 
        //如果任务不为空，那么将任务队列，首个任务取出来
        nTask* task=worker->manager->tasks;
        LIST_REMOVE(task,worker->manager->tasks);

        pthread_mutex_unlock(&worker->manager->mutex);//解锁

        task->task_func(task);//执行任务
    }
    delete worker;//由于存在线程销毁,可以到这一步
}

//API
int nThreadPoolCreate(ThreadPool* pool,int numWorkers){
    if(pool==NULL) return -1;
    if(numWorkers<1) numWorkers=1;//如果初始化 worker小于1，就默认给他1，员工小于1的话，这个线程池是没法工作的
    memset(pool,0,sizeof(ThreadPool));


    //初始化 条件变量
    pthread_cond_t blank_cond = PTHREAD_COND_INITIALIZER;
    pool->cond=blank_cond;
    //初始化 互斥锁
    pthread_mutex_init(&pool->mutex,NULL);
    //初始化work
    for(int i=0;i<numWorkers;i++){
        nWorker *worker=(struct nWorker*)malloc(sizeof(struct nWorker));
        if(worker==NULL){//如果创建失败
            perror("malloc");
            return -2;
        }
        memset(worker,0,sizeof(nWorker));//将堆上创建的数据全部置0
        worker->manager=pool;//方便后续worker去操作线程池

        int ret=pthread_create(&worker->threadId,NULL,nThreadPoolCallBack,worker);//每个worker执行的工作是一样的，但是任务是不一样的
        if(ret){//posixthread有个特点，创建失败会返回非0
            perror("pthread_create");
            delete worker;
            return -3;
        }
        LIST_INSERT(worker,pool->workers);//把worker插入到 执行队列中
    }
    //success
    return 0;
}

//API
int nThreadPoolDestory(ThreadPool* pool,int numWorkers){
    nWorker* worker=NULL;
    for(worker=pool->workers;worker!=NULL;worker=worker->next){
        worker->terminate=1;
    }

    //防止死锁
    pthread_mutex_lock(&pool->mutex); //广播的时候和等待的时候用的是同一把锁
    pthread_cond_broadcast(&pool->cond);//唤醒所有等待这个条件的
    pthread_mutex_unlock(&pool->mutex);

    pool->workers=NULL;
    pool->tasks=NULL;

    return 0;   
}

//API
int nThreadPoolPushTask(ThreadPool* pool,nTask* task){
    pthread_mutex_lock(&pool->mutex);
    LIST_INSERT(task,pool->tasks);
    pthread_cond_signal(&pool->cond);//唤醒等待队列中的一个
    pthread_mutex_unlock(&pool->mutex);
}

//
// sdk --> debug thread pool

#if 1

#define THREADPOOL_INIT_COUNT	20
#define TASK_INIT_SIZE			1000


void task_entry(struct nTask *task) { //type 

	int idx = *(int *)task->user_data;

	printf("idx: %d\n", idx);

	free(task->user_data);
	free(task);
}


int main(void) {

	ThreadPool pool = {0};
	
	nThreadPoolCreate(&pool, THREADPOOL_INIT_COUNT);
	// pool --> memset();
	
	int i = 0;
	for (i = 0;i < TASK_INIT_SIZE;i ++) {
		struct nTask *task = (struct nTask *)malloc(sizeof(struct nTask));
		if (task == NULL) {
			perror("malloc");
			exit(1);
		}
		memset(task, 0, sizeof(struct nTask));

		task->task_func = task_entry;
		task->user_data = malloc(sizeof(int));
		*(int*)task->user_data  = i;

		
		nThreadPoolPushTask(&pool, task);
	}

	getchar();//让程序停留在这一步,直到它从键盘接收到消息.
	
}


#endif
