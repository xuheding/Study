using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

/// <summary>
/// 与c++不同之处
/// 1.结构体定义前要加public，每个字段前加public代表公有，否则默认私有
/// 2.结构体结束不需要加分号
/// </summary>
namespace _10_结构体
{
    //定义结构体
    public struct Person  //这个public可以省略
    {
        //下面的这个不叫变量，叫字段，字段规范的命名都是下划线开头的
        public string _name;//如果不加public只能在结构体内部访问,也就是说不加public就是私有的
        public int _age;
        public Gender _gender;
    }


    public enum Gender
    {
        男,
        女
    }

    public struct MyColor
    {
        public int _red;
        public int _green;
        public int _blue;
    }

    class Program
    {
        static void Test01()
        {
            Person zsPerson;
            zsPerson._name = "张三";
            zsPerson._age = 10;
            zsPerson._gender = Gender.男;
            Console.WriteLine(zsPerson._age);
            Console.ReadKey();
        }

        static void Test02()
        {
            MyColor mc;
            mc._red = 255;
            mc._green = 0;
            mc._blue = 0;
            //这样就定义了一个红色
        }


        static void Main(string[] args)
        {
            Test01();
            Test02();
        }
    }
}
