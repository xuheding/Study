#include<string>
#include<iostream>
using namespace std;

//头部插入
#define LIST_INSERT(item,list) do{  \
    item->prev=nullptr;             \
    item->next=list;                \
    list=item;                      \
}while(0)

//删除节点（如果指只剩下一个节点的时候要特殊考虑）
#define LIST_REMOVE(item,list) do{    \
    if(item->prev!=NULL) item->prev->next=item->next; \
    if(item->next!=NULL) item->next->prev=item->prev; \
    if(list==item) list=item->next; \
    item->prev=item->next=nullptr; \
}while(0)

struct Person{
    string name;
    string phone;
    Person *next;
    Person *prev;
};
struct Contacts{
    Person *people;
    int count;
};


int person_insert(Person *people,Person *ps){
    if(ps==nullptr) return -1;
    LIST_INSERT(ps,people);
    return 0;
}
int person_delete(Person *people,Person *ps){
    if(ps==nullptr) return -1;
    LIST_REMOVE(ps,people);
    return 0;
}
Person* person_search(Person *people,string& name){
    for(Person *item=people;item!=nullptr;item=item->next){
        if(item->name==name) return item;
    }
    return nullptr;
}
int person_travesal(Person *people,Person *ps){
    for(Person* item=people;item!=nullptr;item=item->next){
        cout<<"name:"<<item->name<<" phone:"<<item->phone;
    }   
    return 0;
}

enum{
    OPEN_INSERT=1,
    OPEN_PRINT,
    OPEN_DELETE,
    OPEN_SEARCH,
    OPEN_SAVE,
    OPEN_LOAD
};
int main(){
    while (1)
    {
        int select;
        cin>>select;
        switch(select){
            case OPEN_INSERT:
                break;
            case OPEN_PRINT:
                break;
            case OPEN_DELETE:
                break;
            case OPEN_SEARCH:
                break;
            case OPEN_SAVE:
                break;
            case OPEN_LOAD:
                break;
        }
    }
    
}