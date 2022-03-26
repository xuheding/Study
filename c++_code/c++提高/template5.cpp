#include<iostream>
using namespace std;
//类模板对象做函数参数
template<class NameType,class AgeType>
class Person{
    public:
        Person(NameType name,AgeType age){
            this->m_name=name;
            this->m_age=age;
        }
        void showPerson(){
            cout<<"name"<<m_name<<endl;
            cout<<"age"<<m_age<<endl;
        }
    public:
        NameType m_name;
        AgeType m_age;
};
//1.传入指定类型
void printPerson1(Person<string,int>& p){
    p.showPerson();
}
//2.参数模板化
template<class T1,class T2>
void printPerson2(Person<T1,T2>& p){
    p.showPerson();
}
//3.整个类模板化
template<class T>
void printPerson3(T& p){
    p.showPerson();
}


int main(){

    



    system("pause");
    return 0;
}