#include<iostream>
using namespace std;
//全局函数做友元,只需要在类中声明一下友元函数
class Building{

    friend void goodGay(Building* building);
    friend void test();
    public:
    Building(){
        this->m_SittingRoom="客厅";
        this->m_BedRoom="卧室";
    }
    public:
        string m_SittingRoom;
    private:
        string m_BedRoom;
        static int age;
};
int Building::age = 10;

//加了友元后，可以访问私有成员属性了
void goodGay(Building* building){
    cout<<"好基友正在访问"<<building->m_SittingRoom<<endl;
    cout<<"好基友正在访问"<<building->m_BedRoom<<endl;
    cout<<building->age<<endl;
};
//加了友元后，可以访问私有静态变量了
void test(){
    cout<<Building::age<<endl;
}

int main(){
    Building building;
    goodGay(&building);
    system("pause");
    return 0;
}