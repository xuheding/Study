#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/epoll.h>

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>

#include<pthread.h>

#define BUFFER_LENGTH 1024
#define EPOLL_SIZE 1024

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
    addr.sin_addr.s_addr=INADDR_ANY;
    if(bind(sockfd,(sockaddr*)&addr,sizeof(sockaddr_in))<0){
        perror("bind");
        return 2;
    }
    if(listen(sockfd,5)<0){
        perror("listen");
        return 3;
    }

    int epfd=epoll_create(1);//里面的参数只要大于0就ok,里面的参数只有0和1的区别
    epoll_event events[EPOLL_SIZE]={0};
    epoll_event ev;
    ev.events=EPOLLIN;//EPOLLIN表示有数据来了
    ev.data.fd=sockfd;
    epoll_ctl(epfd,EPOLL_CTL_ADD,sockfd,&ev);//将 监听的sockfd(门卫)交给epollfd(快递员)管理
    while(1){
        int nready=epoll_wait(epfd,events,EPOLL_SIZE,0);//返回值为事件个数 ；第四个参数：-1表示永久阻塞,0表示立即返回,如果是n，那么n个时间间隔执行一次。
        if(nready==-1) continue;//如果一个事件都没有就continue
        for(int i=0;i<nready;i++){//nready中包含了listenfd和clientfd，这两个要区别处理
           if(events[i].data.fd==sockfd){//listenfd  //有新的客户端连接
                sockaddr_in client_addr;
                memset(&client_addr,0,sizeof(sockaddr_in));
                socklen_t client_len=sizeof(client_addr);
                int clientfd=accept(sockfd,(sockaddr*)&client_addr,&client_len);

                ev.events=EPOLLIN|EPOLLET;//边沿触发
                ev.data.fd=clientfd;
                epoll_ctl(epfd,EPOLL_CTL_ADD,clientfd,&ev);//把新的的客户fd加入到epoll中
            }else{
                int clientfd=events[i].data.fd;

                char buffer[BUFFER_LENGTH]={0};
                int len=recv(clientfd,buffer,BUFFER_LENGTH,0);
                if(len<0){
                    close(clientfd);

                    ev.events=EPOLLIN;
                    ev.data.fd=clientfd;
                    epoll_ctl(epfd,EPOLL_CTL_DEL,clientfd,&ev);
                    break;
                }
                else if(len==0){
                    close(clientfd);
                    ev.events=EPOLLIN;
                    ev.data.fd=clientfd;
                    epoll_ctl(epfd,EPOLL_CTL_DEL,clientfd,&ev);
                    break;
                }
                else{
                    printf("Recv:%s,%d bytes\n",buffer,len);
                }
            }
        }

    }

    return 0;
}