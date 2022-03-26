using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


/// <summary>
/// 字符串
/// 1）字符串的不可变性
/// 当你给一个字符串重新赋值之后，老值并没有销毁，而是重新开辟一块空间存储新值
/// 当程序结束后，GC（垃圾回收机制）扫描整个内存，如果发现有的空间没有被指向，则立即把它销毁
/// 2)我们可以将字符串看作是char类型的一个只读数组
/// ToCharArray();将字符串转为char数组
/// new string(char[] cha);将char数组转为字符串
/// </summary>
namespace _21_字符串
{
    class Program
    {
        static void Main(string[] args)
        {
            test02();//string转为char，char转为string
            test03();//StringBuilder创建字符串  还有StopWatch计时器的使用
            test04();//字符串的常用方法
            Console.ReadKey();

        }
        static void test02()
        {
            string s = "abcdefg";
            //s[0]='b';不能这样 因为是只读的
            //首先要将string改为真正意义上的char数组才行
            char[] chs = s.ToCharArray();
            chs[0] = 'b';
            s = new string(chs);

            Console.WriteLine(s);
        }
        static void test03()
        {
            //String在进行运算时（如赋值和拼接等）会产生一个新的实例，而StringBuilder则不会,所以在大量字符串拼接或频繁
            //对一个字符串进行操作时，最好用StringBuilder,不要用String

            //StringBuilder用来创建string的，创建完后要转成string类
            StringBuilder sb = new StringBuilder();

            //Stopwatch是一个计时的类
            Stopwatch sw = new Stopwatch();
            sw.Start();
            for (int i = 0; i < 100000; i++)
            {
                sb.Append(i);
            }
            sw.Stop();

            //Console.WriteLine(sb.ToString());
            Console.WriteLine(sw.Elapsed);
            Console.ReadKey();
        }
        static void test04()
        {
            string s = "abcdefg";
            string s4 = "a  b  + sfasf  -";
            //字符串的长度
            int n=s.Length;
            //将字符串转为大写
            string s1 = s.ToUpper();
            //将字符串转为小写
            string s2 = s.ToLower();
            //比较两字符串是否相等（可以指定是否区分大小写)
            bool b2 = s1.Equals(s2,StringComparison.OrdinalIgnoreCase);
            //分割字符串
            char[] chs = { ' ', '+', '-' };
            string[] str = s4.Split(chs, StringSplitOptions.RemoveEmptyEntries);//后面的选项是把空的字符串去掉

            //字符串的替换Replace();
            //取子字符串Substring();
            //判断字符串中是否含有字串value:   Contains(value);
            //判断字符串是否以子串value开始  StartsWith(value);
            //判断字符串是否以字串value结束 EndsWith(value);
            //取字串value第一次出现的位置 IndexOf(value);
            //将字符串数组合并为字符串 Join(分隔符,字符串数组);
            //去掉字符串前空格  Trim()
            //去掉字符串后空格  TrimEnd()
            //判断字符串是否为空或者Null   IsNullOrEmpty()
            
        }
    }
}
