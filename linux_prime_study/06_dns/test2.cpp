#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include<arpa/inet.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<time.h>

#include<string>
using namespace std;

#define DNS_SERVER_PORT 53
#define DNS_SERVER_IP "114.114.114.114"

struct  dns_header
{
    unsigned short id;
    unsigned short flags;
    unsigned short questions;
    unsigned short answers;
    unsigned short authority;
    unsigned short additional;

};

struct dns_question
{
    int length;
    char* name;
    unsigned short qtype;
    unsigned short qclass;
};

int dns_create_header(dns_header* header){
    if(header==NULL) return -1;
    memset(header,0, sizeof(dns_header));

    srandom(time(NULL));
    header->id=random();
    header->flags=htons(0x0100);
    header->questions=htons(1);
    return 0;
}

#if 1
int dns_create_question(dns_question* question,const char* hostname){
    if(question==NULL||hostname==NULL) return -1;
    memset(question,0,sizeof(dns_question));
    question->name=(char*)malloc(strlen(hostname)+2);
    if(question->name==NULL) return -2;
    question->length=strlen(hostname)+2;
    question->qtype=htons(1);
    question->qclass=htons(1);

    // memset(question->name,0,question->length);
    int i=0,n=strlen(hostname);
    string hostname_tmp=(char*)hostname;
    string name;
    while(i<n){
        int start=i;
        while(i<n&&hostname_tmp[i]!='.') i++;
        name+=i-start;
        name+=hostname_tmp.substr(start,i-start);
        while(i<n&&hostname[i]=='.') i++;
    }
    for(int i=0;i<question->length;i++) question->name[i]=name[i];
    return 0;
}
#endif

#if 0
int dns_create_question(dns_question* question,const char* hostname){
    if(question==NULL||hostname==NULL) return -1;
    memset(question,0,sizeof(question));
    question->name=(char*)malloc(strlen(hostname)+2);
    if(question->name==NULL){
        return -2;
    } 
    question->length=strlen(hostname)+2;
    question->qtype=htons(1);
    question->qclass=htons(1);

    //hostname->name
    const char delim[2]=".";
    char* qname=question->name;
    char* hostname_dup=strdup(hostname);
    char* token=strtok(hostname_dup,delim);
    while(token!=NULL){
        size_t len=strlen(token);
        *qname=len;
        qname++;
        strncpy(qname,token,len+1);
        qname+=len;
        token=strtok(NULL,delim);
    }
    free(hostname_dup);

}
#endif

int dns_build_request(dns_header* header,dns_question* question,char* request,int rlen){
    if(header==NULL||question==NULL||request==NULL) return -1;
    memset(request,0,rlen);
    memcpy(request,header,sizeof(dns_header));
    int offset=sizeof(dns_header);

    memcpy(request+offset,question->name,question->length);
    offset+=question->length;
    memcpy(request+offset,&question->qtype,sizeof(question->qtype));
    offset+=sizeof(question->qtype);
    memcpy(request+offset,&question->qclass,sizeof(question->qclass));
    offset+=sizeof(question->qclass);
    return offset;

}

int dns_client_commit(const char* domin){
    int sockfd=socket(AF_INET,SOCK_DGRAM,0);
    if(sockfd<0) return -1;
    sockaddr_in servaddr={0};
    servaddr.sin_family=AF_INET;
    servaddr.sin_port=htons(DNS_SERVER_PORT);
    servaddr.sin_addr.s_addr=inet_addr(DNS_SERVER_IP);
    int ret=connect(sockfd,(sockaddr*)&servaddr,sizeof(servaddr));//ǿתָ�룿��
    printf("connect:%d",ret);

    dns_header header={0};
    dns_create_header(&header);
    dns_question question={0};
    dns_create_question(&question,domin);

    char request[1024]={0};
    int length=dns_build_request(&header,&question,request,1024);
    
    int slen=sendto(sockfd,request,length,0,(sockaddr*)&servaddr,sizeof(sockaddr));
    char response[1024]={0};
    sockaddr_in addr;
    size_t addr_len=sizeof(sockaddr_in);
    int n=recvfrom(sockfd,response,sizeof(response),0,(sockaddr*)&addr,(socklen_t*)&addr_len);
    printf("recvfrom:%d\n",n);
    for(int i=0;i<n;i++){
        printf("%c",response[i]);
    }
    printf("\n");
    printf("\n");
    for(int i=0;i<n;i++){
        printf("%x",response[i]);
    }
    printf("\n");
    return n;
}

int main(int argc,char** argv){
    if(argc<2) return -1;
    dns_client_commit(argv[1]);
}