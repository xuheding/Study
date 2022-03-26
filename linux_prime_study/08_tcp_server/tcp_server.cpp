#include<sys/socket.h>
#include<arpa/inet.h>

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include<pthread.h>
#include<unistd.h>

#define BUFFER_LENGTH 1024

void* client_routine(void* arg){
    int clientfd=*(int*)arg;
    while(1){
        char buffer[BUFFER_LENGTH]={0};
        int len=recv(clientfd,buffer,BUFFER_LENGTH,0);//阻塞就会挂起
        if(len<0){//阻塞io不存在len<0因为它会挂起在recv时刻,一旦发生，就说明出错了
            close(clientfd);
            break;
        }else if(len==0){//disconnect (读取数据为0就说明客户端断开连接了)
            close(clientfd);
            break;
        }else{
            printf("Recv:%s,%d bytes\n",buffer,len);
        }
    }
}



int main(int argc,char** argv){
    if(argc<2){
        printf("Param Error\n");
        return -1;
    }
    int port=atoi(argv[1]);

    int sockfd=socket(AF_INET,SOCK_STREAM,0);
    sockaddr_in addr;
    memset(&addr,0,sizeof(sockaddr_in));
    addr.sin_family=AF_INET;
    addr.sin_port=htons(port);
    addr.sin_addr.s_addr=INADDR_ANY;//0.0.0.0 泛指本机的意思
    if(bind(sockfd,(sockaddr*)&addr,sizeof(sockaddr_in))<0){//绑定
        perror("bind");
        return 2;
    }
    if(listen(sockfd,5)<0){//监听(最多可以排队5个)
        perror("listen");
        return 3;
    }

    //一请求 一线程
    while(1){
        sockaddr_in client_addr;
        memset(&client_addr,0,sizeof(sockaddr_in));
        socklen_t client_len = sizeof(client_addr);
        int clientfd = accept(sockfd,(sockaddr*)&client_addr,&client_len);//接受一个客户，并将它的ip存到client_addr中,并形成了一个客户端fd

        pthread_t thread_id;
        pthread_create(&thread_id,NULL,client_routine,&clientfd);//为每个clientfd分配一个线程
    }
    return 0;



}