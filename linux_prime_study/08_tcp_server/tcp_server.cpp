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
        int len=recv(clientfd,buffer,BUFFER_LENGTH,0);//�����ͻ����
        if(len<0){//����io������len<0��Ϊ���������recvʱ��,һ����������˵��������
            close(clientfd);
            break;
        }else if(len==0){//disconnect (��ȡ����Ϊ0��˵���ͻ��˶Ͽ�������)
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
    addr.sin_addr.s_addr=INADDR_ANY;//0.0.0.0 ��ָ��������˼
    if(bind(sockfd,(sockaddr*)&addr,sizeof(sockaddr_in))<0){//��
        perror("bind");
        return 2;
    }
    if(listen(sockfd,5)<0){//����(�������Ŷ�5��)
        perror("listen");
        return 3;
    }

    //һ���� һ�߳�
    while(1){
        sockaddr_in client_addr;
        memset(&client_addr,0,sizeof(sockaddr_in));
        socklen_t client_len = sizeof(client_addr);
        int clientfd = accept(sockfd,(sockaddr*)&client_addr,&client_len);//����һ���ͻ�����������ip�浽client_addr��,���γ���һ���ͻ���fd

        pthread_t thread_id;
        pthread_create(&thread_id,NULL,client_routine,&clientfd);//Ϊÿ��clientfd����һ���߳�
    }
    return 0;



}