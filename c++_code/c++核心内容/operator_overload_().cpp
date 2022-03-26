#include<iostream>
using namespace std;

class Myprint{
    public:
        void operator()(string name){
            cout<<name<<endl;
        }
};

int main(){
    Myprint print;
    print("hello world");


    system("pause");
    return 0;
}