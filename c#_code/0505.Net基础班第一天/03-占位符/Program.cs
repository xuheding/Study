using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _03_占位符
{
    class Program
    {
        static void Main(string[] args)
        {
            int n1 = 10;
            int n2 = 20;
            int n3 = 30;
            Console.WriteLine("第一个数字是{0},第二个数字是{1},第三个数字是{2}", n1, n2, n3);
            //Console.ReadKey();

            double c = 3.33333;
            Console.WriteLine("{0:0.00}", c);//使用占位符保留两位小数

            //交换变量
            n1 = n1 - n2;
            n2 = n1 + n2;
            n1 = n2 - n1;
            Console.WriteLine("{0},{1}",n1, n2);
            Console.ReadKey();
        }
    }
}
