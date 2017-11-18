namespace ChopperControl
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.cbComList = new System.Windows.Forms.ComboBox();
            this.btnInit = new System.Windows.Forms.Button();
            this.labSelectComPort = new System.Windows.Forms.Label();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.rbPwmControl = new System.Windows.Forms.RadioButton();
            this.rbSpeedControl = new System.Windows.Forms.RadioButton();
            this.rbTorqueControl = new System.Windows.Forms.RadioButton();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.picKiI = new System.Windows.Forms.PictureBox();
            this.picKpI = new System.Windows.Forms.PictureBox();
            this.labKiI = new System.Windows.Forms.Label();
            this.labKpI = new System.Windows.Forms.Label();
            this.txtKiI = new System.Windows.Forms.TextBox();
            this.txtKpI = new System.Windows.Forms.TextBox();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.labKdW = new System.Windows.Forms.Label();
            this.picKdOmega = new System.Windows.Forms.PictureBox();
            this.picKiOmega = new System.Windows.Forms.PictureBox();
            this.picKpOmega = new System.Windows.Forms.PictureBox();
            this.txtKdW = new System.Windows.Forms.TextBox();
            this.labKiW = new System.Windows.Forms.Label();
            this.txtKpW = new System.Windows.Forms.TextBox();
            this.labKpW = new System.Windows.Forms.Label();
            this.txtKiW = new System.Windows.Forms.TextBox();
            this.btnStart = new System.Windows.Forms.Button();
            this.groupBox4 = new System.Windows.Forms.GroupBox();
            this.btnStop = new System.Windows.Forms.Button();
            this.txtIRef = new System.Windows.Forms.TextBox();
            this.labIRef = new System.Windows.Forms.Label();
            this.labSpeedRef = new System.Windows.Forms.Label();
            this.txtSpeedRef = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.groupBox5 = new System.Windows.Forms.GroupBox();
            this.label11 = new System.Windows.Forms.Label();
            this.label10 = new System.Windows.Forms.Label();
            this.txtDutyCycle = new System.Windows.Forms.TextBox();
            this.label5 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.cbFreq = new System.Windows.Forms.ComboBox();
            this.groupBox6 = new System.Windows.Forms.GroupBox();
            this.picUartStatus = new System.Windows.Forms.PictureBox();
            this.groupBox7 = new System.Windows.Forms.GroupBox();
            this.label7 = new System.Windows.Forms.Label();
            this.labSpeedMeas = new System.Windows.Forms.Label();
            this.label9 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.labCurrentMeas = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.btnUartInfo = new System.Windows.Forms.Button();
            this.groupBox9 = new System.Windows.Forms.GroupBox();
            this.groupBox8 = new System.Windows.Forms.GroupBox();
            this.txtCurrentLimit = new System.Windows.Forms.TextBox();
            this.label8 = new System.Windows.Forms.Label();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.picKiI)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.picKpI)).BeginInit();
            this.groupBox3.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.picKdOmega)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.picKiOmega)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.picKpOmega)).BeginInit();
            this.groupBox4.SuspendLayout();
            this.groupBox5.SuspendLayout();
            this.groupBox6.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.picUartStatus)).BeginInit();
            this.groupBox7.SuspendLayout();
            this.groupBox9.SuspendLayout();
            this.groupBox8.SuspendLayout();
            this.SuspendLayout();
            // 
            // textBox1
            // 
            this.textBox1.Location = new System.Drawing.Point(6, 19);
            this.textBox1.Multiline = true;
            this.textBox1.Name = "textBox1";
            this.textBox1.ReadOnly = true;
            this.textBox1.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.textBox1.Size = new System.Drawing.Size(235, 163);
            this.textBox1.TabIndex = 0;
            // 
            // cbComList
            // 
            this.cbComList.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cbComList.FormattingEnabled = true;
            this.cbComList.Location = new System.Drawing.Point(247, 33);
            this.cbComList.Name = "cbComList";
            this.cbComList.Size = new System.Drawing.Size(121, 21);
            this.cbComList.TabIndex = 1;
            this.cbComList.SelectedIndexChanged += new System.EventHandler(this.cbComList_SelectedIndexChanged);
            this.cbComList.Click += new System.EventHandler(this.cbComList_Click);
            // 
            // btnInit
            // 
            this.btnInit.Enabled = false;
            this.btnInit.Location = new System.Drawing.Point(247, 60);
            this.btnInit.Name = "btnInit";
            this.btnInit.Size = new System.Drawing.Size(121, 23);
            this.btnInit.TabIndex = 2;
            this.btnInit.Text = "Inicjalizuj port";
            this.btnInit.UseVisualStyleBackColor = true;
            this.btnInit.Click += new System.EventHandler(this.btnInit_Click);
            // 
            // labSelectComPort
            // 
            this.labSelectComPort.AutoSize = true;
            this.labSelectComPort.Location = new System.Drawing.Point(254, 17);
            this.labSelectComPort.Name = "labSelectComPort";
            this.labSelectComPort.Size = new System.Drawing.Size(55, 13);
            this.labSelectComPort.TabIndex = 4;
            this.labSelectComPort.Text = "COM port:";
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.rbPwmControl);
            this.groupBox1.Controls.Add(this.rbSpeedControl);
            this.groupBox1.Controls.Add(this.rbTorqueControl);
            this.groupBox1.Location = new System.Drawing.Point(450, 10);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(184, 81);
            this.groupBox1.TabIndex = 5;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Tryb pracy";
            // 
            // rbPwmControl
            // 
            this.rbPwmControl.AutoSize = true;
            this.rbPwmControl.Location = new System.Drawing.Point(10, 59);
            this.rbPwmControl.Name = "rbPwmControl";
            this.rbPwmControl.Size = new System.Drawing.Size(52, 17);
            this.rbPwmControl.TabIndex = 7;
            this.rbPwmControl.TabStop = true;
            this.rbPwmControl.Text = "PWM";
            this.rbPwmControl.UseVisualStyleBackColor = true;
            this.rbPwmControl.CheckedChanged += new System.EventHandler(this.rbControlChanged);
            // 
            // rbSpeedControl
            // 
            this.rbSpeedControl.AutoSize = true;
            this.rbSpeedControl.Location = new System.Drawing.Point(10, 39);
            this.rbSpeedControl.Name = "rbSpeedControl";
            this.rbSpeedControl.Size = new System.Drawing.Size(122, 17);
            this.rbSpeedControl.TabIndex = 6;
            this.rbSpeedControl.Text = "Regulacja prędkości";
            this.rbSpeedControl.UseVisualStyleBackColor = true;
            this.rbSpeedControl.CheckedChanged += new System.EventHandler(this.rbControlChanged);
            // 
            // rbTorqueControl
            // 
            this.rbTorqueControl.AutoSize = true;
            this.rbTorqueControl.Checked = true;
            this.rbTorqueControl.Location = new System.Drawing.Point(10, 19);
            this.rbTorqueControl.Name = "rbTorqueControl";
            this.rbTorqueControl.Size = new System.Drawing.Size(119, 17);
            this.rbTorqueControl.TabIndex = 6;
            this.rbTorqueControl.TabStop = true;
            this.rbTorqueControl.Text = "Regulacja momentu";
            this.rbTorqueControl.UseVisualStyleBackColor = true;
            this.rbTorqueControl.CheckedChanged += new System.EventHandler(this.rbControlChanged);
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.picKiI);
            this.groupBox2.Controls.Add(this.picKpI);
            this.groupBox2.Controls.Add(this.labKiI);
            this.groupBox2.Controls.Add(this.labKpI);
            this.groupBox2.Controls.Add(this.txtKiI);
            this.groupBox2.Controls.Add(this.txtKpI);
            this.groupBox2.Location = new System.Drawing.Point(12, 195);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(138, 158);
            this.groupBox2.TabIndex = 6;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Regulator prądu";
            // 
            // picKiI
            // 
            this.picKiI.Location = new System.Drawing.Point(109, 85);
            this.picKiI.Name = "picKiI";
            this.picKiI.Size = new System.Drawing.Size(20, 20);
            this.picKiI.TabIndex = 2;
            this.picKiI.TabStop = false;
            this.picKiI.Paint += new System.Windows.Forms.PaintEventHandler(this.setPictureBoxIcon);
            this.picKiI.MouseHover += new System.EventHandler(this.picKiI_MouseHover);
            // 
            // picKpI
            // 
            this.picKpI.Location = new System.Drawing.Point(109, 46);
            this.picKpI.Name = "picKpI";
            this.picKpI.Size = new System.Drawing.Size(20, 20);
            this.picKpI.TabIndex = 2;
            this.picKpI.TabStop = false;
            this.picKpI.Paint += new System.Windows.Forms.PaintEventHandler(this.setPictureBoxIcon);
            this.picKpI.MouseHover += new System.EventHandler(this.picKpIcon_MouseHover);
            // 
            // labKiI
            // 
            this.labKiI.AutoSize = true;
            this.labKiI.Location = new System.Drawing.Point(6, 69);
            this.labKiI.Name = "labKiI";
            this.labKiI.Size = new System.Drawing.Size(16, 13);
            this.labKiI.TabIndex = 1;
            this.labKiI.Text = "Ti";
            // 
            // labKpI
            // 
            this.labKpI.AutoSize = true;
            this.labKpI.Location = new System.Drawing.Point(6, 30);
            this.labKpI.Name = "labKpI";
            this.labKpI.Size = new System.Drawing.Size(20, 13);
            this.labKpI.TabIndex = 1;
            this.labKpI.Text = "Kp";
            // 
            // txtKiI
            // 
            this.txtKiI.Location = new System.Drawing.Point(6, 85);
            this.txtKiI.Name = "txtKiI";
            this.txtKiI.Size = new System.Drawing.Size(100, 20);
            this.txtKiI.TabIndex = 0;
            this.txtKiI.Text = "3";
            this.txtKiI.TextChanged += new System.EventHandler(this.checkDataToStartMotor);
            this.txtKiI.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.formatInputData);
            // 
            // txtKpI
            // 
            this.txtKpI.Location = new System.Drawing.Point(6, 46);
            this.txtKpI.Name = "txtKpI";
            this.txtKpI.Size = new System.Drawing.Size(100, 20);
            this.txtKpI.TabIndex = 0;
            this.txtKpI.Text = "0.5";
            this.txtKpI.TextChanged += new System.EventHandler(this.checkDataToStartMotor);
            this.txtKpI.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.formatInputData);
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.labKdW);
            this.groupBox3.Controls.Add(this.picKdOmega);
            this.groupBox3.Controls.Add(this.picKiOmega);
            this.groupBox3.Controls.Add(this.picKpOmega);
            this.groupBox3.Controls.Add(this.txtKdW);
            this.groupBox3.Controls.Add(this.labKiW);
            this.groupBox3.Controls.Add(this.txtKpW);
            this.groupBox3.Controls.Add(this.labKpW);
            this.groupBox3.Controls.Add(this.txtKiW);
            this.groupBox3.Location = new System.Drawing.Point(150, 195);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(143, 158);
            this.groupBox3.TabIndex = 7;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "Regulator prędkości";
            // 
            // labKdW
            // 
            this.labKdW.AutoSize = true;
            this.labKdW.Location = new System.Drawing.Point(6, 111);
            this.labKdW.Name = "labKdW";
            this.labKdW.Size = new System.Drawing.Size(20, 13);
            this.labKdW.TabIndex = 1;
            this.labKdW.Text = "Td";
            // 
            // picKdOmega
            // 
            this.picKdOmega.Location = new System.Drawing.Point(109, 127);
            this.picKdOmega.Name = "picKdOmega";
            this.picKdOmega.Size = new System.Drawing.Size(20, 20);
            this.picKdOmega.TabIndex = 2;
            this.picKdOmega.TabStop = false;
            this.picKdOmega.Paint += new System.Windows.Forms.PaintEventHandler(this.setPictureBoxIcon);
            this.picKdOmega.MouseHover += new System.EventHandler(this.picKdOmega_MouseHover);
            // 
            // picKiOmega
            // 
            this.picKiOmega.Location = new System.Drawing.Point(109, 85);
            this.picKiOmega.Name = "picKiOmega";
            this.picKiOmega.Size = new System.Drawing.Size(20, 20);
            this.picKiOmega.TabIndex = 2;
            this.picKiOmega.TabStop = false;
            this.picKiOmega.Paint += new System.Windows.Forms.PaintEventHandler(this.setPictureBoxIcon);
            this.picKiOmega.MouseHover += new System.EventHandler(this.picKiOmega_MouseHover);
            // 
            // picKpOmega
            // 
            this.picKpOmega.Location = new System.Drawing.Point(109, 46);
            this.picKpOmega.Name = "picKpOmega";
            this.picKpOmega.Size = new System.Drawing.Size(20, 20);
            this.picKpOmega.TabIndex = 2;
            this.picKpOmega.TabStop = false;
            this.picKpOmega.Paint += new System.Windows.Forms.PaintEventHandler(this.setPictureBoxIcon);
            this.picKpOmega.MouseHover += new System.EventHandler(this.picKpOmega_MouseHover);
            // 
            // txtKdW
            // 
            this.txtKdW.Location = new System.Drawing.Point(6, 127);
            this.txtKdW.Name = "txtKdW";
            this.txtKdW.Size = new System.Drawing.Size(100, 20);
            this.txtKdW.TabIndex = 0;
            this.txtKdW.Text = "0.0001";
            this.txtKdW.TextChanged += new System.EventHandler(this.checkDataToStartMotor);
            this.txtKdW.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.formatInputData);
            // 
            // labKiW
            // 
            this.labKiW.AutoSize = true;
            this.labKiW.Location = new System.Drawing.Point(6, 69);
            this.labKiW.Name = "labKiW";
            this.labKiW.Size = new System.Drawing.Size(16, 13);
            this.labKiW.TabIndex = 1;
            this.labKiW.Text = "Ti";
            // 
            // txtKpW
            // 
            this.txtKpW.Location = new System.Drawing.Point(6, 46);
            this.txtKpW.Name = "txtKpW";
            this.txtKpW.Size = new System.Drawing.Size(100, 20);
            this.txtKpW.TabIndex = 0;
            this.txtKpW.Text = "5";
            this.txtKpW.TextChanged += new System.EventHandler(this.checkDataToStartMotor);
            this.txtKpW.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.formatInputData);
            // 
            // labKpW
            // 
            this.labKpW.AutoSize = true;
            this.labKpW.Location = new System.Drawing.Point(6, 30);
            this.labKpW.Name = "labKpW";
            this.labKpW.Size = new System.Drawing.Size(20, 13);
            this.labKpW.TabIndex = 1;
            this.labKpW.Text = "Kp";
            // 
            // txtKiW
            // 
            this.txtKiW.Location = new System.Drawing.Point(6, 85);
            this.txtKiW.Name = "txtKiW";
            this.txtKiW.Size = new System.Drawing.Size(100, 20);
            this.txtKiW.TabIndex = 0;
            this.txtKiW.Text = "0.4";
            this.txtKiW.TextChanged += new System.EventHandler(this.checkDataToStartMotor);
            this.txtKiW.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.formatInputData);
            // 
            // btnStart
            // 
            this.btnStart.Enabled = false;
            this.btnStart.Location = new System.Drawing.Point(6, 19);
            this.btnStart.Name = "btnStart";
            this.btnStart.Size = new System.Drawing.Size(75, 23);
            this.btnStart.TabIndex = 8;
            this.btnStart.Text = "START";
            this.btnStart.UseVisualStyleBackColor = true;
            this.btnStart.Click += new System.EventHandler(this.btnStart_Click);
            // 
            // groupBox4
            // 
            this.groupBox4.Controls.Add(this.btnStop);
            this.groupBox4.Controls.Add(this.btnStart);
            this.groupBox4.Location = new System.Drawing.Point(450, 97);
            this.groupBox4.Name = "groupBox4";
            this.groupBox4.Size = new System.Drawing.Size(184, 53);
            this.groupBox4.TabIndex = 9;
            this.groupBox4.TabStop = false;
            this.groupBox4.Text = "Stan silnika";
            // 
            // btnStop
            // 
            this.btnStop.Enabled = false;
            this.btnStop.Location = new System.Drawing.Point(103, 19);
            this.btnStop.Name = "btnStop";
            this.btnStop.Size = new System.Drawing.Size(75, 23);
            this.btnStop.TabIndex = 8;
            this.btnStop.Text = "STOP";
            this.btnStop.UseVisualStyleBackColor = true;
            this.btnStop.Click += new System.EventHandler(this.btnStop_Click);
            // 
            // txtIRef
            // 
            this.txtIRef.Location = new System.Drawing.Point(15, 30);
            this.txtIRef.Name = "txtIRef";
            this.txtIRef.Size = new System.Drawing.Size(100, 20);
            this.txtIRef.TabIndex = 10;
            this.txtIRef.TextChanged += new System.EventHandler(this.checkDataToStartMotor);
            this.txtIRef.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.formatInputDataSpeedCurrent);
            // 
            // labIRef
            // 
            this.labIRef.AutoSize = true;
            this.labIRef.Location = new System.Drawing.Point(13, 15);
            this.labIRef.Name = "labIRef";
            this.labIRef.Size = new System.Drawing.Size(29, 13);
            this.labIRef.TabIndex = 11;
            this.labIRef.Text = "Prąd";
            // 
            // labSpeedRef
            // 
            this.labSpeedRef.AutoSize = true;
            this.labSpeedRef.Location = new System.Drawing.Point(12, 59);
            this.labSpeedRef.Name = "labSpeedRef";
            this.labSpeedRef.Size = new System.Drawing.Size(52, 13);
            this.labSpeedRef.TabIndex = 13;
            this.labSpeedRef.Text = "Prędkość";
            // 
            // txtSpeedRef
            // 
            this.txtSpeedRef.Location = new System.Drawing.Point(14, 74);
            this.txtSpeedRef.Name = "txtSpeedRef";
            this.txtSpeedRef.Size = new System.Drawing.Size(100, 20);
            this.txtSpeedRef.TabIndex = 12;
            this.txtSpeedRef.TextChanged += new System.EventHandler(this.checkDataToStartMotor);
            this.txtSpeedRef.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.formatInputDataSpeedCurrent);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(120, 36);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(14, 13);
            this.label1.TabIndex = 14;
            this.label1.Text = "A";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(120, 77);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(43, 13);
            this.label2.TabIndex = 14;
            this.label2.Text = "obr/min";
            // 
            // groupBox5
            // 
            this.groupBox5.Controls.Add(this.label11);
            this.groupBox5.Controls.Add(this.label10);
            this.groupBox5.Controls.Add(this.txtDutyCycle);
            this.groupBox5.Controls.Add(this.label5);
            this.groupBox5.Controls.Add(this.label4);
            this.groupBox5.Controls.Add(this.cbFreq);
            this.groupBox5.Location = new System.Drawing.Point(479, 156);
            this.groupBox5.Name = "groupBox5";
            this.groupBox5.Size = new System.Drawing.Size(155, 116);
            this.groupBox5.TabIndex = 17;
            this.groupBox5.TabStop = false;
            this.groupBox5.Text = "PWM";
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(13, 74);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(67, 13);
            this.label11.TabIndex = 4;
            this.label11.Text = "Wypełnienie";
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(11, 20);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(71, 13);
            this.label10.TabIndex = 3;
            this.label10.Text = "Częstotliwość";
            // 
            // txtDutyCycle
            // 
            this.txtDutyCycle.Location = new System.Drawing.Point(16, 90);
            this.txtDutyCycle.Name = "txtDutyCycle";
            this.txtDutyCycle.Size = new System.Drawing.Size(92, 20);
            this.txtDutyCycle.TabIndex = 2;
            this.txtDutyCycle.TextChanged += new System.EventHandler(this.txtDutyCycle_TextChanged);
            this.txtDutyCycle.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.txtDutyCycle_KeyPress);
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(123, 93);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(15, 13);
            this.label5.TabIndex = 1;
            this.label5.Text = "%";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(123, 42);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(20, 13);
            this.label4.TabIndex = 1;
            this.label4.Text = "Hz";
            // 
            // cbFreq
            // 
            this.cbFreq.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cbFreq.FormattingEnabled = true;
            this.cbFreq.Items.AddRange(new object[] {
            "500",
            "1000",
            "1500",
            "2000",
            "2500",
            "3000",
            "3500",
            "4000",
            "4500",
            "5000",
            "5500",
            "6000",
            "6500",
            "7000",
            "7500",
            "8000",
            "8500",
            "9000",
            "9500",
            "10000"});
            this.cbFreq.Location = new System.Drawing.Point(16, 39);
            this.cbFreq.Name = "cbFreq";
            this.cbFreq.Size = new System.Drawing.Size(92, 21);
            this.cbFreq.TabIndex = 0;
            this.cbFreq.SelectedIndexChanged += new System.EventHandler(this.checkDataToStartMotor);
            // 
            // groupBox6
            // 
            this.groupBox6.Controls.Add(this.txtSpeedRef);
            this.groupBox6.Controls.Add(this.txtIRef);
            this.groupBox6.Controls.Add(this.label2);
            this.groupBox6.Controls.Add(this.label1);
            this.groupBox6.Controls.Add(this.labIRef);
            this.groupBox6.Controls.Add(this.labSpeedRef);
            this.groupBox6.Location = new System.Drawing.Point(299, 195);
            this.groupBox6.Name = "groupBox6";
            this.groupBox6.Size = new System.Drawing.Size(174, 105);
            this.groupBox6.TabIndex = 18;
            this.groupBox6.TabStop = false;
            this.groupBox6.Text = "Wartości zadane";
            // 
            // picUartStatus
            // 
            this.picUartStatus.Location = new System.Drawing.Point(374, 33);
            this.picUartStatus.Name = "picUartStatus";
            this.picUartStatus.Size = new System.Drawing.Size(20, 20);
            this.picUartStatus.TabIndex = 19;
            this.picUartStatus.TabStop = false;
            // 
            // groupBox7
            // 
            this.groupBox7.Controls.Add(this.label7);
            this.groupBox7.Controls.Add(this.labSpeedMeas);
            this.groupBox7.Controls.Add(this.label9);
            this.groupBox7.Controls.Add(this.label6);
            this.groupBox7.Controls.Add(this.labCurrentMeas);
            this.groupBox7.Controls.Add(this.label3);
            this.groupBox7.Location = new System.Drawing.Point(479, 278);
            this.groupBox7.Name = "groupBox7";
            this.groupBox7.Size = new System.Drawing.Size(155, 73);
            this.groupBox7.TabIndex = 20;
            this.groupBox7.TabStop = false;
            this.groupBox7.Text = "Wartości mierzone";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(105, 48);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(43, 13);
            this.label7.TabIndex = 1;
            this.label7.Text = "obr/min";
            // 
            // labSpeedMeas
            // 
            this.labSpeedMeas.AutoSize = true;
            this.labSpeedMeas.Location = new System.Drawing.Point(69, 48);
            this.labSpeedMeas.Name = "labSpeedMeas";
            this.labSpeedMeas.Size = new System.Drawing.Size(13, 13);
            this.labSpeedMeas.TabIndex = 2;
            this.labSpeedMeas.Text = "0";
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(6, 48);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(55, 13);
            this.label9.TabIndex = 3;
            this.label9.Text = "Prędkość:";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(105, 25);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(14, 13);
            this.label6.TabIndex = 0;
            this.label6.Text = "A";
            // 
            // labCurrentMeas
            // 
            this.labCurrentMeas.AutoSize = true;
            this.labCurrentMeas.Location = new System.Drawing.Point(69, 25);
            this.labCurrentMeas.Name = "labCurrentMeas";
            this.labCurrentMeas.Size = new System.Drawing.Size(28, 13);
            this.labCurrentMeas.TabIndex = 0;
            this.labCurrentMeas.Text = "0.00";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(6, 25);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(32, 13);
            this.label3.TabIndex = 0;
            this.label3.Text = "Prąd:";
            // 
            // btnUartInfo
            // 
            this.btnUartInfo.Location = new System.Drawing.Point(247, 92);
            this.btnUartInfo.Name = "btnUartInfo";
            this.btnUartInfo.Size = new System.Drawing.Size(121, 23);
            this.btnUartInfo.TabIndex = 21;
            this.btnUartInfo.Text = "Parametry UART";
            this.btnUartInfo.UseVisualStyleBackColor = true;
            this.btnUartInfo.Click += new System.EventHandler(this.btnUartInfo_Click);
            // 
            // groupBox9
            // 
            this.groupBox9.Controls.Add(this.cbComList);
            this.groupBox9.Controls.Add(this.textBox1);
            this.groupBox9.Controls.Add(this.labSelectComPort);
            this.groupBox9.Controls.Add(this.picUartStatus);
            this.groupBox9.Controls.Add(this.btnUartInfo);
            this.groupBox9.Controls.Add(this.btnInit);
            this.groupBox9.Location = new System.Drawing.Point(12, 1);
            this.groupBox9.Name = "groupBox9";
            this.groupBox9.Size = new System.Drawing.Size(402, 188);
            this.groupBox9.TabIndex = 24;
            this.groupBox9.TabStop = false;
            this.groupBox9.Text = "Komunikacja";
            // 
            // groupBox8
            // 
            this.groupBox8.Controls.Add(this.txtCurrentLimit);
            this.groupBox8.Controls.Add(this.label8);
            this.groupBox8.Location = new System.Drawing.Point(299, 303);
            this.groupBox8.Name = "groupBox8";
            this.groupBox8.Size = new System.Drawing.Size(174, 50);
            this.groupBox8.TabIndex = 18;
            this.groupBox8.TabStop = false;
            this.groupBox8.Text = "Ograniczenie prądu";
            // 
            // txtCurrentLimit
            // 
            this.txtCurrentLimit.Location = new System.Drawing.Point(14, 19);
            this.txtCurrentLimit.Name = "txtCurrentLimit";
            this.txtCurrentLimit.Size = new System.Drawing.Size(100, 20);
            this.txtCurrentLimit.TabIndex = 10;
            this.txtCurrentLimit.Text = "15";
            this.txtCurrentLimit.TextChanged += new System.EventHandler(this.checkDataToStartMotor);
            this.txtCurrentLimit.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.formatInputDataSpeedCurrent);
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(120, 22);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(14, 13);
            this.label8.TabIndex = 14;
            this.label8.Text = "A";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(642, 365);
            this.Controls.Add(this.groupBox9);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.groupBox7);
            this.Controls.Add(this.groupBox8);
            this.Controls.Add(this.groupBox6);
            this.Controls.Add(this.groupBox5);
            this.Controls.Add(this.groupBox4);
            this.Controls.Add(this.groupBox3);
            this.Controls.Add(this.groupBox2);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.MaximizeBox = false;
            this.Name = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.picKiI)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.picKpI)).EndInit();
            this.groupBox3.ResumeLayout(false);
            this.groupBox3.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.picKdOmega)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.picKiOmega)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.picKpOmega)).EndInit();
            this.groupBox4.ResumeLayout(false);
            this.groupBox5.ResumeLayout(false);
            this.groupBox5.PerformLayout();
            this.groupBox6.ResumeLayout(false);
            this.groupBox6.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.picUartStatus)).EndInit();
            this.groupBox7.ResumeLayout(false);
            this.groupBox7.PerformLayout();
            this.groupBox9.ResumeLayout(false);
            this.groupBox9.PerformLayout();
            this.groupBox8.ResumeLayout(false);
            this.groupBox8.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.TextBox textBox1;
        private System.Windows.Forms.ComboBox cbComList;
        private System.Windows.Forms.Button btnInit;
        private System.Windows.Forms.Label labSelectComPort;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.RadioButton rbTorqueControl;
        private System.Windows.Forms.RadioButton rbSpeedControl;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.Label labKpI;
        private System.Windows.Forms.TextBox txtKiI;
        private System.Windows.Forms.TextBox txtKpI;
        private System.Windows.Forms.Label labKiI;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.Label labKdW;
        private System.Windows.Forms.TextBox txtKdW;
        private System.Windows.Forms.Label labKiW;
        private System.Windows.Forms.TextBox txtKpW;
        private System.Windows.Forms.Label labKpW;
        private System.Windows.Forms.TextBox txtKiW;
        private System.Windows.Forms.Button btnStart;
        private System.Windows.Forms.GroupBox groupBox4;
        private System.Windows.Forms.Button btnStop;
        private System.Windows.Forms.TextBox txtIRef;
        private System.Windows.Forms.Label labIRef;
        private System.Windows.Forms.Label labSpeedRef;
        private System.Windows.Forms.TextBox txtSpeedRef;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.GroupBox groupBox5;
        private System.Windows.Forms.ComboBox cbFreq;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.GroupBox groupBox6;
        private System.Windows.Forms.PictureBox picUartStatus;
        private System.Windows.Forms.GroupBox groupBox7;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label labSpeedMeas;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label labCurrentMeas;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Button btnUartInfo;
        private System.Windows.Forms.PictureBox picKpI;
        private System.Windows.Forms.PictureBox picKiI;
        private System.Windows.Forms.PictureBox picKpOmega;
        private System.Windows.Forms.PictureBox picKiOmega;
        private System.Windows.Forms.PictureBox picKdOmega;
        private System.Windows.Forms.GroupBox groupBox9;
        private System.Windows.Forms.GroupBox groupBox8;
        private System.Windows.Forms.TextBox txtCurrentLimit;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.RadioButton rbPwmControl;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.TextBox txtDutyCycle;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.Label label11;
    }
}

