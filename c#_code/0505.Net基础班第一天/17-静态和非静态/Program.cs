using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


/// <summary>
/// 1、在非静态类中，既可以有实例成员，也可以有静态成员。
///     1)、在调用实例成员的时候，需要使用对象名.实例成员
///     2)、在调用静态成员的时候,需要使用类名.静态成员名
/// 总结:静态成员必须使用类名去调用，而实例成员使用对象名调用。
///     静态函数中，只能访问静态成员，不允许访问实例成员
///     实例函数中，既可以使用静态成员，也可以使用实例成员
///     
///2、静态类中，只能有静态成员，不允许出现实例成员
///     静态类不能被实例化
///
/// 
///使用：
///     1）如果你想要你的类当作一个“工作类”去使用，这个时候可以考虑将类写成静态类
///     2）静态类在整个项目中资源共享
///只有在全部程序结束时，静态类才会释放资源
/// </summary>
namespace _17_静态和非静态
{
    class Program
    {

        static void Main(string[] args)
        {
        }
    }
}
