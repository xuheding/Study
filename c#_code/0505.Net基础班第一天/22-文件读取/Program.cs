using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _22_文件读取
{
    class Program
    {
        static void Main(string[] args)
        {
            string path = @"E:\code\c#_code\0505.Net基础班第一天\22-文件读取\1.txt";
            string[] contents = File.ReadAllLines(path,Encoding.Default);//后面可以修改读取的格式Encoding，比如utf-8等
            Console.ReadKey();

        }
    }
}
