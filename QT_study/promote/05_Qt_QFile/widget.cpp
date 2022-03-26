#include "widget.h"
#include "./ui_widget.h"
#include<QFileDialog>
#include<QFile>
#include<QTextCodec>//要在cmakelist中添加相应的内容
#include<QFileInfo>
#include<QDebug>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    //点击选取按钮，弹出文件对话框
    connect(ui->pushButton,&QPushButton::clicked,[=](){
        QString path = QFileDialog::getOpenFileName(this,"打开文件","C:\\Users\\xuheding\\Desktop");
        //将路径放到lineEdit中
        ui->lineEdit->setText(path);

//        //编码格式类
//        QTextCodec *codec=QTextCodec::codecForName("gbk");//对于gbk编码，后续array转为utf-8。codec->toUnicode(array)

        //读取内容  放入到textEdit中
        //QFile默认支持的格式是utf-8
        QFile file(path);//参数就是读取文件的路径
        //设置打开方式(只读)
        file.open(QIODeviceBase::ReadOnly);

//        QByteArray array = file.readAll();
        QByteArray array;
        while(!file.atEnd()){
            array+=file.readLine();//按行读
        }

        //将读取的数据  放入到textEdit中
        ui->textEdit->setText(array);

        //对文件对象进行关闭
        file.close();

//        //进行写文件
//        file.open(QIODevice::Append);//用追加的方式写
//        file.write("啊啊啊啊啊");
//        file.close();


        //QFileInfo
        QFileInfo info(path);
        qDebug()<<"file size"<<info.size();//文件大小
        qDebug()<<"suffix"<<info.suffix();//文件后缀
        qDebug()<<"file name"<<info.fileName();//文件名
        qDebug()<<"file path"<<info.filePath();//文件路径

        qDebug()<<"create date"<<info.birthTime().toString("yyyy/MM/dd hh:mm:ss");//文件的创建日期.(toString使用可以查看文档)
        qDebug()<<"modified date"<<info.lastModified().toString("yyyy/MM/dd hh:mm:ss");//文件最后修改日期



    });
}

Widget::~Widget()
{
    delete ui;
}

