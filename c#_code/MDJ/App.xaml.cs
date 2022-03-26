using System;
using System.Collections.Generic;
using System.Configuration;
using System.Data;
using System.Linq;
using System.Threading.Tasks;
using System.Windows;

namespace MDJ
{
    /// <summary>
    /// App.xaml 的交互逻辑
    /// </summary>
    public partial class App : Application
    {
        protected override void OnStartup(StartupEventArgs e)
        {
            SplashScreen s = new SplashScreen("/Resources/startup.png");
            s.Show(false);
            System.Threading.Thread.Sleep(4000);
            s.Close(new TimeSpan(0, 0, 1));

            base.OnStartup(e);
        }
    }
}
