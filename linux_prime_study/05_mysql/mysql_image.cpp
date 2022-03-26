#include<mysql.h>
#include<stdio.h>
#include<string.h>


#define KING_DB_SERVER_IP "192.168.192.128" //ip
#define KING_DB_SERVER_PORT 3306            //端口号
#define KING_DB_USERNAME "admin"            //用户名
#define KING_DB_PASSWORD "123456"           //密码
#define KING_DB_DEFAULTDB "KING_DB"         //数据库名

//插入图片的SQL语句，由于不知道传入的图片是什么，用？作为占位符
#define SQL_INSERT_IMG_USER "insert TBL_USER(U_NAME,U_GENDER,U_IMG) value('Dog','man',?);"  

#define SQL_SELECT_IMG_USER "SELECT U_IMG FROM TBL_USER WHERE U_NAME='Dog';"
#define FILE_IMAGE_LENGTH (64*1024)



//读取图片
//filename:path+file name
//buffer:store image data
int read_image(char* filename,char* buffer){
    if(filename==NULL||buffer==NULL) return -1;
    FILE *fp=fopen(filename,"rb");
    if(fp==NULL){
        printf("fopen faild\n");
        return -2;
    }
    //file size
    fseek(fp,0,SEEK_END);//把文件指针置到末尾
    int length=ftell(fp);//返回当前文件流的指针位置，也就是偏移量，文件大小file size 
    fseek(fp,0,SEEK_SET);//把文件指针置到开头
    int size=fread(buffer,1,length,fp);//每次读1个字节，读length次。读取的参数放到buffer里
    if(size!=length){
        printf("fread faild\n");
        return -3;
    }
    fclose(fp);
    return size;
}

//图片写入到磁盘（参数1：保存的文件名 参数2：要写的数据   参数3：数据长度）
int write_image(char* filename,char* buffer,int length){
    if(filename==NULL||buffer==NULL||length<=0) return -1;
    FILE *fp=fopen(filename,"wb+");//w表示写入 b表示二进制 +表示，如果文件不存在则会创建，存在则会直接写入
    if(fp==NULL){
        printf("fopen faild\n");
        return -2;
    }
    int size=fwrite(buffer,1,length,fp);//从buffer写到fp中,每次写1个字节，写length次
    if(size!=length){
        printf("fwirte failded:%d\n",size);
        return -3;
    }
    fclose(fp);
    return size;
}

int mysql_write(MYSQL* handle,char* buffer,int length){
    if(handle==NULL||buffer==NULL||length<=0) return -1;

    MYSQL_STMT *stmt=mysql_stmt_init(handle);//在mysql中创建一个存储空间
    int ret=mysql_stmt_prepare(stmt,SQL_INSERT_IMG_USER,strlen(SQL_INSERT_IMG_USER));
    if(ret){
        printf("mysql_stmt_prepare:%s\n",mysql_error(handle));
        return -2;
    }
    MYSQL_BIND param={0};
    param.buffer_type=MYSQL_TYPE_LONG_BLOB;
    param.buffer=NULL;
    param.is_null=0;
    param.length=NULL;
    ret=mysql_stmt_bind_param(stmt,&param);
    if(ret){
        printf("mysql_stmt_bind_param:%s\n",mysql_error(handle));
        return -3;
    }
    ret=mysql_stmt_send_long_data(stmt,0,buffer,length);//允许应用程序分块地将参数数据发送到服务器
    if(ret){
        printf("mysql_stmt_send_long_data:%s\n",mysql_error(handle));
        return -4;
    }
    ret=mysql_stmt_execute(stmt);//将当前绑定的参数标记符的值发送到服务器，服务器用新提供的数据替换标记符
    if(ret){
        printf("mysql_stmt_execute:%s\n",mysql_error(handle));
        return -5;
    }
    ret=mysql_stmt_close(stmt);
    if(ret){
        printf("mysql_stmt_close:%s\n",mysql_error(handle));
        return -6;
    }
    return ret;
}

int mysql_read(MYSQL* handle,char* buffer,int length){
    if(handle==NULL||buffer==NULL||length<=0) return -1;

    MYSQL_STMT *stmt=mysql_stmt_init(handle);//在mysql中创建一个存储空间
    int ret=mysql_stmt_prepare(stmt,SQL_SELECT_IMG_USER,strlen(SQL_SELECT_IMG_USER));
    if(ret){
        printf("mysql_stmt_prepare:%s\n",mysql_error(handle));
        return -2;
    }

    MYSQL_BIND result={0};

    result.buffer_type=MYSQL_TYPE_LONG_BLOB;
    unsigned long total_length=0;
    result.length=&total_length;

    ret=mysql_stmt_bind_result(stmt,&result);
    if(ret){
        printf("mysql_stmt_bind_result:%s\n",mysql_error(handle));
        return -3;
    }
    ret=mysql_stmt_execute(stmt);//执行后，长度数据会存储到total_length中
    if(ret){
        printf("mysql_stmt_execute:%s\n",mysql_error(handle));
        return -4;
    }

    //数据从管道里拿出来
    ret=mysql_stmt_store_result(stmt);
    if(ret){
        printf("mysql_stmt_store_result:%s\n",mysql_error(handle));
        return -5;
    }

    while(1){
        ret=mysql_stmt_fetch(stmt);
        if(ret!=0&&ret!=MYSQL_DATA_TRUNCATED) break;
        int start=0;
        while(start<(int)total_length){
            result.buffer=buffer+start;
            result.buffer_length=1;//每次读取得长度为1
            mysql_stmt_fetch_column(stmt,&result,0,start);
            start+=result.buffer_length;
        }
    }
    mysql_stmt_close(stmt);
    return total_length;
}

int main(){
    MYSQL mysql;
    if(!mysql_init(&mysql)){//mysql初始化并判断是否出错(返回0为失败)
        printf("mysql_init:%s\n",mysql_error(&mysql));//mysql_error() 函数返回上一个 MySQL 操作产生的文本错误信息
        return -1;
    }
    if(!mysql_real_connect(&mysql,KING_DB_SERVER_IP,KING_DB_USERNAME,KING_DB_PASSWORD, 
    KING_DB_DEFAULTDB,KING_DB_SERVER_PORT,NULL,0)){ //连接mysql数据库，并判断是否出错(返回0为失败)
        printf("mysql_real_connect:%s\n",mysql_error(&mysql));
        return -2;
    }
    
    printf("case:mysql --> read image and write mysql\n");
    char buffer[FILE_IMAGE_LENGTH]={0};
    int length = read_image("0voice.jpg",buffer);
    if(length<0) goto Exit;
    mysql_write(&mysql,buffer,length);
    printf("case:mysql-->read mysql and write image\n");
    memset(buffer,0,FILE_IMAGE_LENGTH);
    length=mysql_read(&mysql,buffer,FILE_IMAGE_LENGTH);

    write_image("a.jpg",buffer,length);


Exit:
    mysql_close(&mysql);
    return 0;
}