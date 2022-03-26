#include<iostream>
#include<string>
using namespace std;

class Person{
    public:
        static int age;
        static int sex;
        static void getSex(){
            if(sex==0){
                cout<<"male"<<endl;
            }
            else{
                cout<<"female"<<endl;
            }
        }
        string address;
        Person(string address){
            this->address=address;
        };
};
int Person::age=10;
int Person::sex=0;

void test01(){
    Person p1("dog");
    cout<<p1.age<<endl;
    cout<<p1.address<<endl;
    cout<<Person::age<<endl;
}
int main(){
    test01();
    system("pause");
    return 0;
}