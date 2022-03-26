#include<iostream>
using namespace std;

class Animal{
    public:
        virtual void speak(){
            cout<<"动物叫声"<<endl;
        }
};
class Cat:public Animal{
    public:
        void speak(){
            cout<<"猫叫声"<<endl;
        }
};
class Dog:public Animal{
    public:
        void speak(){
            cout<<"狗叫声"<<endl;
        }
};
class Tigger:public Animal{
    public:
};


void dospeak(Animal& animal){//用一个统一的接口，可以实现不同的状态，称为多态
    animal.speak();
}

//虽然不加虚函数也可以实现重写，但是加了之后，才能使用统一的接口(传入Animal类型)

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