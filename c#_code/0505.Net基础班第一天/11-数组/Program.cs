using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _11_数组
{
    class Program
    {

        /// <param name="args"></param>
        static void Main(string[] args)
        {
            //定义数组
            int[] nums = new int[10];//默认都是0
            string[] str = new string[10];//默认都是null，不是""
            bool[] bools = new bool[10];//默认都是false;


            //数组定义方式
            int[] nums1 = new int[10];
            int[] nums2 = { 1, 2, 3, 4, 5, 6 };
            int[] nums3 = new int[3] { 1, 2, 3 };//不推荐
            int[] nums4 = new int[] { 1, 2, 3, 4, 5 };//不推荐

            //一些排序、反向等操作
            int[] nums5 = {3, 7, 2, 1, 4 };
            Array.Sort(nums5);//从小到大排序
            Array.Reverse(nums5);//反向排列数组
            for(int i = 0; i < nums5.Length; i++)
            {
                Console.WriteLine(nums5[i]);
            }
            Console.ReadKey();

        }
    }
}
