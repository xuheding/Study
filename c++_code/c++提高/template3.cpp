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

//��ͨ����ģ��
template<class T>
bool myCompare(T& a,T& b){
    if(a==b){
        return true;
    }
    else{
        return false;
    }
}
//���廯��ģ��(��template<>��ͷ)
//���廯�����ڳ���ģ��
template<> bool myCompare(Person& p1,Person& p2){
    if(p1.m_age==p2.m_age){
        return true;
    }
    else{
        return false;
    }
}

int main(){
    Person p1("����",10);
    Person p2("����",10);
    bool ret = myCompare(p1,p2);
    cout<<ret<<endl;
    system("pause");
    return 0;
}