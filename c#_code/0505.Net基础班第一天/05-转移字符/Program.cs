using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _05_转义字符
{
    class Program
    {
        static void Main(string[] args)
        {
            //对于路径可以使用转义字符\\表示\,当然也可以在字符串前加@表示不使用转移字符
            string path1 = "C:\\a\\b\\c\\hello.txt";
            string path2 = @"C:\a\b\c\hello.txt";

        }
    }
}
