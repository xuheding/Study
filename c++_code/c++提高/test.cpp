

#include<iostream>
#include<string>
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

template<class T>
void printone(T& a){  
    cout<<a<<endl;
}

template<> void printone(Person& p){
    cout<<p.m_name<<endl;
    
}

int main(){
    int a=1;
    int b=3;
    printone(a);
    printone(b);
    Person p1("xhd",10);
    printone(p1);



    system("pause");
    return 0;
}