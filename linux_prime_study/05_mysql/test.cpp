#include<mysql.h>
#include<stdio.h>
#include<string.h>

#define SQL_INSERT_IMG_USER "INSERT TBL_USER(U_NAME,U_GENDER,U_IMG) VALUE('Dog','man',?);"

int read_image(char* filename,char* buffer){
    if(filename==NULL||buffer==NULL) return -1;
    FILE* fp=fopen(filename,"rb");
    if(fp==NULL) return -2;
    fseek(fp,0,SEEK_END);
    int length=ftell(fp);
    fseek(fp,0,SEEK_SET);
    int size=fread(buffer,1,length,fp);
    if(length!=size) return -3;
    fclose(fp);
    return size;
}

int write_image(char* filename,char* buffer,int length){
    if(filename==NULL||buffer==NULL||length<0) return -1;
    FILE* fp=fopen(filename,"wb+");
    int size=fwrite(buffer,1,length,fp);
    if(size!=length) return -2;
    fclose(fp);
    return size;
}
int mysql_write(MYSQL* handle,char* buffer,int length){
    if(handle==NULL||buffer==NULL||length<0) return -1;
    MYSQL_STMT *stmt=mysql_stmt_init(handle);
    mysql_stmt_prepare(stmt,SQL_INSERT_IMG_USER,strlen(SQL_INSERT_IMG_USER));
    MYSQL_BIND param={0};
    param.buffer_type=MYSQL_TYPE_LONG_BLOB;
    param.buffer=NULL;
    param.is_null=0;
    param.length=NULL;
    mysql_stmt_bind_param(stmt,&param);
    mysql_stmt_send_long_data(stmt,0,buffer,length);
    mysql_stmt_execute(stmt);
    mysql_stmt_close(stmt);
    return 0;
}
int mysql_read(MYSQL* handle,char* buffer,int length){
    if(handle==NULL||buffer==NULL||length<0) return -1;
    MYSQL_STMT *stmt=mysql_stmt_init(handle);
    mysql_stmt_prepare(stmt,SQL_INSERT_IMG_USER,strlen(SQL_INSERT_IMG_USER));
}

int main(){

}