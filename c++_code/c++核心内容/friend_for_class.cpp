#include<iostream>
using namespace std;
//类作友元
class Building;//声明

class goodGay{
    public:
        goodGay();
        void visit();
    private:
        Building* building;
};
class Building{
    friend class goodGay;//声明类友元,这样子救恩那个在goodGay中访问building的私有属性
    public:
        Building();
    public:
        string m_Sittingroom;
    private:
        string m_Bedroom;
};
goodGay::goodGay(){
    building = new Building;
}
void goodGay::visit(){
    cout<<"正在访问"<<building->m_Sittingroom<<endl;
    cout<<"正在访问"<<building->m_Bedroom<<endl;
}
Building::Building(){
    this->m_Sittingroom="客厅";
    this->m_Bedroom="卧室";
}
void test01(){
    goodGay gg;
    gg.visit();
}
int main(){
    test01();
    system("pause");
    return 0;
}