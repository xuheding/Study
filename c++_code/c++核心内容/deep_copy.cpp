#include<iostream>
using namespace std;

class Person{
    public:
        Person(int age,int sex){
            this->age=new int(age);
            this->sex=new int(sex);
            cout<<"调用有参构造函数"<<endl;
        }
        Person(const Person& p){
            age = new int(*p.age);
            sex = new int(*p.sex);
            cout<<"调用拷贝构造函数"<<endl;
        }
        int getSex(){
            return *this->sex;
        }
        int getAge(){
            return *this->age;
        }
        ~Person(){
            cout<<"调用析构函数"<<endl;
            if(sex!=NULL) delete sex;
            if(age!=NULL) delete age;
        }
    private:
        int* age;
        int* sex;
};

void test01(){
    Person p1(10,1);
    Person p2(p1);
    cout<<p2.getAge()<<endl;
    cout<<p2.getSex()<<endl;
}


int main(){
    test01();
    system("pause");
    return 0;
}