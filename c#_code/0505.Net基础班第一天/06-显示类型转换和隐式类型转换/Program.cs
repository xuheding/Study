using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _06_显示类型转换和隐式类型转换
{
    class Program
    {
        static void Main(string[] args)
        {
            //test01();
            //test02();
            test03();
        }

        /// <summary>
        /// 1.类型如果相兼容的两个变量，可以使用自动类型转换或者强制类型转换
        /// </summary>
        static void test01()
        {
            //隐式类型转换
            //1.两种类型兼容     double 和 int
            //2.目标类型大于原类型 : double>int

            int num = 10;
            double d = num; //自动类型转换  隐式类型转换

            double a = 301.6;
            int n = (int)a;  //显示类型转换
            Console.WriteLine(n);
            Console.ReadKey();
        }
        /// <summary>
        /// 2.但是，如果两个类型的变量不兼容，比如string与int 或者string 与double
        /// 这时候我们可以使用一个convert的转换工厂进行转换
        /// </summary>
        static void test02()
        {
            string s = "123";
            double d = Convert.ToInt32(s);//类似用c++中的stoi

            Console.WriteLine(d);
            Console.ReadKey();
        }
        static void test03()
        {
            string s = "123";
            int num = int.Parse(s);//这个是和Conver.ToInt32是一样，ToInt32内部就是调用了int.Parse

            //但是对于Conver.ToInt32还是int.Parse,要是输入的是字母，那么就会出错


            //int.TryParse表示尝试去转换为int,如果转换成功int，那么返回值就为true，否则为false。  并对number赋值转换的结果,如果转换失败，就给number赋值0
            int number = 999;
            bool b = int.TryParse("123abc", out number);
            Console.WriteLine(b);
            Console.WriteLine(number);
            Console.ReadKey();
        }
    }
}
