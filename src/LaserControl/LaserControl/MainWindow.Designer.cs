namespace LaserControl
{
    partial class MainWindow
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
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MainWindow));
            this.serialPort = new System.IO.Ports.SerialPort(this.components);
            this.btnConnect = new System.Windows.Forms.Button();
            this.lblBaudRate = new System.Windows.Forms.Label();
            this.lblPorts = new System.Windows.Forms.Label();
            this.baudRate = new System.Windows.Forms.ComboBox();
            this.ports = new System.Windows.Forms.ComboBox();
            this.panelControl = new System.Windows.Forms.Panel();
            this.star = new System.Windows.Forms.Button();
            this.heart = new System.Windows.Forms.Button();
            this.smiley = new System.Windows.Forms.Button();
            this.manFigure = new System.Windows.Forms.Button();
            this.line4 = new System.Windows.Forms.Button();
            this.line3 = new System.Windows.Forms.Button();
            this.line2 = new System.Windows.Forms.Button();
            this.line1 = new System.Windows.Forms.Button();
            this.triangle2 = new System.Windows.Forms.Button();
            this.triangle1 = new System.Windows.Forms.Button();
            this.cross2 = new System.Windows.Forms.Button();
            this.cross1 = new System.Windows.Forms.Button();
            this.btnStop = new System.Windows.Forms.Button();
            this.speedControl = new System.Windows.Forms.GroupBox();
            this.btnFixedSpeed = new System.Windows.Forms.Button();
            this.btnDecrease = new System.Windows.Forms.Button();
            this.btnIncrease = new System.Windows.Forms.Button();
            this.btnRandomSpeed = new System.Windows.Forms.Button();
            this.square4 = new System.Windows.Forms.Button();
            this.square3 = new System.Windows.Forms.Button();
            this.square2 = new System.Windows.Forms.Button();
            this.square1 = new System.Windows.Forms.Button();
            this.Incoming = new System.Windows.Forms.RichTextBox();
            this.calibrationBox = new System.Windows.Forms.GroupBox();
            this.btnCalibrate = new System.Windows.Forms.Button();
            this.connectionBox = new System.Windows.Forms.GroupBox();
            this.connectionStatusText = new System.Windows.Forms.Label();
            this.connectionStatus = new System.Windows.Forms.Panel();
            this.laserControlBox = new System.Windows.Forms.GroupBox();
            this.laserStatusText = new System.Windows.Forms.Label();
            this.laserStatus = new System.Windows.Forms.Panel();
            this.btnLaser = new System.Windows.Forms.Button();
            this.menuStrip = new System.Windows.Forms.MenuStrip();
            this.menuToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.exitToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.helpToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.aboutToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.label1 = new System.Windows.Forms.Label();
            this.stanleptojectscom = new System.Windows.Forms.LinkLabel();
            this.footer = new System.Windows.Forms.Panel();
            this.panelControl.SuspendLayout();
            this.speedControl.SuspendLayout();
            this.calibrationBox.SuspendLayout();
            this.connectionBox.SuspendLayout();
            this.laserControlBox.SuspendLayout();
            this.menuStrip.SuspendLayout();
            this.footer.SuspendLayout();
            this.SuspendLayout();
            // 
            // serialPort
            // 
            this.serialPort.PortName = "COM3";
            this.serialPort.DataReceived += new System.IO.Ports.SerialDataReceivedEventHandler(this.serialPort_DataReceived);
            // 
            // btnConnect
            // 
            resources.ApplyResources(this.btnConnect, "btnConnect");
            this.btnConnect.Name = "btnConnect";
            this.btnConnect.UseVisualStyleBackColor = true;
            this.btnConnect.Click += new System.EventHandler(this.btnConnect_Click);
            // 
            // lblBaudRate
            // 
            resources.ApplyResources(this.lblBaudRate, "lblBaudRate");
            this.lblBaudRate.Name = "lblBaudRate";
            // 
            // lblPorts
            // 
            resources.ApplyResources(this.lblPorts, "lblPorts");
            this.lblPorts.Name = "lblPorts";
            // 
            // baudRate
            // 
            this.baudRate.FormattingEnabled = true;
            resources.ApplyResources(this.baudRate, "baudRate");
            this.baudRate.Name = "baudRate";
            // 
            // ports
            // 
            this.ports.FormattingEnabled = true;
            resources.ApplyResources(this.ports, "ports");
            this.ports.Name = "ports";
            // 
            // panelControl
            // 
            this.panelControl.Controls.Add(this.star);
            this.panelControl.Controls.Add(this.heart);
            this.panelControl.Controls.Add(this.smiley);
            this.panelControl.Controls.Add(this.manFigure);
            this.panelControl.Controls.Add(this.line4);
            this.panelControl.Controls.Add(this.line3);
            this.panelControl.Controls.Add(this.line2);
            this.panelControl.Controls.Add(this.line1);
            this.panelControl.Controls.Add(this.triangle2);
            this.panelControl.Controls.Add(this.triangle1);
            this.panelControl.Controls.Add(this.cross2);
            this.panelControl.Controls.Add(this.cross1);
            this.panelControl.Controls.Add(this.btnStop);
            this.panelControl.Controls.Add(this.speedControl);
            this.panelControl.Controls.Add(this.square4);
            this.panelControl.Controls.Add(this.square3);
            this.panelControl.Controls.Add(this.square2);
            this.panelControl.Controls.Add(this.square1);
            this.panelControl.Controls.Add(this.Incoming);
            this.panelControl.Controls.Add(this.calibrationBox);
            this.panelControl.Controls.Add(this.connectionBox);
            this.panelControl.Controls.Add(this.laserControlBox);
            this.panelControl.Controls.Add(this.menuStrip);
            resources.ApplyResources(this.panelControl, "panelControl");
            this.panelControl.ForeColor = System.Drawing.SystemColors.ControlText;
            this.panelControl.Name = "panelControl";
            // 
            // star
            // 
            this.star.BackColor = System.Drawing.Color.Black;
            resources.ApplyResources(this.star, "star");
            this.star.Image = global::LaserControl.Properties.Resources.star;
            this.star.Name = "star";
            this.star.UseVisualStyleBackColor = false;
            this.star.Click += new System.EventHandler(this.star_Click);
            // 
            // heart
            // 
            this.heart.BackColor = System.Drawing.Color.Black;
            resources.ApplyResources(this.heart, "heart");
            this.heart.Image = global::LaserControl.Properties.Resources.heart;
            this.heart.Name = "heart";
            this.heart.UseVisualStyleBackColor = false;
            this.heart.Click += new System.EventHandler(this.heart_Click);
            // 
            // smiley
            // 
            this.smiley.BackColor = System.Drawing.Color.Black;
            resources.ApplyResources(this.smiley, "smiley");
            this.smiley.Image = global::LaserControl.Properties.Resources.smiley;
            this.smiley.Name = "smiley";
            this.smiley.UseVisualStyleBackColor = false;
            this.smiley.Click += new System.EventHandler(this.smiley_Click);
            // 
            // manFigure
            // 
            this.manFigure.BackColor = System.Drawing.Color.Black;
            resources.ApplyResources(this.manFigure, "manFigure");
            this.manFigure.Image = global::LaserControl.Properties.Resources.figureMan;
            this.manFigure.Name = "manFigure";
            this.manFigure.UseVisualStyleBackColor = false;
            this.manFigure.Click += new System.EventHandler(this.manFigure_Click);
            // 
            // line4
            // 
            this.line4.BackColor = System.Drawing.Color.Black;
            resources.ApplyResources(this.line4, "line4");
            this.line4.ForeColor = System.Drawing.SystemColors.ControlText;
            this.line4.Image = global::LaserControl.Properties.Resources.line4;
            this.line4.Name = "line4";
            this.line4.UseVisualStyleBackColor = false;
            this.line4.Click += new System.EventHandler(this.line4_Click);
            // 
            // line3
            // 
            this.line3.BackColor = System.Drawing.Color.Black;
            resources.ApplyResources(this.line3, "line3");
            this.line3.Image = global::LaserControl.Properties.Resources.line3;
            this.line3.Name = "line3";
            this.line3.UseVisualStyleBackColor = false;
            this.line3.Click += new System.EventHandler(this.line3_Click);
            // 
            // line2
            // 
            this.line2.BackColor = System.Drawing.Color.Black;
            resources.ApplyResources(this.line2, "line2");
            this.line2.Image = global::LaserControl.Properties.Resources.line2;
            this.line2.Name = "line2";
            this.line2.UseVisualStyleBackColor = false;
            this.line2.Click += new System.EventHandler(this.line2_Click);
            // 
            // line1
            // 
            this.line1.BackColor = System.Drawing.Color.Black;
            resources.ApplyResources(this.line1, "line1");
            this.line1.Image = global::LaserControl.Properties.Resources.line1;
            this.line1.Name = "line1";
            this.line1.UseVisualStyleBackColor = false;
            this.line1.Click += new System.EventHandler(this.line1_Click);
            // 
            // triangle2
            // 
            this.triangle2.BackColor = System.Drawing.Color.Black;
            resources.ApplyResources(this.triangle2, "triangle2");
            this.triangle2.Image = global::LaserControl.Properties.Resources.cicuska;
            this.triangle2.Name = "triangle2";
            this.triangle2.UseVisualStyleBackColor = false;
            this.triangle2.Click += new System.EventHandler(this.triangle2_Click);
            // 
            // triangle1
            // 
            this.triangle1.BackColor = System.Drawing.Color.Black;
            resources.ApplyResources(this.triangle1, "triangle1");
            this.triangle1.Image = global::LaserControl.Properties.Resources.triangle;
            this.triangle1.Name = "triangle1";
            this.triangle1.UseVisualStyleBackColor = false;
            this.triangle1.Click += new System.EventHandler(this.triangle1_Click);
            // 
            // cross2
            // 
            this.cross2.BackColor = System.Drawing.Color.Black;
            resources.ApplyResources(this.cross2, "cross2");
            this.cross2.Image = global::LaserControl.Properties.Resources.cross2;
            this.cross2.Name = "cross2";
            this.cross2.UseVisualStyleBackColor = false;
            this.cross2.Click += new System.EventHandler(this.cross2_Click);
            // 
            // cross1
            // 
            this.cross1.BackColor = System.Drawing.Color.Black;
            resources.ApplyResources(this.cross1, "cross1");
            this.cross1.Image = global::LaserControl.Properties.Resources.cross1;
            this.cross1.Name = "cross1";
            this.cross1.UseVisualStyleBackColor = false;
            this.cross1.Click += new System.EventHandler(this.cross1_Click);
            // 
            // btnStop
            // 
            this.btnStop.BackColor = System.Drawing.Color.Red;
            resources.ApplyResources(this.btnStop, "btnStop");
            this.btnStop.ForeColor = System.Drawing.Color.Black;
            this.btnStop.Name = "btnStop";
            this.btnStop.UseVisualStyleBackColor = false;
            this.btnStop.Click += new System.EventHandler(this.btnStop_Click);
            // 
            // speedControl
            // 
            this.speedControl.Controls.Add(this.btnFixedSpeed);
            this.speedControl.Controls.Add(this.btnDecrease);
            this.speedControl.Controls.Add(this.btnIncrease);
            this.speedControl.Controls.Add(this.btnRandomSpeed);
            resources.ApplyResources(this.speedControl, "speedControl");
            this.speedControl.Name = "speedControl";
            this.speedControl.TabStop = false;
            // 
            // btnFixedSpeed
            // 
            resources.ApplyResources(this.btnFixedSpeed, "btnFixedSpeed");
            this.btnFixedSpeed.Name = "btnFixedSpeed";
            this.btnFixedSpeed.UseVisualStyleBackColor = true;
            this.btnFixedSpeed.Click += new System.EventHandler(this.btnFixedSpeed_Click);
            // 
            // btnDecrease
            // 
            resources.ApplyResources(this.btnDecrease, "btnDecrease");
            this.btnDecrease.Name = "btnDecrease";
            this.btnDecrease.UseVisualStyleBackColor = true;
            this.btnDecrease.Click += new System.EventHandler(this.btnDecrease_Click);
            // 
            // btnIncrease
            // 
            resources.ApplyResources(this.btnIncrease, "btnIncrease");
            this.btnIncrease.Name = "btnIncrease";
            this.btnIncrease.UseVisualStyleBackColor = true;
            this.btnIncrease.Click += new System.EventHandler(this.btnIncrease_Click);
            // 
            // btnRandomSpeed
            // 
            resources.ApplyResources(this.btnRandomSpeed, "btnRandomSpeed");
            this.btnRandomSpeed.Name = "btnRandomSpeed";
            this.btnRandomSpeed.UseVisualStyleBackColor = true;
            this.btnRandomSpeed.Click += new System.EventHandler(this.btnRandomSpeed_Click);
            // 
            // square4
            // 
            this.square4.BackColor = System.Drawing.Color.Black;
            resources.ApplyResources(this.square4, "square4");
            this.square4.Image = global::LaserControl.Properties.Resources.square4;
            this.square4.Name = "square4";
            this.square4.UseVisualStyleBackColor = false;
            this.square4.Click += new System.EventHandler(this.square4_Click);
            // 
            // square3
            // 
            this.square3.BackColor = System.Drawing.Color.Black;
            resources.ApplyResources(this.square3, "square3");
            this.square3.Image = global::LaserControl.Properties.Resources.square3;
            this.square3.Name = "square3";
            this.square3.UseVisualStyleBackColor = false;
            this.square3.Click += new System.EventHandler(this.square3_Click);
            // 
            // square2
            // 
            this.square2.BackColor = System.Drawing.Color.Black;
            resources.ApplyResources(this.square2, "square2");
            this.square2.Image = global::LaserControl.Properties.Resources.square2;
            this.square2.Name = "square2";
            this.square2.UseVisualStyleBackColor = false;
            this.square2.Click += new System.EventHandler(this.square2_Click);
            // 
            // square1
            // 
            this.square1.BackColor = System.Drawing.Color.Black;
            resources.ApplyResources(this.square1, "square1");
            this.square1.Image = global::LaserControl.Properties.Resources.square1;
            this.square1.Name = "square1";
            this.square1.UseVisualStyleBackColor = false;
            this.square1.Click += new System.EventHandler(this.square1_Click);
            // 
            // Incoming
            // 
            this.Incoming.BackColor = System.Drawing.SystemColors.ControlText;
            this.Incoming.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(192)))), ((int)(((byte)(0)))));
            resources.ApplyResources(this.Incoming, "Incoming");
            this.Incoming.Name = "Incoming";
            this.Incoming.ReadOnly = true;
            this.Incoming.TextChanged += new System.EventHandler(this.Incoming_TextChanged);
            // 
            // calibrationBox
            // 
            this.calibrationBox.Controls.Add(this.btnCalibrate);
            resources.ApplyResources(this.calibrationBox, "calibrationBox");
            this.calibrationBox.Name = "calibrationBox";
            this.calibrationBox.TabStop = false;
            // 
            // btnCalibrate
            // 
            resources.ApplyResources(this.btnCalibrate, "btnCalibrate");
            this.btnCalibrate.Name = "btnCalibrate";
            this.btnCalibrate.UseVisualStyleBackColor = true;
            this.btnCalibrate.Click += new System.EventHandler(this.btnCalibrate_Click);
            // 
            // connectionBox
            // 
            this.connectionBox.Controls.Add(this.connectionStatusText);
            this.connectionBox.Controls.Add(this.connectionStatus);
            this.connectionBox.Controls.Add(this.lblPorts);
            this.connectionBox.Controls.Add(this.btnConnect);
            this.connectionBox.Controls.Add(this.baudRate);
            this.connectionBox.Controls.Add(this.ports);
            this.connectionBox.Controls.Add(this.lblBaudRate);
            resources.ApplyResources(this.connectionBox, "connectionBox");
            this.connectionBox.Name = "connectionBox";
            this.connectionBox.TabStop = false;
            // 
            // connectionStatusText
            // 
            resources.ApplyResources(this.connectionStatusText, "connectionStatusText");
            this.connectionStatusText.Name = "connectionStatusText";
            // 
            // connectionStatus
            // 
            this.connectionStatus.BackColor = System.Drawing.Color.Red;
            this.connectionStatus.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.connectionStatus.ForeColor = System.Drawing.SystemColors.ControlText;
            resources.ApplyResources(this.connectionStatus, "connectionStatus");
            this.connectionStatus.Name = "connectionStatus";
            // 
            // laserControlBox
            // 
            this.laserControlBox.Controls.Add(this.laserStatusText);
            this.laserControlBox.Controls.Add(this.laserStatus);
            this.laserControlBox.Controls.Add(this.btnLaser);
            resources.ApplyResources(this.laserControlBox, "laserControlBox");
            this.laserControlBox.Name = "laserControlBox";
            this.laserControlBox.TabStop = false;
            // 
            // laserStatusText
            // 
            resources.ApplyResources(this.laserStatusText, "laserStatusText");
            this.laserStatusText.Name = "laserStatusText";
            // 
            // laserStatus
            // 
            this.laserStatus.BackColor = System.Drawing.Color.Red;
            this.laserStatus.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.laserStatus.ForeColor = System.Drawing.SystemColors.ControlText;
            resources.ApplyResources(this.laserStatus, "laserStatus");
            this.laserStatus.Name = "laserStatus";
            // 
            // btnLaser
            // 
            resources.ApplyResources(this.btnLaser, "btnLaser");
            this.btnLaser.Name = "btnLaser";
            this.btnLaser.UseVisualStyleBackColor = true;
            this.btnLaser.Click += new System.EventHandler(this.btnLaser_Click);
            // 
            // menuStrip
            // 
            this.menuStrip.BackColor = System.Drawing.SystemColors.Control;
            this.menuStrip.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.menuToolStripMenuItem,
            this.helpToolStripMenuItem});
            resources.ApplyResources(this.menuStrip, "menuStrip");
            this.menuStrip.Name = "menuStrip";
            // 
            // menuToolStripMenuItem
            // 
            this.menuToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.exitToolStripMenuItem});
            this.menuToolStripMenuItem.Name = "menuToolStripMenuItem";
            resources.ApplyResources(this.menuToolStripMenuItem, "menuToolStripMenuItem");
            // 
            // exitToolStripMenuItem
            // 
            this.exitToolStripMenuItem.Name = "exitToolStripMenuItem";
            resources.ApplyResources(this.exitToolStripMenuItem, "exitToolStripMenuItem");
            // 
            // helpToolStripMenuItem
            // 
            this.helpToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.aboutToolStripMenuItem});
            this.helpToolStripMenuItem.Name = "helpToolStripMenuItem";
            resources.ApplyResources(this.helpToolStripMenuItem, "helpToolStripMenuItem");
            // 
            // aboutToolStripMenuItem
            // 
            this.aboutToolStripMenuItem.Name = "aboutToolStripMenuItem";
            resources.ApplyResources(this.aboutToolStripMenuItem, "aboutToolStripMenuItem");
            // 
            // label1
            // 
            resources.ApplyResources(this.label1, "label1");
            this.label1.Name = "label1";
            // 
            // stanleptojectscom
            // 
            resources.ApplyResources(this.stanleptojectscom, "stanleptojectscom");
            this.stanleptojectscom.LinkColor = System.Drawing.Color.SteelBlue;
            this.stanleptojectscom.Name = "stanleptojectscom";
            this.stanleptojectscom.TabStop = true;
            this.stanleptojectscom.Click += new System.EventHandler(this.stanleyprojectscom_Click);
            // 
            // footer
            // 
            this.footer.BackColor = System.Drawing.SystemColors.Control;
            resources.ApplyResources(this.footer, "footer");
            this.footer.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.footer.Controls.Add(this.stanleptojectscom);
            this.footer.Controls.Add(this.label1);
            this.footer.ForeColor = System.Drawing.SystemColors.ControlDarkDark;
            this.footer.Name = "footer";
            // 
            // MainWindow
            // 
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.None;
            resources.ApplyResources(this, "$this");
            this.Controls.Add(this.panelControl);
            this.Controls.Add(this.footer);
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "MainWindow";
            this.panelControl.ResumeLayout(false);
            this.panelControl.PerformLayout();
            this.speedControl.ResumeLayout(false);
            this.calibrationBox.ResumeLayout(false);
            this.connectionBox.ResumeLayout(false);
            this.connectionBox.PerformLayout();
            this.laserControlBox.ResumeLayout(false);
            this.laserControlBox.PerformLayout();
            this.menuStrip.ResumeLayout(false);
            this.menuStrip.PerformLayout();
            this.footer.ResumeLayout(false);
            this.footer.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion
        private System.IO.Ports.SerialPort serialPort;
        private System.Windows.Forms.ComboBox ports;
        private System.Windows.Forms.ComboBox baudRate;
        private System.Windows.Forms.Label lblBaudRate;
        private System.Windows.Forms.Label lblPorts;
        private System.Windows.Forms.Button btnConnect;
        private System.Windows.Forms.Panel panelControl;
        private System.Windows.Forms.MenuStrip menuStrip;
        private System.Windows.Forms.ToolStripMenuItem menuToolStripMenuItem;
        private System.Windows.Forms.GroupBox laserControlBox;
        private System.Windows.Forms.Button btnLaser;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.LinkLabel stanleptojectscom;
        private System.Windows.Forms.Panel footer;
        private System.Windows.Forms.GroupBox connectionBox;
        private System.Windows.Forms.ToolStripMenuItem helpToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem aboutToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem exitToolStripMenuItem;
        private System.Windows.Forms.Label connectionStatusText;
        private System.Windows.Forms.Panel connectionStatus;
        private System.Windows.Forms.Panel laserStatus;
        private System.Windows.Forms.GroupBox calibrationBox;
        private System.Windows.Forms.Button btnCalibrate;
        private System.Windows.Forms.Label laserStatusText;
        private System.Windows.Forms.RichTextBox Incoming;
        private System.Windows.Forms.Button square1;
        private System.Windows.Forms.Button square2;
        private System.Windows.Forms.Button square4;
        private System.Windows.Forms.Button square3;
        private System.Windows.Forms.GroupBox speedControl;
        private System.Windows.Forms.Button btnRandomSpeed;
        private System.Windows.Forms.Button btnFixedSpeed;
        private System.Windows.Forms.Button btnDecrease;
        private System.Windows.Forms.Button btnIncrease;
        private System.Windows.Forms.Button btnStop;
        private System.Windows.Forms.Button star;
        private System.Windows.Forms.Button heart;
        private System.Windows.Forms.Button smiley;
        private System.Windows.Forms.Button manFigure;
        private System.Windows.Forms.Button line4;
        private System.Windows.Forms.Button line3;
        private System.Windows.Forms.Button line2;
        private System.Windows.Forms.Button line1;
        private System.Windows.Forms.Button triangle2;
        private System.Windows.Forms.Button triangle1;
        private System.Windows.Forms.Button cross2;
        private System.Windows.Forms.Button cross1;
    }
}

