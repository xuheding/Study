#include<iostream>
using namespace std;

//类模板
template<class NameType,class AgeType>
class Person{
    public:
        Person(NameType name,AgeType age);
        void showPerson(){
            cout<<"name:"<<this->m_Name<<"age:"<<this->m_age<<endl;
        }
        NameType m_Name;
        AgeType m_age;
};

//构造函数  类外实现
template<class NameType,class AgeType>
Person<NameType,AgeType>::Person(NameType name,AgeType age){
            this->m_Name=name;
            this->m_age=age;
        }

void test01(){
    Person<string,int> p1("张三",10);
    p1.showPerson();
}

int main(){
    test01();
    system("pause");
    return 0;
}