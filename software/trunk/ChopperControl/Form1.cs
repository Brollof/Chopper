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

namespace ChopperControl
{
    
    public partial class Form1 : Form
    {
        //[DllImport("kernel32")]
        //static extern int AllocConsole();

        private const string programName = "Chopper Control";
        private const string programVersion = " v1.0";
        public delegate void uartDelegate(bool error);
        static public uartDelegate uartTryCatchDelegate;

        private bool motorStarted = false;
        private MyUart uart = new MyUart();

        public Form1()
        {
            InitializeComponent();
            //AllocConsole();
            this.Text = programName + programVersion;    
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            string[] portNames = SerialPort.GetPortNames();
            cbComList.Items.AddRange(portNames);

            rbTorqueControl.Checked = true;
            txtKdW.Enabled = false;
            txtKiW.Enabled = false;
            txtKpW.Enabled = false;
            txtSpeedRef.Enabled = false;
            txtIRef.Enabled = true;
            txtCurrentLimit.Enabled = false;
            txtDutyCycle.Enabled = false;
            
            picUartStatus.BackColor = Color.Red;
            cbFreq.SelectedIndex = 9; //5000 Hz
        }

        private void btnInit_Click(object sender, EventArgs e)
        {
            uart.PortName = cbComList.Text;
            uart.Open();

            if(!uart.CheckIfUartErrorIsRegistered())
                uart.UartErrorOccured += uart_UartErrorOccured;

            if(!uart.CheckIfUpdateTerminalIsRegistered())
                uart.UpdateTerminal += AddTerminalText;

            if (!uart.CheckIfUpdateMeasurementsIsRegistered())
                uart.UpdateMeasurements += UpdateMeasurements;

            btnInit.Enabled = false;
            dataControl();
            if (motorStarted == true)
            {
                btnStop.Enabled = true;
                btnStart.Enabled = false;
            }
            picUartStatus.BackColor = Color.Green;
        }

        public delegate void voidDelegate();
        private void uartError()
        {
            uart.Close();
            cbComList.Items.Clear();
            picUartStatus.BackColor = Color.Red;
            btnInit.Enabled = false;
            btnStart.Enabled = false;
            btnStop.Enabled = false;
            Console.WriteLine("UART ERROR !");
            MessageBox.Show("Błąd komunikacji ze sterownikiem !", "Błąd", MessageBoxButtons.OK, MessageBoxIcon.Error);
        }

        private void uart_UartErrorOccured(object sender, EventArgs e)
        {
            voidDelegate err = uartError;
            this.Invoke(err);
        }

        private void AddTerminalText(string str)
        {
            this.BeginInvoke((Action)(() => { textBox1.AppendText(str); }));
        }

        private void UpdateMeasurements(string current, string speed)
        {
            this.BeginInvoke((Action)(() => { labCurrentMeas.Text = current; }));
            this.BeginInvoke((Action)(() => { labSpeedMeas.Text = speed; }));
        }

        private void btnClose_Click(object sender, EventArgs e)
        {
            uart.Close();
            btnStart.Enabled = false;
            btnStop.Enabled = false;
            btnInit.Enabled = true;
            dataControl();
            picUartStatus.BackColor = Color.Red;
        }

        private void rbControlChanged(object sender, EventArgs e)
        {
            dataControl();

            if (rbTorqueControl.Checked == true)
            {
                txtKpI.Enabled = true;
                txtKiI.Enabled = true;

                txtKdW.Enabled = false;
                txtKiW.Enabled = false;
                txtKpW.Enabled = false;
                txtSpeedRef.Enabled = false;
                txtIRef.Enabled = true;
                txtCurrentLimit.Enabled = false;
                txtDutyCycle.Enabled = false;
            }
            if (rbSpeedControl.Checked == true)
            {
                txtKpI.Enabled = true;
                txtKiI.Enabled = true;

                txtKdW.Enabled = true;
                txtKiW.Enabled = true;
                txtKpW.Enabled = true;
                txtSpeedRef.Enabled = true;
                txtIRef.Enabled = false;
                txtCurrentLimit.Enabled = true;
                txtDutyCycle.Enabled = false;
            }
            if(rbPwmControl.Checked == true)
            {
                txtKpI.Enabled = false;
                txtKiI.Enabled = false;

                txtKdW.Enabled = false;
                txtKiW.Enabled = false;
                txtKpW.Enabled = false;
                txtSpeedRef.Enabled = false;
                txtIRef.Enabled = false;
                txtCurrentLimit.Enabled = false;
                txtDutyCycle.Enabled = true;
            }
        }

        private void btnStart_Click(object sender, EventArgs e)
        {
            bool temp = true;
            temp = checkGains();
            if (temp == false)
                return;
            temp = checkParameters();
            if (temp==false)
                return;
            /* c KpI n KiI n KpW n KiW n KdW n ctrlType n freq n izad n omegazad e*/
            string dataToSend = "c";
            string[] strPointers = 
            {
                txtKpI.Text,
                txtKiI.Text,
                txtKpW.Text,
                txtKiW.Text,
                txtKdW.Text,
                getControlType(),
                cbFreq.Text,
                txtIRef.Text,
                txtSpeedRef.Text,
                txtCurrentLimit.Text,
                string.IsNullOrWhiteSpace(txtDutyCycle.Text) ? "0" : (Convert.ToDouble(txtDutyCycle.Text) / 100).ToString().Replace(',','.'),
            };

            int frameLength = strPointers.Length;

            for (int i = 0; i < frameLength; i++)
            {
                dataToSend += strPointers[i];
                if (i < frameLength-1)
                    dataToSend += 'n';
                else
                    dataToSend += 'e';
            }

            Console.WriteLine(dataToSend);
            uart.Queue.Enqueue(dataToSend);

            //jesli sie udalo wyslac
            btnStop.Enabled = true;
            btnStart.Enabled = false;
            motorStarted = true;
            dataControl();
        }

        private void btnStop_Click(object sender, EventArgs e)
        {
            string dataToSend = "cnnnnnn0nnne";
            Console.WriteLine(dataToSend);
            uart.Queue.Enqueue(dataToSend);

            //jesli sie udalo wyslac 
            btnStop.Enabled = false;
            btnStart.Enabled = true;
            motorStarted = false;
            dataControl();
        }

        private void checkDataToStartMotor(object sender, EventArgs e)
        {
            dataControl();
        }

        /* Sprawdza dane niezbedne do uruchomienia ukladu regulacji */
        private void dataControl()
        {
            if (rbTorqueControl.Checked == true)
            {
                if (txtKpI.Text.Length > 0 && txtKiI.Text.Length > 0 &&
                    uart.IsOpen && txtIRef.Text.Length>0 &&
                    motorStarted == false && txtCurrentLimit.Text.Length > 0)
                    btnStart.Enabled = true;
                else
                    btnStart.Enabled = false;
            }

            if(rbSpeedControl.Checked == true)
            {
                if (txtKpI.Text.Length > 0 && txtKiI.Text.Length > 0 &&
                    txtKpW.Text.Length > 0 && txtKiW.Text.Length > 0 && txtKdW.Text.Length > 0 &&
                    uart.IsOpen && txtSpeedRef.Text.Length > 0 && motorStarted == false &&
                     txtCurrentLimit.Text.Length > 0)
                    btnStart.Enabled = true;
                else
                    btnStart.Enabled = false;
            }

            if(rbPwmControl.Checked == true)
            {
                if (motorStarted == false && uart.IsOpen && txtDutyCycle.Text.Length>0)
                    btnStart.Enabled = true;
                else
                    btnStart.Enabled = false;
            }
        }

        private string getControlType()
        {
            if (rbTorqueControl.Checked)
                return "2";
            else if (rbSpeedControl.Checked)
                return "1";
            else if (rbPwmControl.Checked)
                return "3";

            return "-1";
        }

        /* Wyswietla informacje na temat parameterow UART */
        private void btnUartInfo_Click(object sender, EventArgs e)
        {
            var form = new ParametryUart();
            form.ShowDialog();
        }

        private int previousIndex = -1;
        private void cbComList_Click(object sender, EventArgs e)
        {
            string[] portNames = SerialPort.GetPortNames();
            string temp = cbComList.Text;

            cbComList.Items.Clear();
            cbComList.Items.AddRange(portNames);
            cbComList.Text = temp;
            if (cbComList.Text == "")
            {
                previousIndex = -1;
                picUartStatus.BackColor = Color.Red;
            }
        }

        private void cbComList_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (cbComList.SelectedIndex >= 0)
            {
                if (cbComList.SelectedIndex != previousIndex)
                {
                    btnInit.Enabled = true;
                    previousIndex = cbComList.SelectedIndex;
                }
            }
        }

        private bool checkParameters()
        {
            int temp = 0;

            if (rbTorqueControl.Checked == true)
            {
                temp = Convert.ToInt32(txtIRef.Text);
                if (!(temp >= 1 && temp <= 100))
                {

                    MessageBox.Show("Wartość prądu zadanego powinna mieścić się w zakresie <1;100>", "Błąd parametrów", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    return false;
                }
            }

            if (rbSpeedControl.Checked == true)
            {
                temp = Convert.ToInt32(txtSpeedRef.Text);
                if (!(temp >= 1 && temp <= 3000))
                {
                    MessageBox.Show("Wartość prędkości powinna mieścić się w zakresie <1;3000>", "Błąd parametrów", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    return false;
                }
            }

            return true;
        }

        /* Sprawdz poprawnosc zakresu wprowadzonych danych */
        private bool checkGains()
        {
            string[] strPointers = 
            {
                txtKpI.Text,
                txtKiI.Text,
                txtKpW.Text,
                txtKiW.Text,
                txtKdW.Text,
            };

            int num = 0;
            if (rbTorqueControl.Checked == true)
                num = 2;
            else if (rbSpeedControl.Checked == true)
                num = strPointers.Length;
            else
                return true;

            double value = 0;
            for (int i = 0; i < num; i++)
            {
                try
                {
                    value = Convert.ToDouble(strPointers[i].Replace('.',','));
                }
                catch
                {
                    MessageBox.Show("Niedozwolony ciąg znaków.", "Błąd parametrów", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    return false;
                }
                if (!(value >= 0.0001 && value <= 100))
                {
                    MessageBox.Show("Wartość nastaw powinna mieścić się w zakresie <0.0001;100>", "Błąd parametrów", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    return false;
                }
            }

            return true;
        }

        /* Kontrola znaków */
        private void formatInputData(object sender, KeyPressEventArgs e)
        {
            /* Akceptowalne znaki to kropka, cyfry oraz Backspace */
            e.Handled = !char.IsDigit(e.KeyChar) &&
                e.KeyChar != (char)8 &&
                e.KeyChar != '.';

            TextBox txt = (TextBox)sender;

            /* Nie przyjmuj kropki na miejscu zerowym */
            if (string.IsNullOrWhiteSpace(txt.Text) && e.KeyChar == '.')
                e.Handled = true;

            /* Nie przyjmuj wszystkiego prócz kropki na pierwszym miejscu (gdy na zerowym jest zero)*/
            if (txt.Text.Length == 1 && e.KeyChar >= '0' && e.KeyChar <= '9' && txt.Text[0] == '0')
                e.Handled = true;
            
            /* Nie przyjmuj wiecej kropek niz 1 */
            if(txt.Text.Contains('.') && e.KeyChar == '.')
                e.Handled = true;

            /* Nie przyjmuj wiecej znaków niż 6 - dokładność do 4 miejsca po przecinku */
            if (txt.Text.Length >= 6 && e.KeyChar != (char)8)
                e.Handled = true;

        }

        /* Kontrola wprowadzanych danych dla pól prądu i prędkości */
        private void formatInputDataSpeedCurrent(object sender, KeyPressEventArgs e)
        {
            /* Cyfry i backspace */
            e.Handled = !char.IsDigit(e.KeyChar) &&
            e.KeyChar != (char)8;

            TextBox txt = (TextBox)sender;

            /* Zera na początku odrzucane */
            if (string.IsNullOrWhiteSpace(txt.Text) && e.KeyChar == '0')
                e.Handled = true;
        }

        private static Icon ResizeIcon(Icon icon, int width, int height)
        {
            Bitmap bitmap = new Bitmap(width, height);
            using (Graphics g = Graphics.FromImage(bitmap))
            {
                g.InterpolationMode = System.Drawing.Drawing2D.InterpolationMode.HighQualityBicubic;
                g.DrawImage(icon.ToBitmap(), new Rectangle(0,0,width,height));
            }
            return Icon.FromHandle(bitmap.GetHicon());
        }

        private void setPictureBoxIcon(object sender, PaintEventArgs e)
        {
            Icon ico = ResizeIcon(SystemIcons.Question, 20, 20);
            e.Graphics.DrawIcon(ico, 0, 0);
        }

        private void picKpIcon_MouseHover(object sender, EventArgs e)
        {
            ToolTip tt = new ToolTip();
            tt.SetToolTip(picKpI, "Info o nastawie Kp I");
        }

        private void picKiI_MouseHover(object sender, EventArgs e)
        {
            ToolTip tt = new ToolTip();
            tt.SetToolTip(picKiI, "Info o nastawie Ki I");
        }

        private void picKpOmega_MouseHover(object sender, EventArgs e)
        {
            ToolTip tt = new ToolTip();
            tt.SetToolTip(picKpOmega, "Info o nastawie Kp Omega");
        }

        private void picKiOmega_MouseHover(object sender, EventArgs e)
        {
            ToolTip tt = new ToolTip();
            tt.SetToolTip(picKiOmega, "Info o nastawie Ki Omega");
        }

        private void picKdOmega_MouseHover(object sender, EventArgs e)
        {
            ToolTip tt = new ToolTip();
            tt.SetToolTip(picKdOmega, "Info o nastawie Kd Omega");
        }

        private void txtDutyCycle_KeyPress(object sender, KeyPressEventArgs e)
        {
            /* Akceptowalne znaki to kropka, cyfry oraz Backspace */
            e.Handled = !char.IsDigit(e.KeyChar) &&
                e.KeyChar != (char)8;
        }

        private void txtDutyCycle_TextChanged(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(txtDutyCycle.Text))
            {
                checkDataToStartMotor(sender, e);
                return;
            }

            int value = Convert.ToInt32(txtDutyCycle.Text);

            if (value < 1)
                value = 1;
            else if (value > 100)
                value = 100;

            txtDutyCycle.Text = value.ToString();
            txtDutyCycle.Focus();
            txtDutyCycle.SelectionStart = txtDutyCycle.Text.Length;

            checkDataToStartMotor(sender, e);
        }
    }
}