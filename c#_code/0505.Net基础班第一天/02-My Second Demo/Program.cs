using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _02_变量
{
    class Program
    {
        static void Main(string[] args)
        {
            int a=200;  //整数类型
            double b = 1.5; //浮点数类型 小数点15~16位
            decimal money = 500m; //金钱类型    小数点28~29位，必须数字后加一个m来区别double


            string zsName = "张三";//字符串类型
            string s = "";//字符串可以存储空

            char gender = '男';//字符类型  最多只能存一个字符
            //char c = '';//字符 不能存空


            
            Console.WriteLine("name" + '5');//两边有一个字符串，就作字符串连接
            Console.WriteLine(5 + "5");//两边有一个字符串，就作字符串连接
            Console.WriteLine(5 + '5');//字符是相加，得到的是最终的ASCII码
            Console.ReadKey();

            
        }
    }
}
