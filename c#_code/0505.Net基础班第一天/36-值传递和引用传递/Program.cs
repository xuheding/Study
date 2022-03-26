using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _36_值传递和引用传递
{
    class Program
    {
        static void Main(string[] args)
        {

            //由于引用传递,  p2对应的值改变，p1也会改变
            Person p1 = new Person();
            p1.Name = "张三";
            Person p2 = p1;
            p2.Name = "李四";
            Console.WriteLine(p1.Name);
            Console.WriteLine(p2.Name);


            //字符串比较特殊，具有不可变性
            string s1 = "张三";
            string s2 = s1;//会重新开辟一块新的空间
            s2 = "李四";
            Console.WriteLine(s1);
            Console.WriteLine(s2);
            Console.ReadKey();

            //对于值传递的变量，想要使用引用，必须要使用ref
        }
    }

    public class Person
    {
        string _name;

        public string Name { get => _name; set => _name = value; }
    }
}
