#include<iostream>
using namespace std;
//ʵ��ͨ�� �������������ĺ���
//���� �Ӵ�С
//�㷨 ѡ������
//���� char���� int����

//ѡ������
template<class T>
void mySort(T arr[],int len){
    for(int i=0;i<len;i++){
        int max = i;
        for(int j=i+1;j<len;j++){
            if(arr[j]>arr[max]){
                max=j;
            }
        }
        swap<T>(arr[max],arr[i]);
    }
}


template<class T>
void printArray(T arr[],int len){
    for(int i=0;i<len;i++){
        cout<<arr[i]<<" ";
    }
    cout<<endl;
}

//����char����
void test01(){
    char charArr[]="badcfe";
    int num = sizeof(charArr)/sizeof(char);
    mySort(charArr,num);
    printArray(charArr,num);

    
}
//����int����
void test02(){
    int intArr[]={7,5,1,3,9,2,4,6,8};
    int num=sizeof(intArr)/sizeof(int);
    mySort(intArr,num);
    printArray(intArr,num);
}


int main(){
    
    test01();
    test02();
    system("pause");
    return 0;
}