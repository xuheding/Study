#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

void Myprint(int val){
    cout<<val<<endl;
}
void test01(){
    //��������
    vector<int> v;
    //�������з�����
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
    v.push_back(40);

    vector<int>::iterator pbegin = v.begin();
    vector<int>::iterator pend = v.end();


    //��һ�ֱ�������
    while(pbegin!=pend){
        cout<<*pbegin<<endl;
        pbegin++;
    }
    //�ڶ��±�������
    for(vector<int>::iterator it=v.begin();it!=v.end();it++){
        cout<<*it<<endl;
    }
    //�����±�������
    for_each(v.begin(),v.end(),Myprint);

}

int main(){
    test01();
    system("pause");
    return 0;
}