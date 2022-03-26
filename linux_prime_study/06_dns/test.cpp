#include<stdio.h>
#include<iostream>
#include<string.h>
#include<string>
#include<vector>
using namespace std;

#include<netinet/in.h>

// char* hostname2name(const char* hostname){
//     string s=(char*)hostname;
//     int i=0;
//     string res;
//     while(i<s.size()){
//         int start=i;
//         while(i<s.size()&&s[i]!='.') i++;
//         res+=to_string(i-start);
//         res+=s.substr(start,i-start);
//         while(i<s.size()&&s[i]=='.') i++;
//     }
//     res+='0';
//     char* name=(char*)malloc(res.size()+1);
//     for(int i=0;i<res.size();i++) name[i]=res[i];
//     name[res.size()]='\0';
//     return name;
// }

int main(){
    // const char* hostname=(char*)"www.0voice.com";
    // char* name=hostname2name(hostname);
    // cout<<name;
    cout<<"hello";
    cout<<int('\0');
}
