#include<iostream>
using namespace std;


//空指针可以访问  静态成员变量和  函数
//(因为只有非静态成员变量存储在对象中,其他的存储在别的地方)
class Person{
    public:
        static int age;
        
        void show(){
            cout<<"this is func"<<endl;
        }
};
int Person::age=10;

int main(){
    Person* p=NULL;

    cout<<p->age<<endl;
    p->show();

    system("pause");
    return 0;
}