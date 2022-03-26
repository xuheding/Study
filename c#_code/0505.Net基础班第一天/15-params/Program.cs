using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _15_params_参数
{
    /// <summary>
    /// params称之为可变参数
    /// 可以把99,88,77用params组合成数组score
    /// </summary>
    class Program
    {
        static void Main(string[] args)
        {
            Test("张三", 99, 88, 77);
            Console.ReadKey();
        }

        public static void Test(string name, params int[] score)//params参数必须放在形参的最后一个,且只能写一个parmas
        {
            int sum = 0;
            for(int i = 0; i < score.Length; i++)
            {
                sum += score[i];
            }
            Console.WriteLine("{0}这次考试的总成绩是{1}", name, sum);
        }
    }
}
//以后遇到参数为params int[] 类型的函数参数时候
//我们可以传入几个int类型的参数,或者直接传入int的数组都行
