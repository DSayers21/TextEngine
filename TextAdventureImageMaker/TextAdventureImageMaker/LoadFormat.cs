using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace TextAdventureImageMaker
{
    public partial class LoadFormat : Form
    {
        Form1 Hold;
        public LoadFormat()
        {
            InitializeComponent();
        }
        public LoadFormat(Form1 Sent)
        {
            Hold = Sent;
            InitializeComponent();
        }
        private void button1_Click(object sender, EventArgs e)
        {
            string[] values = richTextBox1.Text.Split(',');
            for (int i = 0; i < values.Length; i++)
            {
                values[i] = values[i].Trim();
                Console.WriteLine(values[i]);
            }
            Hold.LoadFormatPub(Convert.ToInt32(tb_Height.Text), Convert.ToInt32(tb_Width.Text), values);
        }

        private void LoadFormat_Load(object sender, EventArgs e)
        {

        }
    }
}
