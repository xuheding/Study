#include<iostream>
using namespace std;
//ȫ�ֺ�������Ԫ,ֻ��Ҫ����������һ����Ԫ����
class Building{

    friend void goodGay(Building* building);
    friend void test();
    public:
    Building(){
        this->m_SittingRoom="����";
        this->m_BedRoom="����";
    }
    public:
        string m_SittingRoom;
    private:
        string m_BedRoom;
        static int age;
};
int Building::age = 10;

//������Ԫ�󣬿��Է���˽�г�Ա������
void goodGay(Building* building){
    cout<<"�û������ڷ���"<<building->m_SittingRoom<<endl;
    cout<<"�û������ڷ���"<<building->m_BedRoom<<endl;
    cout<<building->age<<endl;
};
//������Ԫ�󣬿��Է���˽�о�̬������
void test(){
    cout<<Building::age<<endl;
}

int main(){
    Building building;
    goodGay(&building);
    system("pause");
    return 0;
}