#include<iostream>
using namespace std;

//多态实现-制作饮料
class AbstractDrinking{
    public:
        virtual void boil()=0;
        virtual void brew()=0;
        virtual void pourInCup()=0;
        virtual void PutSomething()=0;
    void MakeDrink(){
        boil();
        brew();
        pourInCup();
        PutSomething();
    }
};
class Coffe:public AbstractDrinking{
    public:
        void boil(){
            cout<<"煮水"<<endl;
        }
        void brew(){
            cout<<"冲泡咖啡"<<endl;
        }
        void pourInCup(){
            cout<<"把咖啡倒入杯中"<<endl;
        }
        void PutSomething(){
            cout<<"加糖和牛奶"<<endl;
        }
};
class Tea:public AbstractDrinking{
    public:
        void boil(){
            cout<<"煮水"<<endl;
        }
        void brew(){
            cout<<"冲泡茶叶"<<endl;
        }
        void pourInCup(){
            cout<<"把茶叶倒入杯子中"<<endl;
        }
        void PutSomething(){
            cout<<"加柠檬"<<endl;
        }
};

void drink(AbstractDrinking* abs){
    abs->MakeDrink();
    delete abs;
}
void test(){
    drink(new Coffe);
    // drink(new Tea);
}

int main(){
    
    test();
    system("pause");
    return 0;
}