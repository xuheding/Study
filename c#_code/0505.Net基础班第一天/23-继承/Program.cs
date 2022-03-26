using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
/// <summary>
/// 继承：
/// 子类继承了父类的属性和方法，但是子类没有继承父类的私有字段
/// 子类可以继承父类的公有，但不能继承私有
/// 
/// 继承的特性：
/// 1.继承的单根性，一个类只能由一个父类
/// 2.继承的传递性
/// 
/// 查看类图   菜单-视图-查看类视图
/// 
/// 
/// 创建(new)子类的时候,会先调用父类的无参构造函数，再调用子类的构造函数
/// 所以，如果在父类中重新写一个有参数的构造函数之后，那个无参数的就被干掉了，
/// 子类就调用不到了，所以子类会报错
/// 解决办法：
/// 1）在父类中重新写一个无参数的构造函数
/// 2）在子类中显示的调用父类的构造函数，使用关键字:base()
/// </summary>
namespace _23_继承
{
    class ProgramP
    {
        static void Main(string[] args)
        {
            Student stu1 = new Student("zs", 10, '男', 1);
            stu1.Print();
            Console.ReadKey();
        }
    }


    class Person
    {
        string _name;
        int _age;
        char _gender;

        public string Name { get => _name; set => _name = value; }
        public int Age { get => _age; set => _age = value; }
        public char Gender { get => _gender; set => _gender = value; }

        public Person(string name, int age, char gender)
        {
            this.Name = name;
            this.Age = age;
            this.Gender = gender;
        }
        public void Print()
        {
            Console.WriteLine("this is a person");
        }

    }

    class Student : Person
    {
        int _id;

        public int Id { get => _id; set => _id = value; }


        //因为调用子类构造的时候会默认调用父类无参构造函数
        //为了防止代码冗余，可以使用:base调用父类有参构造
        public Student(string name, int age, char gender, int id) : base(name, age, gender)
        {   
            this.Id = id;
            //this.Name = name;
            //this.Age = age;
            //this.Gender = gender;
        }

        public new void Print()//重写父类方法，要加一个new，代表隐藏父类的方法
        {
            Console.WriteLine("this is a student");
        }


    }
}
