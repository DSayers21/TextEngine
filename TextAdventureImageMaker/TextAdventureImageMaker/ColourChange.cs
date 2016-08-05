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
    public partial class ColourChange : Form
    {
        Form1 Hold;
        private int Old, New;
        public ColourChange(Form1 Sent)
        {
            InitializeComponent();
            Hold = Sent;
        }
        private void UpdateCur(Button But, int Col)
        {
            switch (Col)
            {
                case 0:
                    But.BackColor = Color.Black;
                    break;
                case 17:
                    But.BackColor = Color.DarkBlue;
                    break;
                case 34:
                    But.BackColor = Color.DarkGreen;
                    break;
                case 51:
                    But.BackColor = Color.DarkTurquoise;
                    break;
                case 68:
                    But.BackColor = Color.DarkRed;
                    break;
                case 85:
                    But.BackColor = Color.Purple;
                    break;
                case 102:
                    But.BackColor = Color.Gold;
                    break;
                case 119:
                    But.BackColor = Color.LightGray;
                    break;
                case 136:
                    But.BackColor = Color.Gray;
                    break;
                case 153:
                    But.BackColor = Color.Blue;
                    break;
                case 170:
                    But.BackColor = Color.Green;
                    break;
                case 187:
                    But.BackColor = Color.LightBlue;
                    break;
                case 204:
                    But.BackColor = Color.Red;
                    break;
                case 221:
                    But.BackColor = Color.Pink;
                    break;
                case 238:
                    But.BackColor = Color.Yellow;
                    break;
                case 255:
                    But.BackColor = Color.White;
                    break;
            }
        }
        private void b_black_Click(object sender, EventArgs e)
        {
            UpdateCur(colBox, 0);
            Old = 0;
        }
        private void b_darkblue_Click(object sender, EventArgs e)
        {
            UpdateCur(colBox, 17);
            Old = 17;
        }

        private void b_darkgreen_Click(object sender, EventArgs e)
        {
            UpdateCur(colBox, 34);
            Old = 34;
        }

        private void b_darkteal_Click(object sender, EventArgs e)
        {
            UpdateCur(colBox, 51);
            Old = 51;
        }

        private void b_darkred_Click(object sender, EventArgs e)
        {
            UpdateCur(colBox, 68);
            Old = 68;
        }

        private void b_darkpink_Click(object sender, EventArgs e)
        {
            UpdateCur(colBox, 85);
            Old = 85;
        }

        private void b_darkyellow_Click(object sender, EventArgs e)
        {
            UpdateCur(colBox, 102);
            Old = 102;
        }

        private void b_lightgray_Click(object sender, EventArgs e)
        {
            UpdateCur(colBox, 119);
            Old = 119;
        }

        private void b_darkgray_Click(object sender, EventArgs e)
        {
            UpdateCur(colBox, 136);
            Old = 136;
        }

        private void b_blue_Click(object sender, EventArgs e)
        {
            UpdateCur(colBox, 153);
            Old = 153;
        }

        private void b_green_Click(object sender, EventArgs e)
        {
            UpdateCur(colBox, 170);
            Old = 170;
        }

        private void b_lightblue_Click(object sender, EventArgs e)
        {
            UpdateCur(colBox, 187);
            Old = 187;
        }

        private void b_red_Click(object sender, EventArgs e)
        {
            UpdateCur(colBox, 204);
            Old = 204;
        }

        private void b_pink_Click(object sender, EventArgs e)
        {
            UpdateCur(colBox, 221);
            Old = 221;
        }

        private void b_yellow_Click(object sender, EventArgs e)
        {
            UpdateCur(colBox, 238);
            Old = 238;
        }

        private void b_white_Click(object sender, EventArgs e)
        {
            UpdateCur(colBox, 255);
            Old = 255;
        }

        private void button7_Click(object sender, EventArgs e)
        {
            UpdateCur(colBox2, 0);
            New = 0;
        }

        private void button5_Click(object sender, EventArgs e)
        {
            UpdateCur(colBox2, 17);
            New = 17;
        }

        private void button13_Click(object sender, EventArgs e)
        {
            UpdateCur(colBox2, 34);
            New = 34;
        }

        private void button15_Click(object sender, EventArgs e)
        {
            UpdateCur(colBox2, 51);
            New = 51;
        }

        private void button14_Click(object sender, EventArgs e)
        {
            UpdateCur(colBox2, 68);
            New = 68;
        }

        private void button12_Click(object sender, EventArgs e)
        {
            UpdateCur(colBox2, 85);
            New = 85;
        }

        private void button6_Click(object sender, EventArgs e)
        {
            UpdateCur(colBox2, 102);
            New = 102;
        }

        private void button4_Click(object sender, EventArgs e)
        {
            UpdateCur(colBox2, 119);
            New = 119;
        }

        private void button9_Click(object sender, EventArgs e)
        {
            UpdateCur(colBox2, 136);
            New = 136;
        }

        private void button11_Click(object sender, EventArgs e)
        {
            UpdateCur(colBox2, 153);
            New = 153;
        }

        private void button17_Click(object sender, EventArgs e)
        {
            UpdateCur(colBox2, 170);
            New = 170;
        }

        private void button16_Click(object sender, EventArgs e)
        {
            UpdateCur(colBox2, 187);
            New = 187;
        }

        private void button10_Click(object sender, EventArgs e)
        {
            UpdateCur(colBox2, 204);
            New = 204;
        }

        private void button8_Click(object sender, EventArgs e)
        {
            UpdateCur(colBox2, 221);
            New = 221;
        }

        private void button3_Click(object sender, EventArgs e)
        {
            UpdateCur(colBox2, 238);
            New = 238;
        }

        private void button2_Click(object sender, EventArgs e)
        {
            UpdateCur(colBox2, 255);
            New = 255;
        }

        private void ColourChange_Load(object sender, EventArgs e)
        {
            b_black.BackColor = Color.Black;
            b_darkblue.BackColor = Color.DarkBlue;
            b_darkgreen.BackColor = Color.DarkGreen;
            b_darkteal.BackColor = Color.DarkTurquoise;
            b_darkred.BackColor = Color.DarkRed;
            b_darkpink.BackColor = Color.Purple;
            b_darkyellow.BackColor = Color.Gold;
            b_lightgray.BackColor = Color.LightGray;
            b_darkgray.BackColor = Color.Gray;
            b_blue.BackColor = Color.Blue;
            b_green.BackColor = Color.Green;
            b_lightblue.BackColor = Color.LightBlue;
            b_red.BackColor = Color.Red;
            b_pink.BackColor = Color.Pink;
            b_yellow.BackColor = Color.Yellow;
            b_white.BackColor = Color.White;

            button7.BackColor = Color.Black;
            button5.BackColor = Color.DarkBlue;
            button13.BackColor = Color.DarkGreen;
            button15.BackColor = Color.DarkTurquoise;
            button14.BackColor = Color.DarkRed;
            button12.BackColor = Color.Purple;
            button6.BackColor = Color.Gold;
            button4.BackColor = Color.LightGray;
            button9.BackColor = Color.Gray;
            button11.BackColor = Color.Blue;
            button17.BackColor = Color.Green;
            button16.BackColor = Color.LightBlue;
            button10.BackColor = Color.Red;
            button8.BackColor = Color.Pink;
            button3.BackColor = Color.Yellow;
            button2.BackColor = Color.White;
        }

        private void button18_Click(object sender, EventArgs e)
        {
            int Cur;
            if (Hold.GetTable().ColumnCount > 0)
            {
                for (int i = 0; i < Hold.GetTable().ColumnCount; i++)
                {
                    for (int j = 0; j < Hold.GetTable().RowCount; j++)
                    {
                        Cur = Convert.ToInt32(Hold.GetTable()[i, j].Value);
                        if (Cur == Old)
                        {
                            Hold.GetTable()[i, j].Value = New;
                            Hold.ColSwitch(i, j);
                        }
                    }
                }
            }
        }
    }
}
