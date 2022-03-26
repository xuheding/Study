#include<iostream>
#include<fstream>
using namespace std;


int main(){
    ifstream ifs;
    ifs.open("1.txt",ios::in);
    
    char c;
    while((c=ifs.get())!=EOF){
        cout<<c;
    }
    ifs.close();
    

    system("pause");
    return 0;
}