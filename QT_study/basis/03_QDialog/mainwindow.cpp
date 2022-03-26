#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include<QDialog>
#include<QDebug>
#include<QMessageBox>
#include<QColorDialog>
#include<QFileDialog>
#include<QFontDialog>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //点击新建按钮 弹出一个对话框
    connect(ui->actionnew,&QAction::triggered,[=](){//点击新建，触发对话框
        //对话框 分类：模态对话框、非模态对话框
        //模态对话框（弹出后，不可以对其他窗口进行操作）    非模态对话框（弹出后,可以对其他窗口进行操作）

//        //模态对话框创建（阻塞）
//        QDialog dlg(this); // 放到栈上，当局部事件结束后，会自动释放
//        dlg.resize(200,100);//调整对话框大小
//        dlg.exec();//进行阻塞(进行消息循环)
//        qDebug()<<"Model dialog pops up";


//        //非模态对话框创建
//        QDialog *dlg2 = new QDialog(this);//要放到堆上，不然由于没有阻塞，会一闪而过。
//        dlg2->show();
//        dlg2->setAttribute(Qt::WA_DeleteOnClose);//如果点击了关闭按钮，会自动释放空间(看setAttribute文档),（不然的话，用户一直点击新建，就会出现内存泄漏）
//        qDebug()<<"Non-model dialog pops up";

//        //消息对话框

//        //错误对话框
//        QMessageBox::critical(this,"critical","错误");

//        //信息对话框
//        QMessageBox::information(this,"info","信息");

//        //提问对话框（参数1：父亲， 参数2：标题， 参数3：提示内容， 参数4：按键类型， 参数5：默认关联回车按键   返回值：点击的按钮的枚举值）
//        QMessageBox::StandardButton ans = QMessageBox::question(this,"ques","提问",QMessageBox::Save|QMessageBox::Cancel,QMessageBox::Cancel);
//        if(ans==QMessageBox::Save) qDebug()<<"chose to save";
//        else qDebug()<<"save to cancel";

//        //警告对话框
//        QMessageBox::warning(this,"warning","警告");

        //其他标准对话框

//        //颜色对话框
//        QColor color = QColorDialog::getColor(QColor(255,0,0));//默认用红色打开
//        qDebug()<<"r="<<color.red()<<" g="<<color.green()<<" b="<<color.blue();

//        //文件对话框(参数1：父亲， 参数2：标题， 参数3：默认打开路径， 参数4：过滤文件格式   返回值:选取的路径)
//        QString path = QFileDialog::getOpenFileName(this,"打开文件","C:\\Users\\xuheding\\Desktop","(*.txt)");
//        qDebug()<<path;

        //字体对话框
        bool flag;
        QFont font = QFontDialog::getFont(&flag,QFont("华文彩云",36));//默认以华文彩云，36号字体打开。（具体有哪些字体，看系统带了哪些）
        qDebug()<<"字体:"<<font.family().toUtf8().data()<<"字号:"<<font.pointSize()<<"是否加粗"<<font.bold()<<"是否倾斜"<<font.italic();


    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

