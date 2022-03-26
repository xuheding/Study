using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace 补充1_委托
{
    public delegate void GreetingDelegate(string name);//委托的本质是一个类，所以要和类并排写
    class Program
    {
        private static void EnglishGreeting(string name)
        {
            Console.WriteLine("Good Morning, " + name);
        }

        private static void ChineseGreeting(string name)
        {
            Console.WriteLine("早上好, " + name);
        }

        private static void GreetPeople(string name, GreetingDelegate MakeGreeting)//这样委托，可以对函数名像参数一样传递进去了
        {
            MakeGreeting(name);
        }
        static void Main(string[] args)
        {
            GreetPeople("Liker", EnglishGreeting);
            GreetPeople("李志中", ChineseGreeting);
            Console.ReadLine();
        }
    }
}
