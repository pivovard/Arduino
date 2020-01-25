using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace ECGcom
{
    class Program
    {
        static string ip = "192.168.43.19";
        static int port = 666;

        static UdpClient udpClient { get; set; }
        static TcpClient tcpClient { get; set; }

        static void Main(string[] args)
        {
            //runUDP();
            runTCP();
            

            Console.ReadKey();
        }

        public static void runUDP()
        {
            udpClient = new UdpClient(port);
            udpClient.Connect(ip, port);

            Byte[] data = Encoding.ASCII.GetBytes("Ahoj\n");
            udpClient.Send(data, data.Length);

            IPEndPoint RemoteIpEndPoint = new IPEndPoint(IPAddress.Any, 666);
            data = udpClient.Receive(ref RemoteIpEndPoint);
            string msg = Encoding.ASCII.GetString(data);

            Console.WriteLine(msg);
            udpClient.Close();
        }

        public static void runTCP()
        {
            tcpClient = new TcpClient();
            tcpClient.Connect(ip, 80);
            var stream = tcpClient.GetStream();

            Byte[] data = Encoding.ASCII.GetBytes("Ahoj\n??\n\n");
            stream.Write(data, 0, data.Length);

            //stream.Read(data, 0, 6);
            //string msg = Encoding.ASCII.GetString(data);

            //while (stream.CanRead && stream.DataAvailable)
            {
                Console.WriteLine("Reading");
                stream.Read(data, 0, data.Length);
                string msg = Encoding.ASCII.GetString(data);
                Console.WriteLine(msg);
            }

            stream.Close();
            tcpClient.Close();
        }
    }
}
