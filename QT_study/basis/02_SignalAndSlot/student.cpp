#include "student.h"
#include<QDebug>
Student::Student(QObject *parent)
    : QObject{parent}
{

}

void Student::treat()
{
    qDebug()<<"Invite the teacher to dinner";
}

void Student::treat(QString foodName)
{
    //QString 转成 char* 先转成QByteArray(.toUtf8())  再转char* (.data())

    qDebug()<<"Invite the teacher to eat "<<foodName.toUtf8().data();
}
