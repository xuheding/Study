#include<mysql.h>
#include<stdio.h>
#include<string.h>

#define KING_DB_SERVER_IP "192.168.192.128" //ip
#define KING_DB_SERVER_PORT 3306            //�˿ں�
#define KING_DB_USERNAME "admin"            //�û���
#define KING_DB_PASSWORD "123456"           //����
#define KING_DB_DEFAULTDB "KING_DB"         //���ݿ���

//SQL���
#define SQL_INSERT_TBL_USER "insert TBL_USER(U_NAME,U_GENDER) value('Dog','man');"  
#define SQL_SELECT_TBL_USER "select * from TBL_USER;"
#define SQL_DELETE_TBL_USER "CALL PROC_DELETE_USER('Dog');"

//////******��ѯ******///////////
//��һ����Ҫ��sql��䷢�͸�mysql������
//�ڶ�������mysql���������������ܻ���,������
//�����������ܵ�����(�ж϶����ж�����)
//���Ĳ���ץȡ������Ҫ������ 
int king_mysql_select(MYSQL* handle){
    //mysql_real_query--->sql
    if(mysql_real_query(handle,SQL_SELECT_TBL_USER,strlen(SQL_SELECT_TBL_USER))){ //(����0Ϊ�ɹ�)
        printf("mysql_real_query:%s\n",mysql_error(handle));
        return -1;
    }
    //store    ����ѯ���ִ����֮�����ݾ��Ѿ����յ��˹ܵ������ݣ�mysql���������͵ģ�,���Ҫ�洢����
    MYSQL_RES *res=mysql_store_result(handle);
    if(res==NULL){
        printf("mysql_store_result:%s\n",mysql_error(handle));
        return -2;
    }
    //rows/fields  ��/��
    int rows=mysql_num_rows(res);
    printf("rows:%d\n",rows);
    int fields = mysql_num_fields(res);
    printf("fields:%d\n",fields);
    //fetch
    MYSQL_ROW row;//����һ�е�����
    while(row=mysql_fetch_row(res)){
        for(int i=0;i<fields;i++){
            printf("%s\t",row[i]);
        }
        printf("\n");
    }


    mysql_free_result(res);
    return 0;
}



//C U R D  //create update read delete   ��˵�еģ���ɾ�Ĳ�
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
    
    
#if 1
    //Mysql->select
    king_mysql_select(&mysql);
#endif

#if 1
    //Mysql -->insert
    if(mysql_real_query(&mysql,SQL_INSERT_TBL_USER,strlen(SQL_INSERT_TBL_USER))){ //(����0Ϊ�ɹ�)
        printf("mysql_real_query:%s\n",mysql_error(&mysql));
    }
    king_mysql_select(&mysql);
#endif

#if 1
    //mysql-->delete
    if(mysql_real_query(&mysql,SQL_DELETE_TBL_USER,strlen(SQL_DELETE_TBL_USER))){ //(����0Ϊ�ɹ�)
        printf("mysql_real_query:%s\n",mysql_error(&mysql));
    }
    king_mysql_select(&mysql);
#endif

    mysql_close(&mysql);
    return 0;
}

