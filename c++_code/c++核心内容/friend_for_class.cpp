#include<iostream>
using namespace std;
//������Ԫ
class Building;//����

class goodGay{
    public:
        goodGay();
        void visit();
    private:
        Building* building;
};
class Building{
    friend class goodGay;//��������Ԫ,�����Ӿȶ��Ǹ���goodGay�з���building��˽������
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
    cout<<"���ڷ���"<<building->m_Sittingroom<<endl;
    cout<<"���ڷ���"<<building->m_Bedroom<<endl;
}
Building::Building(){
    this->m_Sittingroom="����";
    this->m_Bedroom="����";
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