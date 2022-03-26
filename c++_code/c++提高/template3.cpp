#include<iostream>
using namespace std;

class Person{
    public:
        Person(string name,int age){
            this->m_name = name;
            this->m_age = age;
        }
        string m_name;
        int m_age;
};

//普通函数模板
template<class T>
bool myCompare(T& a,T& b){
    if(a==b){
        return true;
    }
    else{
        return false;
    }
}
//具体化的模板(以template<>开头)
//具体化优先于常规模板
template<> bool myCompare(Person& p1,Person& p2){
    if(p1.m_age==p2.m_age){
        return true;
    }
    else{
        return false;
    }
}

int main(){
    Person p1("张三",10);
    Person p2("李四",10);
    bool ret = myCompare(p1,p2);
    cout<<ret<<endl;
    system("pause");
    return 0;
}