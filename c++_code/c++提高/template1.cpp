#include<iostream>
using namespace std;

template<typename T>//����һ��ģ�壬���߰�һ���������н����ŵ�T��Ҫ����T��һ��ͨ����������
//template<class T>  Ҳ��һ����
void Myswap(T& a,T& b){
    T temp=a;
    a=b;
    b=temp;
}


int main(){
    
    int a=10;
    int b=20;

    //���ַ�ʽʹ�ú���ģ��
    //1.�Զ������Ƶ�
    Myswap(a,b);
    //2.��ʾָ������
    Myswap<int>(a,b);//������ָ������T�е�����


    //ģ������þ��ǽ����Ͳ���������ʹ�õ�ʱ���ٴ���

    cout<<a<<endl;
    cout<<b<<endl;

    system("pause");
    return 0;
}