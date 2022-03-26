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
    //14.215.177.39 -->usigned int(因为ipv4是32位的，每个点分隔,值为0~255.正好可以用unsigned int表示，每8位表示一个0~255，共4个)
    //inet_nota 是把 0x12121212 --->"18.18.18.18" 也就是将网络地址转换成“.”点隔的字符串格式
    if(host_entry){
        return inet_ntoa(*(in_addr*)*host_entry->h_addr_list);//由于h_addr_list可能有几个ip地址，这边取第一个,因此加*,然后强转成in_addr*,由于inet_ntoa为值传递，因此还要加*
    }
    return NULL;
}

int http_create_socket(char* ip){
    int sockfd=socket(AF_INET,SOCK_STREAM,0);//sockfd的结果就是int类型，是一个文件句柄。TCP要用SOCK_STREAM,UDP用SOCK_DGRAM
    sockaddr_in sin={0};
    sin.sin_family=AF_INET;
    sin.sin_port=htons(80);//http协议端口为80
    sin.sin_addr.s_addr=inet_addr(ip);//"字符串的ip"地址转为uint32_t和上面的inet_ntoa正好相反

    // int ret=connect(sockfd,(sockaddr*)&sin,sizeof(sockaddr_in));
    // if(ret!=0) return -1;
    if (0 != connect(sockfd, (struct sockaddr*)&sin, sizeof(struct sockaddr_in))) {
		return -1;
	}

    fcntl(sockfd,F_SETFL,O_NONBLOCK);//设置为非阻塞(如果socket是阻塞，read(),会阻塞挂起。如果socket是非阻塞，read()也是立刻返回)（设置文件状态标志用F_GETFL，读取文件状态标志用F_SETFL）
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


    // recv()//因为是非阻塞状态，如果用recv会快速过去

    //select
    fd_set fdread;
    FD_ZERO(&fdread);//用来清空fd_set集合，即让fd_set集合不再包含任何文件句柄
    FD_SET(sockfd,&fdread);//将sockfd置为检测的状态(用来将一个给定的文件描述符加入集合之中)

    timeval tv;
    tv.tv_sec=5;//5秒间隔 select采集一次
    tv.tv_usec=0;


    char* result=(char*)malloc(sizeof(int));
    memset(result,0,sizeof(int));
    while(1){
        int selection=select(sockfd+1,&fdread,NULL,NULL,&tv);//第一个参数为所有文件描述符的最大值+1   用select去监测，这个io里面有无数据
        if(!selection||!FD_ISSET(sockfd,&fdread)){//FD_ISSET判断描述符fd是否在给定的描述符集fdset中
            break;
        }else{
            memset(buffer,0,BUFFER_SIZE);
            int len=recv(sockfd,buffer,BUFFER_SIZE,0);//接受数据(如果fdread中检测到数据)
            if(len==0){//disconnect
                break;
            }
            result=(char*)realloc(result,(strlen(result)+len+1)*sizeof(char));//重新分配内存重建(+1是为了末尾'\0',不是最后一个的话会被覆盖)
            strncat(result,buffer,len);//把buffer数据copy到resulut中
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