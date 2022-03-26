#include<iostream>
#include<string>
#include<vector>
using namespace std;

class Point{
    public:
        void setX(int x){
            this->x=x;
        }
        int getX(){
            return x;
        }
        void setY(int y){
            this->y=y;
        }
        int getY(){
            return y;
        }
    private:
        int x;
        int y;
};

class Circle{
    public:
        void setCenter(Point& center){
            this->center = center;
        }
        Point getCenter(){
            return center;
        }
        void setRadius(float radius){
            this->radius=radius;
        }
        float getRadius(){
            return radius;
        }
        void judge(Point& p){
            float distance;
            distance = (p.getX()-center.getX())*(p.getX()-center.getX())+
            (p.getY()-center. getY())*(p.getY()-center. getY());
            if(distance<radius*radius){
                cout<<"点在圆内"<<endl;
            }
            else if(distance>radius*radius){
                cout<<"点在圆外"<<endl;
            }
            else{
                cout<<"点在圆上"<<endl;
            }
        }
    private:
        Point center;
        float radius;
};
int main(){

    Point p1;
    p1.setX(1);
    p1.setY(0);


    Point center;
    center.setX(0);
    center.setY(0);
    Circle c;
    c.setCenter(center);
    c.setRadius(1);

    c.judge(p1);

    system("pause");
    return 0;
}

