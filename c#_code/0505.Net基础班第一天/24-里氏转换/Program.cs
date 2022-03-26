using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


/// <summary>
/// 
/// </summary>
namespace _24_里氏转换
{
    class Program
    {
        static void Main(string[] args)
        {
            // 1、里氏转换
            //    1）、子类可以赋值给父类:如果有一个地方需要一个父类作为参数，我们可以给一个子类代替

            //Student s = new Student();
            //Person p = s;

            Person p = new Student();

            //string str = string.Join("|", new string[] { "1", "2", "3", "4" });
            //Console.WriteLine(str);
            //Console.ReadKey();

            //    2）、如果父类中装的是子类对象，那么可以将整个父类强转为子类对象
            //Student ss = (Student)p; //可以转换
            //Teacher tc = (Teacher)p;//不能转换，因为p中装着的是Student对象
            //因此在作类型转换的时候一般会去判断，用is来判断


            //    3)类型转换判断
            //is：表示类型转换，如果能够转换成功，则返回一个true，否则返回一个false
            //as:表示类型转换，如果能够转换则返回对应的对象，否则返回一个null

            //is的用法
            if (p is Teacher)
            {
                Teacher tt = (Teacher)p;
            }
            else
            {
                Console.WriteLine("转换失败");
            }

            //as的用法

            Teacher t = p as Teacher;//因为p装着student对象，因此t为null
            Student s = p as Student;//s为转换后的结果

            Console.ReadKey();
        }
    }
    public class Person
    {
        
    }

    public class Student : Person
    {

    }

    public class Teacher : Person
    {

    }

}
