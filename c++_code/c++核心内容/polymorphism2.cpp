#include<iostream>
using namespace std;

//��̬ʵ��-��������
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
            cout<<"��ˮ"<<endl;
        }
        void brew(){
            cout<<"���ݿ���"<<endl;
        }
        void pourInCup(){
            cout<<"�ѿ��ȵ��뱭��"<<endl;
        }
        void PutSomething(){
            cout<<"���Ǻ�ţ��"<<endl;
        }
};
class Tea:public AbstractDrinking{
    public:
        void boil(){
            cout<<"��ˮ"<<endl;
        }
        void brew(){
            cout<<"���ݲ�Ҷ"<<endl;
        }
        void pourInCup(){
            cout<<"�Ѳ�Ҷ���뱭����"<<endl;
        }
        void PutSomething(){
            cout<<"������"<<endl;
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