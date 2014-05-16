// VideoInputSharp.h

#pragma once

#include "VideoInputFormat.h"

using namespace System;
using namespace System::Runtime::InteropServices;

namespace VideoInputSharp 
{
	/// <summary>
    /// VIDEO INPUT
    /// </summary>
	public ref class VideoInput : public IDisposable
	{
	private:
		videoInput* _ptr;
		Boolean _isDisposed;

	public:
		VideoInput();
		!VideoInput();
		~VideoInput();

		// turns off console messages - default is to prInt32 messages
		static void SetVerbose(Boolean verbose);
		// Functions in rough order they should be used.
		static Int32 ListDevices();
		static Int32 ListDevices(Boolean silent);
		// needs to be called after listDevices - otherwise returns null
		static String^ GetDeviceName(Int32 deviceID);

		// choose to use callback based capture - or single threaded
		void SetUseCallback(Boolean useCallback);	
		// call before setupDevice
		// directshow will try and get the closest possible framerate to what is requested
		void SetIdealFramerate(Int32 deviceID, Int32 idealFramerate);
		// some devices will stop delivering frames after a while - this method gives you the option to try and reconnect
		// to a device if videoInput detects that a device has stopped delivering frames. 
		// you MUST CALL isFrameNew every app loop for this to have any effect
		void SetAutoReconnectOnFreeze(Int32 deviceNumber, Boolean doReconnect, Int32 numMissedFramesBeforeReconnect);
		// Choose one of these four to setup your device
		Boolean SetupDevice(Int32 deviceID);
		Boolean SetupDevice(Int32 deviceID, Int32 w, Int32 h);
		// These two are only for capture cards
		// USB and Firewire cameras souldn't specify connection 
		Boolean SetupDevice(Int32 deviceID, Int32 connection);	
		Boolean SetupDevice(Int32 deviceID, Int32 w, Int32 h, Int32 connection); 
		// If you need to you can set your NTSC/PAL/SECAM
		// preference here. if it is available it will be used.
		// see #defines above for available formats - eg VI_NTSC_M or VI_PAL_B
		// should be called after setupDevice
		// can be called multiple times
		Boolean SetFormat(Int32 deviceNumber, VideoInputFormat format);	
		// Tells you when a new frame has arrived - you should call this if you have specified setAutoReconnectOnFreeze to true
		Boolean IsFrameNew(Int32 deviceID); 		
		Boolean IsDeviceSetup(Int32 deviceID);
		// Returns the pixels - flipRedAndBlue toggles RGB/BGR flipping - and you can flip the image too
		IntPtr GetPixels(Int32 deviceID);
		IntPtr GetPixels(Int32 deviceID, Boolean flipRedAndBlue);
		IntPtr GetPixels(Int32 deviceID, Boolean flipRedAndBlue, Boolean flipImage);
		// Or pass in a buffer for getPixels to fill returns true if successful.
		Boolean GetPixels(Int32 id, IntPtr pixels);
		Boolean GetPixels(Int32 id, IntPtr pixels, Boolean flipRedAndBlue);
		Boolean GetPixels(Int32 id, IntPtr pixels, Boolean flipRedAndBlue, Boolean flipImage);
		Boolean GetPixels(Int32 id, array<Byte>^ pixels);
		Boolean GetPixels(Int32 id, array<Byte>^ pixels, Boolean flipRedAndBlue);
		Boolean GetPixels(Int32 id, array<Byte>^ pixels, Boolean flipRedAndBlue, Boolean flipImage);
		// Launches a pop up settings window
		// For some reason in GLUT you have to call it twice each time. 
		void ShowSettingsWindow(Int32 deviceID);
		// Manual control over settings thanks..... 
		// These are experimental for now.
		Boolean SetVideoSettingFilter(Int32 deviceID, Int32 Property, Int32 lValue);
		Boolean SetVideoSettingFilter(Int32 deviceID, Int32 Property, Int32 lValue, Int32 Flags);
		Boolean SetVideoSettingFilter(Int32 deviceID, Int32 Property, Int32 lValue, Int32 Flags, Boolean useDefaultValue);
		Boolean SetVideoSettingFilterPct(Int32 deviceID, Int32 Property, Single pctValue);
		Boolean SetVideoSettingFilterPct(Int32 deviceID, Int32 Property, Single pctValue, Int32 Flags);
		Boolean GetVideoSettingFilter(Int32 deviceID, Int32 Property, [Out] Int32% min, [Out] Int32% max, [Out] Int32% SteppingDelta, [Out] Int32% currentValue, [Out] Int32% flags, [Out] Int32% defaultValue);
		Boolean SetVideoSettingCamera(Int32 deviceID, Int32 Property, Int32 lValue);
		Boolean SetVideoSettingCamera(Int32 deviceID, Int32 Property, Int32 lValue, Int32 Flags);
		Boolean SetVideoSettingCamera(Int32 deviceID, Int32 Property, Int32 lValue, Int32 Flags, Boolean useDefaultValue);
		Boolean SetVideoSettingCameraPct(Int32 deviceID, Int32 Property, Single pctValue);
		Boolean SetVideoSettingCameraPct(Int32 deviceID, Int32 Property, Single pctValue, Int32 Flags);
		Boolean GetVideoSettingCamera(Int32 deviceID, Int32 Property, [Out] Int32% min, Int32% max, [Out] Int32% SteppingDelta, [Out] Int32% currentValue, [Out] Int32% flags, [Out] Int32% defaultValue);
		// get width, height and number of pixels
		Int32 GetWidth(Int32 deviceID);
		Int32 GetHeight(Int32 deviceID);
		Int32 GetSize(Int32 deviceID);
		// completely stops and frees a device
		void StopDevice(Int32 deviceID);
		// as above but then sets it up with same settings
		Boolean RestartDevice(Int32 deviceID);

		/// <summary>
		/// Number of devices available
		/// </summary>
		property Int32 DevicesFound { Int32 get(); void set(Int32 value); }
		
		property Int32 PropBrightness { Int32 get(); void set(Int32 value); }
		property Int32 PropContrast { Int32 get(); void set(Int32 value); }
		property Int32 PropHue { Int32 get(); void set(Int32 value); }
		property Int32 PropSaturation { Int32 get(); void set(Int32 value); }
		property Int32 PropSharpness { Int32 get(); void set(Int32 value); }
		property Int32 PropGamma { Int32 get(); void set(Int32 value); }
		property Int32 PropColorEnable { Int32 get(); void set(Int32 value); }
		property Int32 PropWhiteBalance { Int32 get(); void set(Int32 value); }
		property Int32 PropBacklightCompensation { Int32 get(); void set(Int32 value); }
		property Int32 PropGain { Int32 get(); void set(Int32 value); }
		property Int32 PropPan { Int32 get(); void set(Int32 value); }
		property Int32 PropTilt { Int32 get(); void set(Int32 value); }
		property Int32 PropRoll { Int32 get(); void set(Int32 value); }
		property Int32 PropZoom { Int32 get(); void set(Int32 value); }
		property Int32 PropExposure { Int32 get(); void set(Int32 value); }
		property Int32 PropIris { Int32 get(); void set(Int32 value); }
		property Int32 PropFocus { Int32 get(); void set(Int32 value); }
	};
}
