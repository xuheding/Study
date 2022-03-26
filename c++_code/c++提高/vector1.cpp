#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

void Myprint(int val){
    cout<<val<<endl;
}
void test01(){
    //创建容器
    vector<int> v;
    //向容器中放数据
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
    v.push_back(40);

    vector<int>::iterator pbegin = v.begin();
    vector<int>::iterator pend = v.end();


    //第一种遍历方法
    while(pbegin!=pend){
        cout<<*pbegin<<endl;
        pbegin++;
    }
    //第二章遍历方法
    for(vector<int>::iterator it=v.begin();it!=v.end();it++){
        cout<<*it<<endl;
    }
    //第三章遍历方法
    for_each(v.begin(),v.end(),Myprint);

}

int main(){
    test01();
    system("pause");
    return 0;
}