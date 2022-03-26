using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

/// <summary>
/// 所有定义的类继承了父类obj,obj默认定义了ToString()的虚方法，默认是所在命名空间，可以进行重写
/// </summary>
namespace _40_重写父类的ToString__
{
    class Program
    {
        static void Main(string[] args)
        {
            Person p = new Person();
            Console.WriteLine(p);//打印对象的时候，输出的是对象的ToString();
            Console.ReadKey();
        }
    }

    public class Person
    {
        public override string ToString()
        {
            return "Hello world";
        }
    }
}
