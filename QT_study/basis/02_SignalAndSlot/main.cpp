#include "widget.h"

#include <QApplication>


//需求:
//Teacher类  老师类
//Student类  学生类
//下课后，老师会触发一个型号，饿了，学生响应信号，请客吃饭
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();
}
