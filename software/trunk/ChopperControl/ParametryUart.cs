using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ChopperControl
{
    public partial class ParametryUart : Form
    {
        public ParametryUart()
        {
            InitializeComponent();
            Bitmap bitmap1 = Bitmap.FromHicon(SystemIcons.Information.Handle);
            pictureBox1.Image = bitmap1;

            label1.Text = "Baud rate: 115200 b/s\n"+
                          "Bity danych: 8\n"+
                          "Bity parzystości: 0\n"+
                          "Bity stopu: 1\n";
        }

        private void button1_Click(object sender, EventArgs e)
        {
            pictureBox1.Dispose();
            this.Close();
        }
    }
}
