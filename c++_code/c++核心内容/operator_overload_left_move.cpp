#include<iostream>
using namespace std;

class Person{
    friend ostream& operator<<(ostream& out,const Person& p);
    public:
        Person(int a,int b){
            this->m_A=a;
            this->m_B=b;
        };
        //成员函数 实现不了  p << cout 不是我们想要的效果
	    //void operator<<(Person& p){
	    //}
    private:
        int m_A;
        int m_B;
};

ostream& operator<<(ostream& out,const Person& p){
    out<<"a"<<p.m_A<<"b"<<p.m_B;
    return out;
}

void test(){
    Person p1(10,20);
    cout<<p1<<endl;

}
int main(){
    test();
    system("pause");
    return 0;
}