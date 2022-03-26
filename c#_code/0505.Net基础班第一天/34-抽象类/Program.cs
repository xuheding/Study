using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


/// <summary>
/// 当不知道父类的方法怎么实现的时候，可以使用抽象类，这样就不用去实现抽象方法了
/// 抽象类是不能实例化的
/// 抽象成员必须在抽象类中
/// 如果子类也是抽象类，那么父类的抽象方法可以不实现
/// 抽象类中也可以有虚方法
/// 抽象类是有构造函数的，虽然不能被实例化
/// 
/// =======
/// 如果父类中的方法有默认的实现，并且父类需要被实例化，这时可以考虑将父类定义成一个普通类，用虚方法来实现多态。
/// 如果父类中的方法没有默认实现，父类也不需要被实例化，则可以将该类定义为抽象类
/// </summary>
namespace _34_抽象类
{
    class Program
    {
        static void Main(string[] args)
        {
        }

        
    }

    //抽象类
    public abstract class Animal
    {

        public abstract void Bark();//抽象方法（不用写方法体）

     
    }


    public class Dog : Animal  //在子类中可以按Alt+Enter进行快速重写
    {

        public override void Bark()//重写抽象方法
        {
            Console.WriteLine("狗叫");//抽象子类必须实现抽象方法，不然会报错
        }

    }
}
