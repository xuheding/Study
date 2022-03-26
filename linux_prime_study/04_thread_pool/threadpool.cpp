#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<pthread.h>

//����
struct nManager;

////***********��������ĺ궨��**************////
//ͷ������
#define LIST_INSERT(item,list) do{  \
    item->prev=NULL;             \
    item->next=list;                \
    if((list)!=NULL) (list)->prev=item; \
    (list)=item;\
}while(0)

//ɾ���ڵ㣨���ָֻʣ��һ���ڵ��ʱ��Ҫ���⿼�ǣ�
#define LIST_REMOVE(item,list) do{    \
    if(item->prev!=NULL) item->prev->next=item->next; \
    if(item->next!=NULL) item->next->prev=item->prev; \
    if(list==item) list=item->next; \
    item->prev=item->next=NULL; \
}while(0)
////********************end******************////

struct nTask{
    void (*task_func)(nTask* task);//����ָ��
    void *user_data;//��������ݣ�Ҫ���뵽����ĺ�����ȥ��

    //��˫����������ʾ�������
    nTask *prev; 
    nTask *next;
}; 

struct nWorker{
    pthread_t threadId;
    nManager *manager;//������worker���Ը����̳߳�
    int terminate;//�Ƿ���ֹ

    nWorker *prev;
    nWorker *next;
};

//���������Ҳ�����̳߳�
typedef struct nManager{
    nTask *tasks;//������е��׽ڵ�
    nWorker *workers;//ִ�ж��е��׽ڵ�

    pthread_mutex_t mutex;//������
    pthread_cond_t cond;//�������� (����û���������ʱ��worker��Ҫ��ʲô�أ�������Ҫ�������)

}ThreadPool;

//callback!=task     
static void* nThreadPoolCallBack(void* arg){
    //workerһֱ���ж��������������û�����񣨵ȴ�����������һ�������񣬾ͻ���������ȡ����������
    nWorker* worker=(nWorker*)arg;

    //1.�ж����޵ȴ�������(�������)��2.���������Ͱ������������worker��3.ִ������

    while(true){//������Ϊ�յ�ʱ�򣬾ͻ������ߣ���Ȼ��һֱ������������
        pthread_mutex_lock(&worker->manager->mutex);//����
        while(worker->manager->tasks==NULL){
            if(worker->terminate) break;//�жϣ�2���ط����ԣ�1.�ȴ���ʱ�� 2.�����񣬻�δ���������ʱ��
            pthread_cond_wait(&worker->manager->cond,&worker->manager->mutex);//�ȴ�
        }
        if(worker->terminate){
            pthread_mutex_unlock(&worker->manager->mutex);//�жϵĻ��ǵý�������Ȼ���������
            break;
        } 
        //�������Ϊ�գ���ô��������У��׸�����ȡ����
        nTask* task=worker->manager->tasks;
        LIST_REMOVE(task,worker->manager->tasks);

        pthread_mutex_unlock(&worker->manager->mutex);//����

        task->task_func(task);//ִ������
    }
    delete worker;//���ڴ����߳�����,���Ե���һ��
}

//API
int nThreadPoolCreate(ThreadPool* pool,int numWorkers){
    if(pool==NULL) return -1;
    if(numWorkers<1) numWorkers=1;//�����ʼ�� workerС��1����Ĭ�ϸ���1��Ա��С��1�Ļ�������̳߳���û��������
    memset(pool,0,sizeof(ThreadPool));


    //��ʼ�� ��������
    pthread_cond_t blank_cond = PTHREAD_COND_INITIALIZER;
    pool->cond=blank_cond;
    //��ʼ�� ������
    pthread_mutex_init(&pool->mutex,NULL);
    //��ʼ��work
    for(int i=0;i<numWorkers;i++){
        nWorker *worker=(struct nWorker*)malloc(sizeof(struct nWorker));
        if(worker==NULL){//�������ʧ��
            perror("malloc");
            return -2;
        }
        memset(worker,0,sizeof(nWorker));//�����ϴ���������ȫ����0
        worker->manager=pool;//�������workerȥ�����̳߳�

        int ret=pthread_create(&worker->threadId,NULL,nThreadPoolCallBack,worker);//ÿ��workerִ�еĹ�����һ���ģ����������ǲ�һ����
        if(ret){//posixthread�и��ص㣬����ʧ�ܻ᷵�ط�0
            perror("pthread_create");
            delete worker;
            return -3;
        }
        LIST_INSERT(worker,pool->workers);//��worker���뵽 ִ�ж�����
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

    //��ֹ����
    pthread_mutex_lock(&pool->mutex); //�㲥��ʱ��͵ȴ���ʱ���õ���ͬһ����
    pthread_cond_broadcast(&pool->cond);//�������еȴ����������
    pthread_mutex_unlock(&pool->mutex);

    pool->workers=NULL;
    pool->tasks=NULL;

    return 0;   
}

//API
int nThreadPoolPushTask(ThreadPool* pool,nTask* task){
    pthread_mutex_lock(&pool->mutex);
    LIST_INSERT(task,pool->tasks);
    pthread_cond_signal(&pool->cond);//���ѵȴ������е�һ��
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

	getchar();//�ó���ͣ������һ��,ֱ�����Ӽ��̽��յ���Ϣ.
	
}


#endif
