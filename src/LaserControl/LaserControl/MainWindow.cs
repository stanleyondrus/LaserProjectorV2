using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace LaserControl
{
    public partial class MainWindow : Form
    {

        private String disconnectedStatus = "IDLE";
        string inData = String.Empty;

        private Boolean laser = false;

        public MainWindow()
        {
            InitializeComponent();
            fillData();
            disableControls();
            panelControl.Visible = true;
            this.FormBorderStyle = FormBorderStyle.FixedDialog;
            serialPort.ReadTimeout = 2000;
            serialPort.WriteTimeout = 2000;
        }

        private void disableControls()
        {
            btnConnect.Text = "Connect";

            btnLaser.Enabled = false;
            laserStatus.BackColor = Color.LightGray;
            laserStatusText.Text = disconnectedStatus;
            laserStatusText.Enabled = false;
            btnCalibrate.Enabled = false;
            Incoming.ResetText();
            btnRandomSpeed.Enabled = false;
            btnFixedSpeed.Enabled = false;
            btnIncrease.Enabled = false;
            btnDecrease.Enabled = false;
            btnStop.Enabled = false;
            btnStop.BackColor = Color.LightGray;

            square1.Enabled = false;
            square2.Enabled = false;
            square3.Enabled = false;
            square4.Enabled = false;
            line1.Enabled = false;
            line2.Enabled = false;
            line3.Enabled = false;
            line4.Enabled = false;
            cross1.Enabled = false;
            cross2.Enabled = false;
            triangle1.Enabled = false;
            triangle2.Enabled = false;
            manFigure.Enabled = false;
            smiley.Enabled = false;
            heart.Enabled = false;
            star.Enabled = false;

        }

        private void enableControls()
        {
            btnConnect.Text = "Disconnect";
            btnLaser.Enabled = true;
            laserStatusText.Enabled = true;
            btnCalibrate.Enabled = true;
            btnRandomSpeed.Enabled = true;
            btnFixedSpeed.Enabled = true;
            btnIncrease.Enabled = true;
            btnDecrease.Enabled = true;
            btnStop.Enabled = true;
            btnStop.BackColor = Color.Red;
            refreshIndicators();

            square1.Enabled = true;
            square2.Enabled = true;
            square3.Enabled = true;
            square4.Enabled = true;
            line1.Enabled = true;
            line2.Enabled = true;
            line3.Enabled = true;
            line4.Enabled = true;
            cross1.Enabled = true;
            cross2.Enabled = true;
            triangle1.Enabled = true;
            triangle2.Enabled = true;
            manFigure.Enabled = true;
            smiley.Enabled = true;
            heart.Enabled = true;
            star.Enabled = true;
        }

        private void refreshIndicators()
        {
            if (laser == true)  // laser status
            {
                laserStatus.BackColor = Color.Green;
                laserStatusText.Text = "ON";
                btnLaser.Text = "Turn Off";
            }
            else
            {
                laserStatus.BackColor = Color.Red;
                laserStatusText.Text = "OFF";
                btnLaser.Text = "Turn On";
            }
        }

        private void fillData()
        {
            string[] ArrayComPortsNames = null;
            int index = -1;
            string ComPortName = null;

            ArrayComPortsNames = SerialPort.GetPortNames();

            do
            {
                index += 1;
                ports.Items.Add(ArrayComPortsNames[index]);
            }

            while (!((ArrayComPortsNames[index] == ComPortName)
               || (index == ArrayComPortsNames.GetUpperBound(0))));
            Array.Sort(ArrayComPortsNames);

            //want to get first out
            if (index == ArrayComPortsNames.GetUpperBound(0))
            {
                ComPortName = ArrayComPortsNames[0];
            }
            ports.Text = ArrayComPortsNames[0];

            baudRate.Items.Add(300);
            baudRate.Items.Add(600);
            baudRate.Items.Add(1200);
            baudRate.Items.Add(2400);
            baudRate.Items.Add(9600);
            baudRate.Items.Add(14400);
            baudRate.Items.Add(19200);
            baudRate.Items.Add(38400);
            baudRate.Items.Add(57600);
            baudRate.Items.Add(115200);
            baudRate.Items.ToString();
            //get first item print in text
            baudRate.Text = baudRate.Items[4].ToString();
        }

        private void stanleyprojectscom_Click(object sender, EventArgs e)
        {
            System.Diagnostics.Process.Start("http://www.stanleyprojects.com");
        }   // footer link

        private void btnConnect_Click(object sender, EventArgs e)
        {
            if (!(serialPort.IsOpen))
            {
                if (connect())
                {
                    btnConnect.Text = "Disconnect";
                    connectionStatus.BackColor = Color.Green;
                    connectionStatusText.Text = "Connected";
                    ports.Enabled = false;
                    baudRate.Enabled = false;
                    enableControls();
                }
            }

            else if (serialPort.IsOpen)
            {
                serialPort.Close();
                btnConnect.Text = "Connect";
                connectionStatus.BackColor = Color.Red;
                connectionStatusText.Text = "Disconnected";
                ports.Enabled = true;
                baudRate.Enabled = true;
                disableControls();
            }
        }

        private Boolean connect()
        {
            serialPort.PortName = Convert.ToString(ports.Text);
            serialPort.BaudRate = Convert.ToInt32(baudRate.Text);

            try
            {
                serialPort.Open();
                return true;
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }

            return false;
        }

        private void serialPort_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            inData = serialPort.ReadExisting();
            this.Invoke(new EventHandler(DisplayText));
        }

        private void DisplayText(object sender, EventArgs e)
        {
            Incoming.AppendText(inData);
        }

        private void Incoming_TextChanged(object sender, EventArgs e)
        {
            Incoming.SelectionStart = Incoming.Text.Length; 
            Incoming.ScrollToCaret();
        }

        private void btnLaser_Click(object sender, EventArgs e)
        {
            if (laser != true)
            {
                serialPort.Write("A");
                laser = true;
            }
            else
            {
                serialPort.Write("B");
                laser = false;
            }
            refreshIndicators();
        }

        private void btnCalibrate_Click(object sender, EventArgs e)
        {
            serialPort.Write("C");
        }

        private void btnStop_Click(object sender, EventArgs e)
        {
            serialPort.Write("D");
        }

        private void btnRandomSpeed_Click(object sender, EventArgs e)
        {
            serialPort.Write("E");
        }

        private void btnFixedSpeed_Click(object sender, EventArgs e)
        {
            serialPort.Write("F");
        }

        private void btnIncrease_Click(object sender, EventArgs e)
        {
            serialPort.Write("G");
        }

        private void btnDecrease_Click(object sender, EventArgs e)
        {
            serialPort.Write("H");
        }

        private void square1_Click(object sender, EventArgs e)
        {
            serialPort.Write("I");
        }

        private void square2_Click(object sender, EventArgs e)
        {
            serialPort.Write("J");
        }

        private void square3_Click(object sender, EventArgs e)
        {
            serialPort.Write("K");
        }

        private void square4_Click(object sender, EventArgs e)
        {
            serialPort.Write("L");
        }

        private void cross1_Click(object sender, EventArgs e)
        {
            serialPort.Write("M");
        }

        private void cross2_Click(object sender, EventArgs e)
        {
            serialPort.Write("N");
        }

        private void triangle1_Click(object sender, EventArgs e)
        {
            serialPort.Write("O");
        }

        private void triangle2_Click(object sender, EventArgs e)
        {
            serialPort.Write("P");
        }

        private void line1_Click(object sender, EventArgs e)
        {
            serialPort.Write("Q");
        }

        private void line2_Click(object sender, EventArgs e)
        {
            serialPort.Write("R");
        }

        private void line3_Click(object sender, EventArgs e)
        {
            serialPort.Write("S");
        }

        private void line4_Click(object sender, EventArgs e)
        {
            serialPort.Write("T");
        }

        private void manFigure_Click(object sender, EventArgs e)
        {
            serialPort.Write("U");
        }

        private void smiley_Click(object sender, EventArgs e)
        {
            serialPort.Write("V");
        }

        private void heart_Click(object sender, EventArgs e)
        {
            serialPort.Write("W");
        }

        private void star_Click(object sender, EventArgs e)
        {
            serialPort.Write("X");
        }
    }
}
