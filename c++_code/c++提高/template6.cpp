#include<iostream>
using namespace std;


template<class T>
class Base{
    T m;
};
//(������಻��ģ����)����ָ��һ������
class Son:public Base<int>{
};

//��ģ��̳���ģ�� ,������T2ָ�������е�T����
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