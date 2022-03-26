#include<sys/socket.h>
#include<netdb.h>
#include<arpa/inet.h>

#include<stdio.h>
#include<fcntl.h>
char* host_to_ip(char* hostname){
    hostent* host_entry=gethostbyname(hostname);
    if(host_entry){
        return inet_ntoa(*(in_addr*)*(host_entry->h_addr_list));
    }
    return NULL;
}

int http_create_socket(char* ip){
    int sockfd=socket(AF_INET,SOCK_STREAM,0);
    sockaddr_in sin={0};
    sin.sin_family=AF_INET;
    sin.sin_port=htons(80);
    sin.sin_addr.s_addr=inet_addr(ip);
    int ret=connect(sockfd,(sockaddr*)&sin,sizeof(sockaddr));
    if(ret!=0) return false;
    fcntl(sockfd,F_SETFL,O_NONBLOCK);
    return sockfd;
}