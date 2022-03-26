using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _18_构造函数_析构函数
{
    public class Student
    {
        private string _name;
        private int _age;
        private char _gender;

        public string Name { get => _name; set => _name = value; }
        public int Age { get => _age; set => _age = value; }
        public char Gender { get => _gender; set => _gender = value; }

        //构造函数(必须要是public 否则没法调用构造)
        public Student(string name,int age,char gender)
        {
            this.Name = name;
            this.Age = age;
            this.Gender = gender;
            Console.WriteLine("调用构造函数");
        }
        //如果不写构造函数，默认是无参构造函数,当写了其他构造函数，默认的无参构造就失效了



        //构造函数可以重载
        public Student(string name,int age) : this(name,age,'男')
        {
            //重复写这些东西有些冗余，可以直接用 :this 调用之前的那个构造函数
            //this.Name = name;
            //this.Age = age;
            //this.Gender = '男';

        }

        ~Student()
        {
            Console.WriteLine("调用析构函数");
        }
        
    }
}
