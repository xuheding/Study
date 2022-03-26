using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _12_方法_函数_
{
    /// <summary>
    /// [public] static 返回值类型 方法名([参数列表])
    /// {
    ///     方法体；
    /// }
    /// 
    /// </summary>
    class Program
    {
        //字段，属于类的字段（由于c#中没有全局变量这个概念，用静态变量来模拟全局变量，这样，在这个类中都可以访问到）
        public static int _number = 10; 


        static void Main(string[] args)
        {
            //int num = GetMax(10, 20);  //在类中调用函数不需要加类名
            int num = Program.GetMax(10, 20);
            Console.WriteLine(num);
            Console.ReadKey();
        }

        public static int GetMax(int n1,int n2)//如果在前面加一个public代表公有，这样类外也能访问，类内属性，如果不加，默认为私有
        {
            return n1 > n2 ? n1 : n2;
        }
    }
}
