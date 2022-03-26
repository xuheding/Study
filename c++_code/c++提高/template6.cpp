#include<iostream>
using namespace std;


template<class T>
class Base{
    T m;
};
//(如果子类不是模板类)必须指定一个类型
class Son:public Base<int>{
};

//类模板继承类模板 ,可以用T2指定父类中的T类型
template<class T1,class T2>
class Son2:public Base<T1>{
    public:
        Son2(){
            cout<<typeid(T1).name()<<endl;
            cout<<typeid(T2).name()<<endl;
        }
        
};





int main(){
    Son2<int,char> son;
    

    system("pause");
    return 0;
}