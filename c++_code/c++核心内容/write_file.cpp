#include<iostream>
#include<fstream>
using namespace std;


int main(){
    ofstream ofs;
    ofs.open("1.txt",ios::out);
    ofs<<"caonima";
    ofs.close();

    system("pause");
    return 0;
}