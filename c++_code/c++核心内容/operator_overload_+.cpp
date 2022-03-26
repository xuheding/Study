#include<iostream>
using namespace std;

class Person{
    public:
        Person(){};
        Person(int a,int b){
            this->m_A=a;
            this->m_B=b;
        }
        Person operator+(const Person& p){
            Person tmp;
            tmp.m_A=this->m_A+p.m_A;
            tmp.m_B=this->m_B+p.m_B;
            return tmp;
        }
    public:
        int m_A;
        int m_B;
};
Person operator+(const Person&p,int val){
    Person tmp;
    tmp.m_A = p.m_A+val;
    tmp.m_B = p.m_B+val;
    return tmp;
}
void test(){
    Person p1(10,20);
    Person p2(15,25);
    Person p3=p1+p2;
    cout<<p3.m_A<<endl;
    cout<<p3.m_B<<endl;
    Person p4=p1+11;
    cout<<p4.m_A<<endl;
    cout<<p4.m_B<<endl;
}
int main(){
    
    test();


    system("pause");
    return 0;
}