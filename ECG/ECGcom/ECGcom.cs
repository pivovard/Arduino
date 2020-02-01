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

        public bool status = false;

        static Random r = new Random();
        static uint i = 100;

        public ECGcom(string ip, int port = 666)
        {
            Console.WriteLine("Connecting to {ip}:{port}...");
            tcpClient = new TcpClient();
            tcpClient.Connect(ip, port);

            if (!(status = tcpClient.Connected))
            {
                Console.WriteLine("Not connected.");
                return;
            }

            Console.WriteLine("Connected.");
            stream = tcpClient.GetStream();

            Byte[] data = Encoding.ASCII.GetBytes("Ahoj\n");
            stream.Write(data, 0, data.Length);
        }

        ~ECGcom()
        {
            //stream.Close();
            //tcpClient.Close();
        }
        byte[] data = new byte[12];
        public Item Receive()
        {
            stream.Read(data, 0, data.Length);
            string msg = Encoding.ASCII.GetString(data);
            Console.WriteLine($"Received: {msg}");

            uint t = System.BitConverter.ToUInt32(data, 0);
            float e = System.BitConverter.ToSingle(data, 4);
            float s = System.BitConverter.ToSingle(data, 8);

            Console.WriteLine($"Received: {t} {e} {s}");
            return new Item(t, e, s);
        }

        public static Item ReceiveDummy()
        {
            i++;
            return new Item(i, (float)r.NextDouble(), (float)r.NextDouble());
        }
    }

    public class Item
    {
        public float time;
        public float ecg;
        public float speed;

        public Item(uint time, float ecg, float speed)
        {
            this.time = time / 1000.0f; //ms->s
            this.ecg = ecg;
            this.speed = speed;
        }
    }
}
