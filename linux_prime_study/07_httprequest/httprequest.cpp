#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<netdb.h>
#include <fcntl.h>

#define HTTP_VERSION "HTTP/1.1"
#define CONNECTION_TYPE "Connection:close\r\n"
#define BUFFER_SIZE 4096


char* host_to_ip(const char* hostname){
    hostent *host_entry=gethostbyname(hostname);
    //14.215.177.39 -->usigned int(��Ϊipv4��32λ�ģ�ÿ����ָ�,ֵΪ0~255.���ÿ�����unsigned int��ʾ��ÿ8λ��ʾһ��0~255����4��)
    //inet_nota �ǰ� 0x12121212 --->"18.18.18.18" Ҳ���ǽ������ַת���ɡ�.��������ַ�����ʽ
    if(host_entry){
        return inet_ntoa(*(in_addr*)*host_entry->h_addr_list);//����h_addr_list�����м���ip��ַ�����ȡ��һ��,��˼�*,Ȼ��ǿת��in_addr*,����inet_ntoaΪֵ���ݣ���˻�Ҫ��*
    }
    return NULL;
}

int http_create_socket(char* ip){
    int sockfd=socket(AF_INET,SOCK_STREAM,0);//sockfd�Ľ������int���ͣ���һ���ļ������TCPҪ��SOCK_STREAM,UDP��SOCK_DGRAM
    sockaddr_in sin={0};
    sin.sin_family=AF_INET;
    sin.sin_port=htons(80);//httpЭ��˿�Ϊ80
    sin.sin_addr.s_addr=inet_addr(ip);//"�ַ�����ip"��ַתΪuint32_t�������inet_ntoa�����෴

    // int ret=connect(sockfd,(sockaddr*)&sin,sizeof(sockaddr_in));
    // if(ret!=0) return -1;
    if (0 != connect(sockfd, (struct sockaddr*)&sin, sizeof(struct sockaddr_in))) {
		return -1;
	}

    fcntl(sockfd,F_SETFL,O_NONBLOCK);//����Ϊ������(���socket��������read(),�������������socket�Ƿ�������read()Ҳ�����̷���)�������ļ�״̬��־��F_GETFL����ȡ�ļ�״̬��־��F_SETFL��
    return sockfd;
}

//hostname:github.com
//resource:/wangbojing
char* http_send_request(const char* hostname,const char* resource){
    char* ip=host_to_ip(hostname);
    int sockfd=http_create_socket(ip);

    char buffer[BUFFER_SIZE]={0};
    sprintf(buffer,
"GET %s %s\r\n\
Host:%s\r\n\
%s\r\n\
\r\n",
    resource,HTTP_VERSION,
    hostname,
    CONNECTION_TYPE
    );

    send(sockfd,buffer,strlen(buffer),0);


    // recv()//��Ϊ�Ƿ�����״̬�������recv����ٹ�ȥ

    //select
    fd_set fdread;
    FD_ZERO(&fdread);//�������fd_set���ϣ�����fd_set���ϲ��ٰ����κ��ļ����
    FD_SET(sockfd,&fdread);//��sockfd��Ϊ����״̬(������һ���������ļ����������뼯��֮��)

    timeval tv;
    tv.tv_sec=5;//5���� select�ɼ�һ��
    tv.tv_usec=0;


    char* result=(char*)malloc(sizeof(int));
    memset(result,0,sizeof(int));
    while(1){
        int selection=select(sockfd+1,&fdread,NULL,NULL,&tv);//��һ������Ϊ�����ļ������������ֵ+1   ��selectȥ��⣬���io������������
        if(!selection||!FD_ISSET(sockfd,&fdread)){//FD_ISSET�ж�������fd�Ƿ��ڸ�������������fdset��
            break;
        }else{
            memset(buffer,0,BUFFER_SIZE);
            int len=recv(sockfd,buffer,BUFFER_SIZE,0);//��������(���fdread�м�⵽����)
            if(len==0){//disconnect
                break;
            }
            result=(char*)realloc(result,(strlen(result)+len+1)*sizeof(char));//���·����ڴ��ؽ�(+1��Ϊ��ĩβ'\0',�������һ���Ļ��ᱻ����)
            strncat(result,buffer,len);//��buffer����copy��resulut��
        }
    }
    return result;
}

int main(int argc,char* argv[]){
    if(argc<3) return -1;
    char* response = http_send_request(argv[1],argv[2]);
    printf("response:%s\n",response);
    free(response);
}