#include<iostream>
using namespace std;

//多态实现计算器
class AbstractCalculator{
    public:
        virtual int getResult(){
            return 0;
        }
        AbstractCalculator(){
            this->num1=20;
            this->num2=5;
        }
        int num1;
        int num2;
};
class Add:public AbstractCalculator{
    public:
        int getResult(){
            return num1+num2;
        }
};
class Sub:public AbstractCalculator{
    public:
        int getResult(){
            return num1-num2;
        }
};
class Mul:public AbstractCalculator{
    public:
        int getResult(){
            return num1*num2;
        }
};
ostream& operator<<(ostream& out,const AbstractCalculator& abs){
    out<<"num1:"<<abs.num1<<endl;
    out<<"num2:"<<abs.num2;
    return out;
}

int main(){
    AbstractCalculator* abs = new Add;
    cout<<*abs<<endl;
    cout<<abs->getResult()<<endl;
    abs = new Sub;
    cout<<abs->getResult()<<endl;
    abs = new Mul;
    cout<<abs->getResult()<<endl;




    system("pause");
    return 0;
}