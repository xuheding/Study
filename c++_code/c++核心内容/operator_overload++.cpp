#include<iostream>
using namespace std;

class MyInteger{
    friend ostream& operator<<(ostream& out,const MyInteger& myint);
    public:
        MyInteger(){
            m_Num=0;
        }
        //Ç°ÖÃ++
        MyInteger& operator++(){
            m_Num++;
            return *this;
        }
        //ºóÖÃ++
        MyInteger operator++(int){
            MyInteger tmp = *this;
            m_Num++;
            return tmp;
        }
    private:
        int m_Num;

};
ostream& operator<<(ostream& out,const MyInteger& myint){
    out<<myint.m_Num;
    return out;
}
int main(){
    MyInteger mynum;
    cout<<(mynum++)<<endl;
    cout<<++mynum<<endl;

    system("pause");
    return 0;
}