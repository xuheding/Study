using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _29_List泛型集合
{
    class Program
    {
        static void Main(string[] args)
        {
            //创建List泛型集合对象
            List<int> list = new List<int>();
            list.Add(1);
            list.Add(2);
            list.Add(3);

            list.AddRange(new int[] { 1,2,3,4});

            //将数组转为List
            char[] chs = new char[] { 'c', 'a', 'b' };
            List<char> chsList = chs.ToList();
            //将List转为数组
            char[] chsArray = chsList.ToArray();

            foreach(var c in chsList)
            {
                Console.WriteLine(c);
            }
            Console.ReadKey();
        }
    }
}
