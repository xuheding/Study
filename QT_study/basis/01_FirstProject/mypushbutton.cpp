#include "mypushbutton.h"
#include<QDebug>

MyPushButton::MyPushButton(QPushButton *parent)
    : QPushButton{parent}
{
    qDebug()<<"myPushButton constructor";
}
MyPushButton::~MyPushButton()
{
    qDebug()<<"myPushButton destructor";
}
