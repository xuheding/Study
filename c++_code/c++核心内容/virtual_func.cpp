#include<iostream>
using namespace std;

class Animal{
    public:
        virtual void speak(){
            cout<<"�������"<<endl;
        }
};
class Cat:public Animal{
    public:
        void speak(){
            cout<<"è����"<<endl;
        }
};
class Dog:public Animal{
    public:
        void speak(){
            cout<<"������"<<endl;
        }
};
class Tigger:public Animal{
    public:
};


void dospeak(Animal& animal){//��һ��ͳһ�Ľӿڣ�����ʵ�ֲ�ͬ��״̬����Ϊ��̬
    animal.speak();
}

//��Ȼ�����麯��Ҳ����ʵ����д�����Ǽ���֮�󣬲���ʹ��ͳһ�Ľӿ�(����Animal����)

int main(){
    
    Cat cat;
    Dog dog;
    Tigger tigger;
    dospeak(cat);
    dospeak(dog);
    dospeak(tigger);
    system("pause");
    return 0;
}