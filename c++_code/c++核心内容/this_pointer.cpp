#include<iostream>
using namespace std;

//this指针返回 对象本身
class Person{
    public:
        Person(int age){
            this->age=age;
        }

        Person& addPerson(const Person& p){
            this->age+=p.age;
            return *this;
        }
        int age;
};


void test01(){
    Person p1(10);
    Person p2(20);
    
    p2.addPerson(p1).addPerson(p1);
    cout<<p2.age<<endl;

}

int main(){
    test01();
    system("pause");
    return 0;
}