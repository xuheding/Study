using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

/// <summary>
/// ref就是和c++的引用是一个意思
/// </summary>
namespace _14_ref参数
{
    class Program
    {

        public static void swap(ref int a,ref int b)
        {
            int tmp = a;
            a = b;
            b = tmp;
        }
        static void Main(string[] args)
        {
            int a = 10, b = 20;
            swap(ref a, ref b);//传参的时候一定要加入关键字ref，才代表引用
            Console.WriteLine("a:{0}", a);
            Console.WriteLine("b:{0}", b);
            Console.ReadKey();


        }

    }
}
