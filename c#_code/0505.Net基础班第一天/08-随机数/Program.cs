using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _08_随机数
{
    class Program
    {
        static void Main(string[] args)
        {
            //1.创建能够产生随机数的对象
            Random r = new Random();
            //2.让产生随机数的这个对象调用方法来产生随机数
            int number = r.Next(1, 10);//产生1~9的整数随机数，取不到10
            Console.WriteLine(number);
            Console.ReadKey();
        }
    }
}
