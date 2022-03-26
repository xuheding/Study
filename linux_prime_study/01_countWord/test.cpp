#include<stdio.h>
#include<iostream>
using namespace std;

#define OUT 0
#define IN 1
#define INIT OUT

int count_word(char* filename){
    int status=INIT;
    FILE *fp=fopen(filename,"r");
    if(fp==NULL) return -1;
    char c;
    //只要统计由OUT变为IN的次数
    int word=0;
    while((c=fgetc(fp))!=EOF){
        if(!isalpha(c)){
            status=OUT;
        }
        else if(OUT==status){
            status=IN;
            word++;
        }
    }
    return word;
}


int main(int argc,char *argv[]){
    if(argc<2) return -1;
    printf("word:%d\n",count_word(argv[1]));
}