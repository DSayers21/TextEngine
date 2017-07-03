using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace TextAdventureImageMaker
{
    public partial class Form1 : Form
    {
        private bool Refreshing = false;
        private int ActiveColour = 0;

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
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
    }

        private void button1_Click(object sender, EventArgs e)
        {
            Refreshing = true;
            dG_List.Rows.Clear();
            if ((tb_Width.Text != "") && (tb_Height.Text != ""))
            {
                dG_List.ColumnCount = Convert.ToInt32(tb_Width.Text);
                foreach (DataGridViewColumn c in dG_List.Columns)
                    c.Width = 20;
                for (int i = 0; i < Convert.ToInt32(tb_Height.Text); i++)
                    dG_List.Rows.Add();

                for (int i = 0; i < dG_List.ColumnCount; i++)
                {
                    for (int j = 0; j < dG_List.RowCount; j++)
                    {
                        dG_List[i, j].Value = 0;
                        FormatCell(i, j, Color.Black);
                    }
                }
                ColourTable();
                Refreshing = false;
            }
        }

        private void ColourTable()
        {
            for (int i = 0; i < dG_List.ColumnCount; i++)
            {
                for (int j = 0; j < dG_List.RowCount; j++)
                {
                    ColSwitch(i, j);
                }
            }
        }
        public void ColSwitch(int i, int j)
        {
            switch (Convert.ToInt32(dG_List[i, j].Value))
            {
                case 0:
                    FormatCell(i, j, Color.Black);
                    break;
                case 17:
                    FormatCell(i, j, Color.DarkBlue);
                    break;
                case 34:
                    FormatCell(i, j, Color.DarkGreen);
                    break;
                case 51:
                    FormatCell(i, j, Color.DarkTurquoise);
                    break;
                case 68:
                    FormatCell(i, j, Color.DarkRed);
                    break;
                case 85:
                    FormatCell(i, j, Color.Purple);
                    break;
                case 102:
                    FormatCell(i, j, Color.Gold);
                    break;
                case 119:
                    FormatCell(i, j, Color.LightGray);
                    break;
                case 136:
                    FormatCell(i, j, Color.Gray);
                    break;
                case 153:
                    FormatCell(i, j, Color.Blue);
                    break;
                case 170:
                    FormatCell(i, j, Color.Green);
                    break;
                case 187:
                    FormatCell(i, j, Color.LightBlue);
                    break;
                case 204:
                    FormatCell(i, j, Color.Red);
                    break;
                case 221:
                    FormatCell(i, j, Color.Pink);
                    break;
                case 238:
                    FormatCell(i, j, Color.Yellow);
                    break;
                case 255:
                    FormatCell(i, j, Color.White);
                    break;
            }
        }

        private void UpdateCur()
        {
            switch (ActiveColour)
            {
                case 0:
                    colBox.BackColor = Color.Black;
                    break;
                case 17:
                    colBox.BackColor = Color.DarkBlue;
                    break;
                case 34:
                    colBox.BackColor = Color.DarkGreen;
                    break;
                case 51:
                    colBox.BackColor = Color.DarkTurquoise;
                    break;
                case 68:
                    colBox.BackColor = Color.DarkRed;
                    break;
                case 85:
                    colBox.BackColor = Color.Purple;
                    break;
                case 102:
                    colBox.BackColor = Color.Gold;
                    break;
                case 119:
                    colBox.BackColor = Color.LightGray;
                    break;
                case 136:
                    colBox.BackColor = Color.Gray;
                    break;
                case 153:
                    colBox.BackColor = Color.Blue;
                    break;
                case 170:
                    colBox.BackColor = Color.Green;
                    break;
                case 187:
                    colBox.BackColor = Color.LightBlue;
                    break;
                case 204:
                    colBox.BackColor = Color.Red;
                    break;
                case 221:
                    colBox.BackColor = Color.Pink;
                    break;
                case 238:
                    colBox.BackColor = Color.Yellow;
                    break;
                case 255:
                    colBox.BackColor = Color.White;
                    break;
            }
        }

        private void FormatCell(int row, int col, Color SColor)
        {
            DataGridViewCell c = dG_List[row, col];

            c.Style.BackColor = SColor;
            c.Style.ForeColor = SColor;

            c.ReadOnly = true;
            c.Style.SelectionBackColor = Color.BlueViolet;
            c.Style.SelectionForeColor = Color.BlueViolet;
        }

        private void dG_List_CellValueChanged(object sender, DataGridViewCellEventArgs e)
        {
            if (!Refreshing)
            {
                ColSwitch(e.ColumnIndex, e.RowIndex);
            }
        }

        private void exitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        private void saveToolStripMenuItem_Click(object sender, EventArgs e)
        {
            string Output = "";

            for (int i = 0; i < dG_List.RowCount; i++)
            {
                for (int j = 0; j < dG_List.ColumnCount; j++)
                {
                    if((i == 0)&&(j == 0))
                        Output = Output  + dG_List[j, i].Value;
                    else
                        Output = Output + ',' + dG_List[j, i].Value;
                }
            }
            SaveFile(Output);
            //Console.WriteLine(Output);
        }

        private void SaveFile(string Save)
        {
            SaveFileDialog savefile = new SaveFileDialog();
            // set a default file name
            savefile.FileName = "unknown.txt";
            // set filters - this can be done in properties as well
            savefile.Filter = "Text files (*.txt)|*.txt|All files (*.*)|*.*";

            if (savefile.ShowDialog() == DialogResult.OK)
            {
                System.IO.FileStream fs = (System.IO.FileStream)savefile.OpenFile();
                //Create Byte array
                Byte[] info = new UTF8Encoding(true).GetBytes("");
                //Create byte array
                byte[] newline = Encoding.ASCII.GetBytes(Environment.NewLine);

                info = new UTF8Encoding(true).GetBytes(tb_Width.Text);
                fs.Write(info, 0, info.Length);
                fs.Write(newline, 0, newline.Length);
                info = new UTF8Encoding(true).GetBytes(Save);
                fs.Write(info, 0, info.Length);

                //Closes the file stream
                fs.Close();
            }
        }

        private void b_black_Click(object sender, EventArgs e)
        {
            ActiveColour = 0;
            UpdateCur();
        }

        private void b_darkblue_Click(object sender, EventArgs e)
        {
            ActiveColour = 17;
            UpdateCur();
        }

        private void b_darkgreen_Click(object sender, EventArgs e)
        {
            ActiveColour = 34;
            UpdateCur();
        }

        private void b_darkteal_Click(object sender, EventArgs e)
        {
            ActiveColour = 51;
            UpdateCur();
        }

        private void b_darkred_Click(object sender, EventArgs e)
        {
            ActiveColour = 68;
            UpdateCur();
        }

        private void b_darkpink_Click(object sender, EventArgs e)
        {
            ActiveColour = 85;
            UpdateCur();
        }

        private void b_darkyellow_Click(object sender, EventArgs e)
        {
            ActiveColour = 102;
            UpdateCur();
        }

        private void b_lightgray_Click(object sender, EventArgs e)
        {
            ActiveColour = 119;
            UpdateCur();
        }

        private void b_darkgray_Click(object sender, EventArgs e)
        {
            ActiveColour = 136;
            UpdateCur();
        }

        private void b_blue_Click(object sender, EventArgs e)
        {
            ActiveColour = 153;
            UpdateCur();
        }

        private void b_green_Click(object sender, EventArgs e)
        {
            ActiveColour = 170;
            UpdateCur();
        }

        private void b_lightblue_Click(object sender, EventArgs e)
        {
            ActiveColour = 187;
            UpdateCur();
        }

        private void b_red_Click(object sender, EventArgs e)
        {
            ActiveColour = 204;
            UpdateCur();
        }

        private void b_pink_Click(object sender, EventArgs e)
        {
            ActiveColour = 221;
            UpdateCur();
        }

        private void b_yellow_Click(object sender, EventArgs e)
        {
            ActiveColour = 238;
            UpdateCur();
        }

        private void b_white_Click(object sender, EventArgs e)
        {
            ActiveColour = 255;
            UpdateCur();
        }

        private void dG_List_CellClick(object sender, DataGridViewCellEventArgs e)
        {
            
        }

        private void loadFormatToolStripMenuItem_Click(object sender, EventArgs e)
        {
            //LoadFormat loadForm = new LoadFormat(this);
            //loadForm.Show();
            int counter = 0;
            string line;

            OpenFileDialog openFileDialog1 = new OpenFileDialog();
            //Set the title of the open file dialog
            openFileDialog1.Title = "Open List File";
            //Set the filter as to what the file can be opened as e.g. .txt
            openFileDialog1.Filter = "List File|*.txt";
            //Set the initial directory the open file dialog opens to
            //penFileDialog1.InitialDirectory = @"C:\";
            //If open file has been clicked on acceptable file in the open file dialog
            string[] values = { };
            if (openFileDialog1.ShowDialog() == DialogResult.OK)
            {
                // Read the file and display it line by line.
                System.IO.StreamReader file = new System.IO.StreamReader(openFileDialog1.FileName);
                while ((line = file.ReadLine()) != null)
                {
                    if (counter == 0)
                    {
                        tb_Width.Text = line;
                    }
                    if (counter == 1)
                    {
                        values = line.Split(',');
                        for (int i = 0; i < values.Length; i++)
                        {
                            values[i] = values[i].Trim();
                        }
                    }
                    counter++;
                }
                file.Close();
            }
            int Width = Convert.ToInt32(tb_Width.Text);
            int Size = values.Length;
            int Height = Size / Width;
            tb_Height.Text = Convert.ToString(Height);
            LoadFormatPub(values);
        }
        public DataGridView GetTable()
        {
            return dG_List;
        }
        public void LoadFormatPub(string[] Sent)
        {
            Refreshing = true;
            dG_List.Rows.Clear();
            dG_List.ColumnCount = Convert.ToInt32(tb_Width.Text);
            int Count = 0;
            foreach (DataGridViewColumn c in dG_List.Columns)
                c.Width = 20;
            for (int i = 0; i < Convert.ToInt32(tb_Height.Text); i++)
                dG_List.Rows.Add();

            for (int i = 0; i < dG_List.RowCount; i++)
            {
                for (int j = 0; j < dG_List.ColumnCount; j++)
                {
                    dG_List[j, i].Value = Sent[Count];
                    Count++;
                }
            }
            ColourTable();
            Refreshing = false;
        }

        private void button2_Click(object sender, EventArgs e)
        {
            if (dG_List.ColumnCount + dG_List.RowCount > 0)
            {
                dG_List.Columns.RemoveAt(dG_List.ColumnCount - 1);
                tb_Width.Text = Convert.ToString(dG_List.ColumnCount);
                tb_Height.Text = Convert.ToString(dG_List.RowCount);
            }
        }

        private void button5_Click(object sender, EventArgs e)
        {
            if (dG_List.ColumnCount + dG_List.RowCount > 0)
            {
                dG_List.ColumnCount += 1;
                foreach (DataGridViewColumn c in dG_List.Columns)
                    c.Width = 20;

                for (int i = 0; i < dG_List.RowCount; i++)
                {
                    dG_List[dG_List.ColumnCount - 1, i].Value = 0;
                    FormatCell(dG_List.ColumnCount - 1, i, Color.Black);
                }
                tb_Width.Text = Convert.ToString(dG_List.ColumnCount);
                tb_Height.Text = Convert.ToString(dG_List.RowCount);
            }
        }

        private void button3_Click(object sender, EventArgs e)
        {
            if (dG_List.ColumnCount + dG_List.RowCount > 0)
            {
                dG_List.Rows.RemoveAt(dG_List.RowCount - 1);
                tb_Width.Text = Convert.ToString(dG_List.ColumnCount);
                tb_Height.Text = Convert.ToString(dG_List.RowCount);
            }
        }

        private void button4_Click(object sender, EventArgs e)
        {
            if (dG_List.ColumnCount + dG_List.RowCount > 0)
            {
                dG_List.Rows.Add();
                for (int i = 0; i < dG_List.ColumnCount; i++)
                {
                    dG_List[i, dG_List.RowCount - 1].Value = 0;
                    FormatCell(i, dG_List.RowCount - 1, Color.Black);
                }
                tb_Width.Text = Convert.ToString(dG_List.ColumnCount);
                tb_Height.Text = Convert.ToString(dG_List.RowCount);
            }
        }

        private void button6_Click(object sender, EventArgs e)
        {
            if (dG_List.ColumnCount + dG_List.RowCount > 0)
            {
                DataGridViewTextBoxColumn columnSave = new DataGridViewTextBoxColumn();
                dG_List.Columns.Insert(0, columnSave);
                foreach (DataGridViewColumn c in dG_List.Columns)
                    c.Width = 20;
                for (int i = 0; i < dG_List.RowCount; i++)
                {
                    dG_List[0, i].Value = 0;
                    FormatCell(0, i, Color.Black);
                }
                dG_List.Columns.RemoveAt(dG_List.ColumnCount - 1);
                tb_Width.Text = Convert.ToString(dG_List.ColumnCount);
                tb_Height.Text = Convert.ToString(dG_List.RowCount);
            }
        }

        private void button7_Click(object sender, EventArgs e)
        {
            if (dG_List.ColumnCount + dG_List.RowCount > 0)
            {
                dG_List.Rows.Insert(0, 1);
                for (int i = 0; i < dG_List.ColumnCount; i++)
                {
                    dG_List[i, 0].Value = 0;
                    FormatCell(i, 0, Color.Black);
                }
                dG_List.Rows.RemoveAt(dG_List.RowCount - 1);
                tb_Width.Text = Convert.ToString(dG_List.ColumnCount);
                tb_Height.Text = Convert.ToString(dG_List.RowCount);
            }
        }

        private void button8_Click(object sender, EventArgs e)
        {
            if (dG_List.ColumnCount + dG_List.RowCount > 0)
            {
                dG_List.Rows.Insert(dG_List.RowCount, 1);
                for (int i = 0; i < dG_List.ColumnCount; i++)
                {
                    dG_List[i, dG_List.RowCount - 1].Value = 0;
                    FormatCell(i, dG_List.RowCount - 1, Color.Black);
                }
                dG_List.Rows.RemoveAt(0);
                tb_Width.Text = Convert.ToString(dG_List.ColumnCount);
                tb_Height.Text = Convert.ToString(dG_List.RowCount);
            }
        }

        private void button9_Click(object sender, EventArgs e)
        {
            if (dG_List.ColumnCount + dG_List.RowCount > 0)
            {
                DataGridViewTextBoxColumn columnSave = new DataGridViewTextBoxColumn();
                dG_List.Columns.Insert(dG_List.ColumnCount, columnSave);
                foreach (DataGridViewColumn c in dG_List.Columns)
                    c.Width = 20;
                for (int i = 0; i < dG_List.RowCount; i++)
                {
                    dG_List[dG_List.ColumnCount - 1, i].Value = 0;
                    FormatCell(dG_List.ColumnCount - 1, i, Color.Black);
                }
                dG_List.Columns.RemoveAt(0);
                tb_Width.Text = Convert.ToString(dG_List.ColumnCount);
                tb_Height.Text = Convert.ToString(dG_List.RowCount);
            }
        }

        private void button10_Click(object sender, EventArgs e)
        {
            ColourChange ColourForm = new ColourChange(this);
            ColourForm.Show();
        }

        private void dG_List_CellMouseClick(object sender, DataGridViewCellMouseEventArgs e)
        {
            if (dG_List.ColumnCount > 0)
            {
                dG_List[e.ColumnIndex, e.RowIndex].Value = ActiveColour;
                ColSwitch(e.ColumnIndex, e.RowIndex);
            }
        }

        private void dG_List_CellMouseUp(object sender, DataGridViewCellMouseEventArgs e)
        {
            for (int i = 0; i < dG_List.RowCount; i++)
            {
                for (int j = 0; j < dG_List.ColumnCount; j++)
                {
                    if (this.dG_List.Rows[i].Cells[j].Selected)
                    {
                        dG_List[j, i].Value = ActiveColour;
                        ColSwitch(j, i);
                        this.dG_List.Rows[i].Cells[j].Selected = false;
                    }
                }
            }
       }
    }
}
