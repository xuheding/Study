using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _28_File类
{
    class Program
    {
        static void Main(string[] args)
        {
            //使用相对路径
            //相对路径是相对bin/Debug/XXXX.exe的

            //File只适合读取小文件，因为File是一口气全部读取进来的，如果要读取大文件则需要用到FileStream



            //创建一个文件
            File.Create(@"E:\code\c#_code\0505.Net基础班第一天\28-File类\new.txt");
            Console.WriteLine("创建成功");
            Console.ReadKey();

            //删除一个文件
            File.Delete(@"E:\code\c#_code\0505.Net基础班第一天\28-File类\new.txt");
            Console.WriteLine("删除成功");

            //复制一个文件
            File.Copy(@"E:\code\c#_code\0505.Net基础班第一天\28-File类\new.txt", @"E:\code\c#_code\0505.Net基础班第一天\28-File类\new2.txt");
            Console.WriteLine("复制成功");

            //File.Exists();判断文件是否存在
            //File.ReadAllLines("path",Encoding.Default);读取所有行,返回stirng[]
            //File.ReadAllText("path",Encoding.Default);读取所有行，返回string
            //File.ReadAllBytes("path");读取文件，返回byte[],把文件作为二进制来处理

            //File.WriteAllLines("path",new string[4],Encoding.Default);//将string数组按行写入文件
            //File.WriteAllText("path","string");将字符串全部写入文件
            //File.WriteAllBytes("path",new byte[5]);将byte[]全部写入到文件
            //File.AppendAllText();//将string追加到文件

        }
    }
}
