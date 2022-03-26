using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


//枚举就是将值给限定，比如季节就4种状态，可以规范我们的开发 ,所以该枚举类型就只能是这4种值，它与c++不同，末尾不需要分号，对于枚举值也不需要加引号

//枚举只可以放在命名空间下 或者 类中

namespace _09_枚举
{
    //枚举声明到命名空间的下面，类的外面，表示这个命名空间下，所有的类都可以使用这个枚举
    public enum Gender
    {
        男,
        女
    } 

    public enum Season
    {
        春,
        夏,
        秋,
        冬
    }
    class Program
    {   
        
        /// <param name="args"></param>
        static void Main(string[] args)
        {
            //test01();//定义枚举变量
            test02();
        }


     
        static void test01()
        {
            Gender gender = Gender.男;
            Season season = Season.夏;
            Console.WriteLine(gender);
            Console.ReadKey();
        }

        static void test02()
        {
            //1.将枚举类型强转为 int类型
            Season season = Season.冬;
            int n = (int)season;
            Console.WriteLine(n);
   

            //2.将int 类型 强转为枚举类型
            int n1 = 3;
            int n2 = 8;
            Season s1 = (Season)n1;//输出 冬
            Season s2 = (Season)n2;//对于转不了的int类型，依旧输出原来的值，s2输出8
            Console.WriteLine(s1);
            Console.WriteLine(s2);


            //3.将枚举类型转为string
            string s3 = s2.ToString();//所有类型都可以通过ToString转华为字符串类型

            //4.将字符串转为枚举类型
            string s = "夏";
            Season s4 = (Season)Enum.Parse(typeof(Season), s);
            Console.WriteLine(s4);

            Console.ReadKey();
        }
    }
}
