#include<iostream>
using namespace std;
//实现通用 对数组进行排序的函数
//规则 从大到小
//算法 选择排序
//测试 char数组 int数组

//选择排序
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

//测试char数组
void test01(){
    char charArr[]="badcfe";
    int num = sizeof(charArr)/sizeof(char);
    mySort(charArr,num);
    printArray(charArr,num);

    
}
//测试int数组
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