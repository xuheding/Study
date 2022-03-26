using System;
using System.Collections;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

/// <summary>
/// 2、装箱、拆箱
/// 装箱：就是将值类型转换为引用类型
/// 拆箱：将引用类型转换为值类型
/// </summary>
namespace _30_装箱_拆箱
{
    class Program
    {
        static void Main(string[] args)
        {
            //int n = 10;
            //object o = n;//装箱
            //int nn = (int)o;//拆箱

            //ArrayList list = new ArrayList(); // ArrayList内部实现都是通过object装箱操作，所以速度会慢很多，因此平时要尽可能避免装箱
            List<int> list = new List<int>(); //不涉及装箱问题，一直都是int类型

            Stopwatch sw = new Stopwatch();
            sw.Start();
            for(int i = 0; i < 10000; i++)
            {
                list.Add(i);
            }
            sw.Stop();
            Console.WriteLine(sw.Elapsed);
            Console.ReadKey();

            //看两种类型是否发生了装箱或者拆箱，要看，这两种类型是否存在继承关系

            //string str = "123";//所以这里没有发生装箱和拆箱
            //int n = Convert.ToInt32(str);

            int n = 10;
            IComparable j = n;//装箱 (int继承了ICompare,也就是说ICompareable是int的父类)

            //可以理解为里氏变换，是装箱的过程




        }
    }
}
