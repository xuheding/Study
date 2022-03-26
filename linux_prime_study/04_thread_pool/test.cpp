#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>


struct nManager;

#define LIST_INSERT(item,list) do{\
    item->prev=NULL;\
    item->next=list;\
    if((list)!=NULL) (list)->prev=item;\
    (list)=item;\
}while(0)

#define LIST_REMOVE(item,list) do{\
    if(item->prev!=NULL) item->prev->next=item->next;\
    if(item->next!=NULL) item->next->prev=item->prev;\
    if(item==list) list=item->next;\
    item->prev=item->next=NULL;\
}while(0)


struct nTask{
    void(*task_func)(nTask* task);
    void *user_data;
    nTask* prev;
    nTask* next;
};

struct nWorker{
    pthread_t pthreadId;
    nManager *manager;
    int terminate;
    nWorker* prev;
    nWorker* next;
};

typedef struct nManager{
    nTask *tasks;
    nWorker *workers;

    pthread_mutex_t mutex;
    pthread_cond_t cond;
}ThreadPool;

static void* nThreadPoolCallBack(void* arg){
    nWorker* worker=(nWorker*)arg;
    while(true){
        pthread_mutex_lock(&worker->manager->mutex);
        while(worker->manager->tasks==NULL){
            if(worker->terminate) break;
            pthread_cond_wait(&worker->manager->cond,&worker->manager->mutex);
        }
        if(worker->terminate){
            pthread_mutex_unlock(&worker->manager->mutex);
            break;
        }
        nTask* task=worker->manager->tasks;
        LIST_REMOVE(task,worker->manager->tasks);
        pthread_mutex_unlock(&worker->manager->mutex);//解锁
        task->task_func(task);
    }
    free(worker);
}
//API
int nThreadPoolCreate(ThreadPool* pool,int numWorkers){
    if(pool==NULL) return -1;
    if(numWorkers<1) numWorkers=1;
    memset(pool,0,sizeof(ThreadPool));

    pthread_cond_t blank_cond=PTHREAD_COND_INITIALIZER;
    pool->cond=blank_cond;
    pthread_mutex_init(&pool->mutex,NULL);
    for(int i=0;i<numWorkers;i++){
        nWorker* worker=(nWorker*)malloc(sizeof(nWorker));
        if(worker==NULL){
            perror("malloc");
            return -2;
        }
        memset(worker,0,sizeof(nWorker));
        worker->manager=pool;
        int ret=pthread_create(&worker->pthreadId,NULL,nThreadPoolCallBack,worker);
        if(ret){
            perror("pthread_create");
            free(worker);
            return -3;
        }
        LIST_INSERT(worker,pool->workers);
    }
    return 0;
}
//API
int nThreadPoolDestory(ThreadPool* pool,int numWorkers){
    nWorker* worker=NULL;
    for(worker=pool->workers;worker!=NULL;worker=worker->next){
        worker->terminate=1;
    }
    pthread_mutex_lock(&pool->mutex);
    pthread_cond_broadcast(&pool->cond);
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

#if 1
#define THREADPOOL_INIT_COUNT 20
#define TASK_INIT_SIZE 1000

void task_entry(nTask* task){
    int idx=*(int*)task->user_data;
    printf("idx:%d\n",idx);
    free(task->user_data);
    free(task);
}

int main(void){
    ThreadPool pool={0};
    nThreadPoolCreate(&pool,THREADPOOL_INIT_COUNT);
    int i=0;
    for(int i=0;i<TASK_INIT_SIZE;i++){
        nTask *task=(nTask*)malloc(sizeof(nTask));
        if(task==NULL){
            perror("malloc");
            exit(1);
        }
        memset(task,0,sizeof(nTask));
        task->task_func=task_entry;
        task->user_data=malloc(sizeof(int));
        *(int*)task->user_data=i;
        nThreadPoolPushTask(&pool,task);
    }
    getchar();
}




#endif