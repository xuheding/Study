#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

#include<sys/socket.h>
#include<sys/epoll.h>
#include<netinet/in.h>
#include<arpa/inet.h>

#define EPOLL_SIZE 1024
#define BUFFER_SIZE 1024
int main(int argc,char** argv){
    if(argc<2){
        printf("Param Error");
        return -1;
    }
    int port=atoi(argv[1]);
    int sockfd=socket(AF_INET,SOCK_DGRAM,0);
    sockaddr_in addr;
    addr.sin_family=AF_INET;
    addr.sin_port=htons(port);
    addr.sin_addr.s_addr=INADDR_ANY;
    if(bind(sockfd,(sockaddr*)&addr,sizeof(sockaddr_in))<0){
        perror("bind");
        return -2;
    }
    if(listen(sockfd,5)<0){
        perror("listen");
        return -3;
    }

    int epfd=epoll_create(1);
    epoll_event events[EPOLL_SIZE]={0};
    epoll_event ev;
    ev.events=EPOLLIN;
    ev.data.fd=sockfd;
    epoll_ctl(epfd,EPOLL_CTL_ADD,sockfd,&ev);
    while(1){
        int nready=epoll_wait(epfd,events,EPOLL_SIZE,5);
        if(nready==-1) continue;
        for(int i=0;i<nready;i++){
            if(events[i].data.fd==sockfd){
                sockaddr_in client_addr;
                memset(&client_addr,0,sizeof(sockaddr_in));
                socklen_t client_len=sizeof(client_addr);
                int clientfd=accept(sockfd,(sockaddr*)&client_addr,&client_len);
                ev.events=EPOLLIN|EPOLLET;
                ev.data.fd=clientfd;
                epoll_ctl(epfd,EPOLL_CTL_ADD,clientfd,&ev);
            }
            else{
                int clientfd=events[i].data.fd;
                char buffer[BUFFER_SIZE]={0};
                int len=recv(clientfd,buffer,BUFFER_SIZE,0);
                if(len<0){
                    close(clientfd);
                    ev.events=EPOLLIN;
                    ev.data.fd=clientfd;
                    epoll_ctl(epfd,EPOLL_CTL_DEL,clientfd,&ev);
                }
                else if(len==0){
                    close(clientfd);
                    ev.events=EPOLLIN;
                    ev.data.fd=clientfd;
                    epoll_ctl(epfd,EPOLL_CTL_DEL,clientfd,&ev);
                }
                else{
                    printf("Recv:%s,%d btyes\n",buffer,len);
                }

            }
        }
        return 0;
    }
    


}