#include<iostream>
using namespace std;

class Person{
    public:
        Person(int age){
            m_Age = new int(age);
        }
        Person& operator=(Person& p){
            if(m_Age!=NULL){
                delete m_Age;
                m_Age=NULL;
            }
            m_Age=new int(*p.m_Age);
            return *this;
        }
        ~Person(){
            if(m_Age!=NULL){
                delete m_Age;
                m_Age=NULL;
            }
        }
    int *m_Age;
};
ostream& operator<<(ostream& out,const Person& p){
    out<<*p.m_Age;
    return out;
}
int main(){
    Person p1(18);
    Person p2(20);
    Person p3(30);

    p2=p3=p1;
    cout<<p1<<endl;
    cout<<p2<<endl;
    cout<<p3<<endl;



    system("pause");
    return 0;
}