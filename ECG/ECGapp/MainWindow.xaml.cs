using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;


namespace ECGapp
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private ECGcom.ECGcom com { get; set; }
        private Thread th { get; set; }
        private bool thKill = false;


        public MainWindow()
        {
            InitializeComponent();
        }

        private void BtnConnect_Click(object sender, RoutedEventArgs e)
        {
            if(com == null || !com.status)
            {
                Connect();
            }
            else
            {
                Disconnect();
            }
        }

        private void Connect()
        {
            com = new ECGcom.ECGcom(tbIP.Text);

            if (com.status)
            {
                lbStatus.Content = "Connected";
                lbStatus.Background = Brushes.LightGreen;
                btnConnect.Content = "Disconnect";

                var model = this.DataContext as ViewModel;

                //start new thread that receives data from server
                th = new Thread(delegate ()
                {
                    while (true)
                    {
                        if (thKill) break;

                        var item = com.Receive();
                        //var item = ECGcom.ECGcom.ReceiveDummy();
                        model.Add(item);
                    }
                });
                th.Start();
            }

            
        }

        private void Disconnect()
        {
            if (th != null && th.IsAlive)
            {
                thKill = true;
                th.Join();
                thKill = false;
            }
            
            com = null;

            lbStatus.Content = "Disconnected";
            lbStatus.Background = Brushes.Red;
            btnConnect.Content = "Connect";
        }

        private void Window_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            Disconnect();
        }
    }
}
