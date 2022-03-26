#include<mysql.h>
#include<stdio.h>
#include<string.h>

#define KING_DB_SERVER_IP "192.168.192.128" //ip
#define KING_DB_SERVER_PORT 3306            //端口号
#define KING_DB_USERNAME "admin"            //用户名
#define KING_DB_PASSWORD "123456"           //密码
#define KING_DB_DEFAULTDB "KING_DB"         //数据库名

//SQL语句
#define SQL_INSERT_TBL_USER "insert TBL_USER(U_NAME,U_GENDER) value('Dog','man');"  
#define SQL_SELECT_TBL_USER "select * from TBL_USER;"
#define SQL_DELETE_TBL_USER "CALL PROC_DELETE_USER('Dog');"

//////******查询******///////////
//第一步：要把sql语句发送给mysql服务器
//第二步：把mysql服务器处理结果接受回来,并保存
//第三步：接受的数据(判断多少行多少列)
//第四步：抓取我们想要的数据 
int king_mysql_select(MYSQL* handle){
    //mysql_real_query--->sql
    if(mysql_real_query(handle,SQL_SELECT_TBL_USER,strlen(SQL_SELECT_TBL_USER))){ //(返回0为成功)
        printf("mysql_real_query:%s\n",mysql_error(handle));
        return -1;
    }
    //store    当查询语句执行完之后，数据就已经接收到了管道的数据（mysql服务器发送的）,因此要存储起来
    MYSQL_RES *res=mysql_store_result(handle);
    if(res==NULL){
        printf("mysql_store_result:%s\n",mysql_error(handle));
        return -2;
    }
    //rows/fields  行/列
    int rows=mysql_num_rows(res);
    printf("rows:%d\n",rows);
    int fields = mysql_num_fields(res);
    printf("fields:%d\n",fields);
    //fetch
    MYSQL_ROW row;//定义一行的数据
    while(row=mysql_fetch_row(res)){
        for(int i=0;i<fields;i++){
            printf("%s\t",row[i]);
        }
        printf("\n");
    }


    mysql_free_result(res);
    return 0;
}



//C U R D  //create update read delete   传说中的：增删改查
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
    
    
#if 1
    //Mysql->select
    king_mysql_select(&mysql);
#endif

#if 1
    //Mysql -->insert
    if(mysql_real_query(&mysql,SQL_INSERT_TBL_USER,strlen(SQL_INSERT_TBL_USER))){ //(返回0为成功)
        printf("mysql_real_query:%s\n",mysql_error(&mysql));
    }
    king_mysql_select(&mysql);
#endif

#if 1
    //mysql-->delete
    if(mysql_real_query(&mysql,SQL_DELETE_TBL_USER,strlen(SQL_DELETE_TBL_USER))){ //(返回0为成功)
        printf("mysql_real_query:%s\n",mysql_error(&mysql));
    }
    king_mysql_select(&mysql);
#endif

    mysql_close(&mysql);
    return 0;
}

