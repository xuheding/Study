#include<iostream>
using namespace std;

template<typename T>//声明一个模板，告诉版一起后面代码中紧跟着的T不要报错，T是一个通用数据类型
//template<class T>  也是一样的
void Myswap(T& a,T& b){
    T temp=a;
    a=b;
    b=temp;
}


int main(){
    
    int a=10;
    int b=20;

    //两种方式使用函数模板
    //1.自动类型推导
    Myswap(a,b);
    //2.显示指定类型
    Myswap<int>(a,b);//尖括号指定上面T中的类型


    //模板的作用就是将类型参数化，在使用的时候再传入

    cout<<a<<endl;
    cout<<b<<endl;

    system("pause");
    return 0;
}