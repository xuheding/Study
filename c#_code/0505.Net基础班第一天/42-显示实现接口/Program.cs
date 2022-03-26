using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _42_显示实现接口
{
    class Program
    {
        static void Main(string[] args)
        {
            IFlyable fly = new Bird();
            fly.Fly();//调用接口
            Bird bird = new Bird();
            bird.Fly();//调用对象本身的方法
            Console.ReadKey();

        }
    }

    public interface IFlyable
    {
        void Fly();
    }

    public class Bird : IFlyable
    {

        /// <summary>
        /// 由于可能会出现重名的问题，比如Fly()是鸟自己的方法，不能被接口调用。因此需要显示实现接口
        /// </summary>
        /// 


        public void Fly()
        {
            Console.WriteLine("鸟会飞");
        }
        void IFlyable.Fly()//显示实现接口
        {
            Console.WriteLine("显示实现接口");
        }
    }

}
