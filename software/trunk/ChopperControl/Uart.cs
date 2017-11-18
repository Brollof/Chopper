using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO.Ports;
using System.Runtime.InteropServices;
using System.Threading;
using System.Collections.Concurrent;
using System.Diagnostics;

namespace ChopperControl
{
    class MyUart
    {
        private string portName;
        const int CHECK_UART_Q_INTERVAL = 100;
        const int CHECK_FOR_ACK_TIMEOUT = 6000;
        private System.Timers.Timer timer = new System.Timers.Timer();
        SerialPort uart = new SerialPort();
        public event EventHandler UartErrorOccured;
        public event Action<string> UpdateTerminal;
        public event Action<string, string> UpdateMeasurements;
        public ConcurrentQueue<string> Queue = new ConcurrentQueue<string>();

        /* Heartbeat module */
        private bool startHeartbeat = false;
        private bool ackReceived = true;
        const int HEARTBEAT_SLEEP_TIME = 3000;
        private Thread RequestSender;
        string requestMessage = "se";

        public string PortName
        {
            get { return this.portName; }
            set { this.portName = value; }
        }

        public bool IsAckReceived
        {
            get { return this.ackReceived; }
            set { this.ackReceived = value; }
        }

        public MyUart()
        {
            uart.BaudRate = 115200;

            timer.Interval = CHECK_UART_Q_INTERVAL;
            timer.Elapsed += CheckUartQueue;
            timer.AutoReset = true;

            RequestSender = new Thread(new ThreadStart(sendRequest));
            RequestSender.IsBackground = true;
            RequestSender.Name = "AckRequestSender";
            //RequestSender.Start();
        }

        public void Close()
        {
            uart.Close();
            startHeartbeat = false;
            timer.Stop();
            uart.DataReceived -= uartDataReceived;
        }

        public void Open()
        {
            uart.PortName = portName;
            uart.Open();
            uart.DataReceived += uartDataReceived;
            timer.Start();
            startHeartbeat = true;
        }

        public bool IsOpen
        {
            get { return uart.IsOpen; }
        }

        private void CheckUartQueue(object sender, System.Timers.ElapsedEventArgs e)
        {
            string txt;
            if (Queue.TryPeek(out txt))
            {
                Queue.TryDequeue(out txt);

                try { uart.Write(txt); }
                catch { OnUartError(); }
            }
        }

        private bool firstCurrent = false;
        private bool firstSpeed = false;
        private string currentStr = String.Empty;
        private string speedStr = String.Empty;
        private void uartDataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            SerialPort sp = (SerialPort)sender;
            string s = sp.ReadExisting();
            
            if (s.Contains("&"))
            {
                ackReceived = true;
                s = s.Replace("&", "");
                Console.WriteLine("ACK received");
            }

            int startIndex = 0;
            for (int i = 0; i < s.Length; i++)
            {
                if(s[i] == '$')
                {
                    if (firstCurrent == false)
                    {
                        currentStr = String.Empty;
                        startIndex = i;
                        firstCurrent = true;
                    }
                    else if (firstCurrent == true)
                    {
                        firstCurrent = false;
                        s = s.Remove(startIndex, i - startIndex+1);
                        break;
                    }
                }
                else if (firstCurrent == true)
                {
                    currentStr += s[i];
                }
            }

            if (firstCurrent == true)
                s = s.Remove(startIndex, s.Length - startIndex);

            startIndex = 0;
            for (int i = 0; i < s.Length; i++)
            {
                if (s[i] == '^')
                {
                    if (firstSpeed == false)
                    {
                        startIndex = i;
                        firstSpeed = true;
                        speedStr = String.Empty;
                    }
                    else if (firstSpeed == true)
                    {
                        firstSpeed = false;
                        s = s.Remove(startIndex, i - startIndex + 1);
                        break;
                    }
                }
                else if (firstSpeed == true)
                {
                    speedStr += s[i];
                }
            }

            if (firstSpeed == true)
                s = s.Remove(startIndex, s.Length - startIndex);

            UpdateTerminal(s);
            UpdateMeasurements(currentStr, speedStr);
        }

        private int uartErrorCounter = 0;
        private void sendRequest()
        {
            while (true)
            {
                if (startHeartbeat)
                {
                    if (ackReceived)
                    {
                        ackReceived = false;
                        uartErrorCounter = 0;
                        Queue.Enqueue(requestMessage);
                        Console.WriteLine("Sending Synch ACK request...");
                    }
                    else if (uartErrorCounter < 2)
                    {
                        uartErrorCounter++;
                        Console.WriteLine("Not received: " + uartErrorCounter);
                        Queue.Enqueue(requestMessage);
                        Console.WriteLine("Sending Synch ACK request...");
                    }
                    else
                    {
                        uartErrorCounter = 0;
                        Console.WriteLine("ACK NOT received.");
                        ackReceived = true;
                        OnUartError();
                    }
                }
                Thread.Sleep(HEARTBEAT_SLEEP_TIME);
            }
        }

        protected virtual void OnUartError()
        {
            if (UartErrorOccured != null)
                UartErrorOccured(this, null);
        }

        public bool CheckIfUartErrorIsRegistered()
        {
            if (UartErrorOccured != null)
                return true;
            else
                return false;
        }

        public bool CheckIfUpdateTerminalIsRegistered()
        {
            if (UpdateTerminal != null)
                return true;
            else
                return false;
        }

        public bool CheckIfUpdateMeasurementsIsRegistered()
        {
            return UpdateMeasurements != null ? true : false;
        }
    }
}