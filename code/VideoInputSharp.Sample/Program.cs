using System;
using System.Collections.Generic;
using System.Drawing;
using System.Drawing.Imaging;
using System.Runtime.InteropServices;
using System.Text;
using System.Windows.Forms;
using VideoInputSharp;

namespace VideoInputSharp.Sample
{
    class Program
    {
        /// <summary>
        /// Entry point
        /// </summary>
        /// <param name="args"></param>
        [STAThread]
        static void Main(string[] args)
        {
            const int DeviceID = 1;
            const int CaptureFps = 30;
            const int CaptureWidth = 640;
            const int CaptureHeight = 480;

            // lists all capture devices
            //ListDevices();
            
            using (VideoInput vi = new VideoInput())
            {
                // initializes settings
                vi.SetIdealFramerate(DeviceID, CaptureFps);
                vi.SetupDevice(DeviceID, CaptureWidth, CaptureHeight);

                int width = vi.GetWidth(DeviceID);
                int height = vi.GetHeight(DeviceID);

                using (Bitmap bitmap = new Bitmap(width, height, PixelFormat.Format24bppRgb))
                using (Form form = new Form() { Text = "VideoInputSharp sample", ClientSize = new Size(width, height) })
                using (PictureBox pb = new PictureBox() { Dock = DockStyle.Fill, Image = bitmap })
                {
                    // allocates pixel data buffer
                    byte[] buffer = new byte[vi.GetSize(DeviceID)];

                    // to get the data from the device first check if the data is new
                    if (vi.IsFrameNew(DeviceID))
                    {
                        vi.GetPixels(DeviceID, buffer, false, true);
                    }

                    // shows window
                    form.Controls.Add(pb);
                    form.Show();

                    // captures until the window is closed
                    while (form.Created)
                    {
                        if (vi.IsFrameNew(DeviceID))
                        {
                            vi.GetPixels(DeviceID, buffer, false, true);
                        }
                        WritePixels(bitmap, buffer);
                        pb.Refresh();
                        Application.DoEvents();
                    }

                    // stops capturing
                    vi.StopDevice(DeviceID);
                }
            }
        }

        /// <summary>
        /// Shows the error message and shuts down this program
        /// </summary>
        /// <param name="msg"></param>
        static void Error(string msg)
        {
            Console.ForegroundColor = ConsoleColor.Red;
            Console.WriteLine(msg);
            Console.Read();
            Environment.Exit(-1);
        }

        /// <summary>
        /// Lists all available capture devices
        /// </summary>
        static void ListDevices()
        {
            int num = VideoInput.ListDevices();
            if (num == 0)
            {
                Error("Capture device not found");
            }
            Console.WriteLine("{0} device(s) found", num);
            for (int i = 0; i < num; i++)
            {
                Console.WriteLine("[{0}]: {1}", i, VideoInput.GetDeviceName(i));
            }
        }
        
        /// <summary>
        /// Writes the pixel data to the specified Bitmap
        /// </summary>
        /// <param name="bitmap"></param>
        /// <param name="pixels"></param>
        static void WritePixels(Bitmap bitmap, byte[] pixels)
        {
            BitmapData bd = bitmap.LockBits(new Rectangle(0, 0, bitmap.Width, bitmap.Height), ImageLockMode.WriteOnly, bitmap.PixelFormat);
            Marshal.Copy(pixels, 0, bd.Scan0, pixels.Length);
            bitmap.UnlockBits(bd);
        }
    }
}
