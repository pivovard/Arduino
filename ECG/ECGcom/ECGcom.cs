using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;

namespace ECGcom
{
    public class ECGcom
    {
        TcpClient tcpClient { get; set; }
        NetworkStream stream { get; set; }

        public Queue<Item> buffer { get; private set; }
        public bool status = false;

        public ECGcom(string ip, int port = 666)
        {
            tcpClient = new TcpClient();
            tcpClient.Connect(ip, port);
            if (!(status = tcpClient.Connected)) return;

            stream = tcpClient.GetStream();
            buffer = new Queue<Item>();
        }

        public Item Receive()
        {
            byte[] data = new byte[256];
            stream.Read(data, 0, data.Length);
            string msg = Encoding.ASCII.GetString(data);
            Console.WriteLine("Received: " + msg);
            return Parse(msg);
        }

        private Item Parse(string msg)
        {
            string[] s = msg.Split(';');
            return new Item(int.Parse(s[1]), double.Parse(s[2]), double.Parse(s[3]));
        }

        public Item GetItem()
        {
            return (buffer.Count > 0) ? buffer.Dequeue() : null;
        }
    }

    public class Item
    {
        public int time;
        public double ecg;
        public double speed;

        public Item(int time, double ecg, double speed)
        {
            this.time = time;
            this.ecg = ecg;
            this.speed = speed;
        }
    }
}
