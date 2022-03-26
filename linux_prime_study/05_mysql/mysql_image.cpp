#include<mysql.h>
#include<stdio.h>
#include<string.h>


#define KING_DB_SERVER_IP "192.168.192.128" //ip
#define KING_DB_SERVER_PORT 3306            //�˿ں�
#define KING_DB_USERNAME "admin"            //�û���
#define KING_DB_PASSWORD "123456"           //����
#define KING_DB_DEFAULTDB "KING_DB"         //���ݿ���

//����ͼƬ��SQL��䣬���ڲ�֪�������ͼƬ��ʲô���ã���Ϊռλ��
#define SQL_INSERT_IMG_USER "insert TBL_USER(U_NAME,U_GENDER,U_IMG) value('Dog','man',?);"  

#define SQL_SELECT_IMG_USER "SELECT U_IMG FROM TBL_USER WHERE U_NAME='Dog';"
#define FILE_IMAGE_LENGTH (64*1024)



//��ȡͼƬ
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
    fseek(fp,0,SEEK_END);//���ļ�ָ���õ�ĩβ
    int length=ftell(fp);//���ص�ǰ�ļ�����ָ��λ�ã�Ҳ����ƫ�������ļ���Сfile size 
    fseek(fp,0,SEEK_SET);//���ļ�ָ���õ���ͷ
    int size=fread(buffer,1,length,fp);//ÿ�ζ�1���ֽڣ���length�Ρ���ȡ�Ĳ����ŵ�buffer��
    if(size!=length){
        printf("fread faild\n");
        return -3;
    }
    fclose(fp);
    return size;
}

//ͼƬд�뵽���̣�����1��������ļ��� ����2��Ҫд������   ����3�����ݳ��ȣ�
int write_image(char* filename,char* buffer,int length){
    if(filename==NULL||buffer==NULL||length<=0) return -1;
    FILE *fp=fopen(filename,"wb+");//w��ʾд�� b��ʾ������ +��ʾ������ļ���������ᴴ�����������ֱ��д��
    if(fp==NULL){
        printf("fopen faild\n");
        return -2;
    }
    int size=fwrite(buffer,1,length,fp);//��bufferд��fp��,ÿ��д1���ֽڣ�дlength��
    if(size!=length){
        printf("fwirte failded:%d\n",size);
        return -3;
    }
    fclose(fp);
    return size;
}

int mysql_write(MYSQL* handle,char* buffer,int length){
    if(handle==NULL||buffer==NULL||length<=0) return -1;

    MYSQL_STMT *stmt=mysql_stmt_init(handle);//��mysql�д���һ���洢�ռ�
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
    ret=mysql_stmt_send_long_data(stmt,0,buffer,length);//����Ӧ�ó���ֿ�ؽ��������ݷ��͵�������
    if(ret){
        printf("mysql_stmt_send_long_data:%s\n",mysql_error(handle));
        return -4;
    }
    ret=mysql_stmt_execute(stmt);//����ǰ�󶨵Ĳ�����Ƿ���ֵ���͵��������������������ṩ�������滻��Ƿ�
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

    MYSQL_STMT *stmt=mysql_stmt_init(handle);//��mysql�д���һ���洢�ռ�
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
    ret=mysql_stmt_execute(stmt);//ִ�к󣬳������ݻ�洢��total_length��
    if(ret){
        printf("mysql_stmt_execute:%s\n",mysql_error(handle));
        return -4;
    }

    //���ݴӹܵ����ó���
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
            result.buffer_length=1;//ÿ�ζ�ȡ�ó���Ϊ1
            mysql_stmt_fetch_column(stmt,&result,0,start);
            start+=result.buffer_length;
        }
    }
    mysql_stmt_close(stmt);
    return total_length;
}

int main(){
    MYSQL mysql;
    if(!mysql_init(&mysql)){//mysql��ʼ�����ж��Ƿ����(����0Ϊʧ��)
        printf("mysql_init:%s\n",mysql_error(&mysql));//mysql_error() ����������һ�� MySQL �����������ı�������Ϣ
        return -1;
    }
    if(!mysql_real_connect(&mysql,KING_DB_SERVER_IP,KING_DB_USERNAME,KING_DB_PASSWORD, 
    KING_DB_DEFAULTDB,KING_DB_SERVER_PORT,NULL,0)){ //����mysql���ݿ⣬���ж��Ƿ����(����0Ϊʧ��)
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