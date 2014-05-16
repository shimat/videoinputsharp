VideoInputSharp
===============

## Description
VideoInputSharp is a wrapper to the [videoInput](http://www.muonics.net/school/spring05/videoInput/) library for .NET Framework. [videoInput](http://www.muonics.net/school/spring05/videoInput/) is a free windows video capture library. You can easily capture image from your devices using VideoInputSharp without additional software.

VideoInputSharpは、 [videoInput](http://www.muonics.net/school/spring05/videoInput/).NET Framework向けラッパーです。[videoInput](http://www.muonics.net/school/spring05/videoInput/)とは、DirectShowによるWindows向けのビデオキャプチャを容易に行えるライブラリです。VideoInputSharpにより、その他にライブラリを用意することなく簡単にカメラ等のデバイスからキャプチャが行えます。 

![capture sample](https://raw.githubusercontent.com/shimat/videoinputsharp/master/github/capture_sample.png)

## Downloads
Get the VideoInputSharp DLL file from the [release page](https://github.com/shimat/videoinputsharp/releases).

## Example
```c#
using VideoInputSharp;

class Program
{
    static void Main(string[] args)
    {
        const int DeviceID = 0;

        using (VideoInput vi = new VideoInput())
        {
            vi.SetIdealFramerate(DeviceID, 30);
            vi.SetupDevice(DeviceID, 640, 480);

            byte[] buffer = new byte[vi.GetSize(DeviceID)];

            while (true)
            {
                vi.GetPixels(DeviceID, buffer);
                // do something....
            }

            vi.StopDevice(DeviceID);
        }
    }
}
```

## Requirements
- Windows
- .NET Framework 2.0 or later
