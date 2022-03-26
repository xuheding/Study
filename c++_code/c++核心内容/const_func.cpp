#include<iostream>
using namespace std;

class Person{
    public:
        Person(){
            m_A=0;
            m_B=0;
        }
        void showPerson() const{
            this->m_B=100;
            // this->m_A=100;//涓嶅彲浠ヤ慨鏀规垚鍛樺睘鎬�,鍙兘淇敼mutable淇グ鐨�
        }

    public:
        int m_A;
        mutable int m_B;

};


int main(){
    system("pause");
    return 0;
}