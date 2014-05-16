// これは メイン DLL ファイルです。

#include "stdafx.h"
#include "VideoInputWrapper.h"

namespace VideoInputSharp
{
	#pragma region Init and Disposal
	/// <summary>
    /// Constructor
    /// </summary>
	VideoInput::VideoInput()
	{
		_ptr = new videoInput();
		_isDisposed = false;
	}
	/// <summary>
    /// Destructor
    /// </summary>
	VideoInput::!VideoInput()
	{
		if(!_isDisposed)
		{
			delete _ptr;
			_isDisposed = true;
		}
	}
	/// <summary>
    /// Finalizer 
    /// </summary>
	VideoInput::~VideoInput()
	{
		this->!VideoInput();
	}
	#pragma endregion

	#pragma region Static methods
	/// <summary>
    /// Turns off console messages - default is to prInt32 messages
    /// </summary>
	void VideoInput::SetVerbose(Boolean verbose)
	{
		videoInput::setVerbose(verbose);
	}
	/// <summary>
    /// Functions in rough order they should be used.
    /// </summary>	
	/// <returns></returns>
	Int32 VideoInput::ListDevices()
	{
		return videoInput::listDevices();
	}
	/// <summary>
    /// Functions in rough order they should be used.
    /// </summary>
	/// <param name="silent"></param>
	/// <returns></returns>
	Int32 VideoInput::ListDevices(Boolean silent)
	{
		return videoInput::listDevices(silent);
	}
	/// <summary>
    /// Needs to be called after listDevices - otherwise returns null
    /// </summary>
	/// <param name="deviceID"></param>
	/// <returns></returns>
	String^  VideoInput::GetDeviceName(Int32 deviceID)
	{
		char* ptr = videoInput::getDeviceName(deviceID);
		if(ptr == nullptr)
			return nullptr;
		else
			return gcnew String(ptr);
	}
	#pragma endregion

	#pragma region Instance Methods
	/// <summary>
    /// Choose to use callback based capture - or single threaded
    /// </summary>
	/// <param name="useCallback"></param>
	void VideoInput::SetUseCallback(Boolean useCallback)
	{
		if(_isDisposed)
			throw gcnew ObjectDisposedException("videoInput");
		_ptr->setUseCallback(useCallback);
	}
	/// <summary>
    /// Call before setupDevice.
	/// DirectShow will try and get the closest possible framerate to what is requested.
    /// </summary>
	/// <param name="deviceID"></param>
	/// <param name="idealFramerate"></param>
	void VideoInput::SetIdealFramerate(Int32 deviceID, Int32 idealFramerate)
	{
		if(_isDisposed)
			throw gcnew ObjectDisposedException("videoInput");
		_ptr->setIdealFramerate(deviceID, idealFramerate);
	}
	/// <summary>
    /// Some devices will stop delivering frames after a while - this method gives you the option to try and reconnect
	/// to a device if videoInput detects that a device has stopped delivering frames. 
	/// You MUST CALL isFrameNew every app loop for this to have any effect
    /// </summary>
	/// <param name="deviceNumber"></param>
	/// <param name="doReconnect"></param>
	/// <param name="numMissedFramesBeforeReconnect"></param>
	void VideoInput::SetAutoReconnectOnFreeze(Int32 deviceNumber, Boolean doReconnect, Int32 numMissedFramesBeforeReconnect)
	{
		if(_isDisposed)
			throw gcnew ObjectDisposedException("videoInput");
		_ptr->setAutoReconnectOnFreeze(deviceNumber, doReconnect, numMissedFramesBeforeReconnect);
	}
	/// <summary>
    /// Choose one of these four to setup your device
    /// </summary>
	/// <param name="deviceID"></param>
	/// <returns></returns>
	Boolean VideoInput::SetupDevice(Int32 deviceID)
	{
		if(_isDisposed)
			throw gcnew ObjectDisposedException("videoInput");
		return _ptr->setupDevice(deviceID);
	}
	/// <summary>
    /// Choose one of these four to setup your device
    /// </summary>
	/// <param name="deviceID"></param>
	/// <param name="w"></param>
	/// <param name="h"></param>
	/// <returns></returns>
	Boolean VideoInput::SetupDevice(Int32 deviceID, Int32 w, Int32 h)
	{
		if(_isDisposed)
			throw gcnew ObjectDisposedException("videoInput");
		return _ptr->setupDevice(deviceID, w, h);
	}
	/// <summary>
    /// These two are only for capture cards.
	/// USB and Firewire cameras souldn't specify connection 
    /// </summary>
	/// <param name="deviceID"></param>
	/// <param name="connection"></param>
	/// <returns></returns>
	Boolean VideoInput::SetupDevice(Int32 deviceID, Int32 connection)
	{
		if(_isDisposed)
			throw gcnew ObjectDisposedException("videoInput");
		return _ptr->setupDevice(deviceID, connection);
	}
	/// <summary>
    /// These two are only for capture cards.
	/// USB and Firewire cameras souldn't specify connection 
    /// </summary>
	/// <param name="deviceID"></param>
	/// <param name="w"></param>
	/// <param name="h"></param>
	/// <param name="connection"></param>
	/// <returns></returns>
	Boolean VideoInput::SetupDevice(Int32 deviceID, Int32 w, Int32 h, Int32 connection)
	{
		if(_isDisposed)
			throw gcnew ObjectDisposedException("videoInput");
		return _ptr->setupDevice(deviceID, w, h, connection);
	}
	/// <summary>
    /// If you need to you can set your NTSC/PAL/SECAM
	/// preference here. if it is available it will be used.
	/// see #defines above for available formats - eg VI_NTSC_M or VI_PAL_B
	/// should be called after setupDevice
	/// can be called multiple times 
    /// </summary>
	/// <param name="deviceNumber"></param>
	/// <param name="format"></param>
	/// <returns></returns>
	Boolean VideoInput::SetFormat(Int32 deviceNumber, VideoInputFormat format)
	{
		if(_isDisposed)
			throw gcnew ObjectDisposedException("videoInput");
		return _ptr->setFormat(deviceNumber, static_cast<int>(format));
	}
	/// <summary>
    /// Tells you when a new frame has arrived - you should call this if you have specified setAutoReconnectOnFreeze to true
    /// </summary>
	/// <param name="deviceID"></param>
	/// <returns></returns>
	Boolean VideoInput::IsFrameNew(Int32 deviceID)
	{
		if(_isDisposed)
			throw gcnew ObjectDisposedException("videoInput");
		return _ptr->isFrameNew(deviceID);
	}
	/// <summary>
    /// 
    /// </summary>
	/// <param name="deviceID"></param>
	/// <returns></returns>
	Boolean VideoInput::IsDeviceSetup(Int32 deviceID)
	{
		if(_isDisposed)
			throw gcnew ObjectDisposedException("videoInput");
		return _ptr->isDeviceSetup(deviceID);
	}
	/// <summary>
    /// Returns the pixels
    /// </summary>
	/// <param name="deviceID"></param>
	/// <returns>pixel data</returns>
	IntPtr VideoInput::GetPixels(Int32 deviceID)
	{
		if(_isDisposed)
			throw gcnew ObjectDisposedException("videoInput");
		return IntPtr(_ptr->getPixels(deviceID));
	}
	/// <summary>
    /// Returns the pixels
    /// </summary>
	/// <param name="deviceID"></param>
	/// <param name="flipRedAndBlue">toggles RGB/BGR flipping</param>
	/// <returns>pixel data</returns>
	IntPtr VideoInput::GetPixels(Int32 deviceID, Boolean flipRedAndBlue)
	{
		if(_isDisposed)
			throw gcnew ObjectDisposedException("videoInput");
		return IntPtr(_ptr->getPixels(deviceID, flipRedAndBlue));
	}
	/// <summary>
    /// Returns the pixels
    /// </summary>
	/// <param name="deviceID"></param>
	/// <param name="flipRedAndBlue">toggles RGB/BGR flipping</param>
	/// <param name="flipImage">If true, you can flip the image</param>
	/// <returns>pixel data</returns>
	IntPtr VideoInput::GetPixels(Int32 deviceID, Boolean flipRedAndBlue, Boolean flipImage)
	{
		if(_isDisposed)
			throw gcnew ObjectDisposedException("videoInput");
		return IntPtr(_ptr->getPixels(deviceID, flipRedAndBlue, flipImage));
	}
	/// <summary>
    /// Get the pixels. Pass in a buffer for getPixels to fill returns true if successful.
    /// </summary>
	/// <param name="id"></param>
	/// <param name="pixels">pixel data</param>
	/// <returns>true if successful</returns>
	Boolean VideoInput::GetPixels(Int32 id, IntPtr pixels)
	{
		if(_isDisposed)
			throw gcnew ObjectDisposedException("videoInput");
		return _ptr->getPixels(id, static_cast<unsigned char*>(pixels.ToPointer()));
	}
	/// <summary>
    /// Get the pixels. Pass in a buffer for getPixels to fill returns true if successful.
    /// </summary>
	/// <param name="id"></param>
	/// <param name="pixels">pixel data</param>
	/// <param name="flipRedAndBlue">toggles RGB/BGR flipping</param>
	/// <returns>true if successful</returns>
	Boolean VideoInput::GetPixels(Int32 id, IntPtr pixels, Boolean flipRedAndBlue)
	{
		if(_isDisposed)
			throw gcnew ObjectDisposedException("videoInput");
		return _ptr->getPixels(id, static_cast<unsigned char*>(pixels.ToPointer()), flipRedAndBlue);
	}
	/// <summary>
    /// Get the pixels. Pass in a buffer for getPixels to fill returns true if successful.
    /// </summary>
	/// <param name="id"></param>
	/// <param name="pixels">pixel data</param>
	/// <param name="flipRedAndBlue">toggles RGB/BGR flipping</param>
	/// <param name="flipImage">If true, you can flip the image</param>
	/// <returns>true if successful</returns>
	Boolean VideoInput::GetPixels(Int32 id, IntPtr pixels, Boolean flipRedAndBlue, Boolean flipImage)
	{
		if(_isDisposed)
			throw gcnew ObjectDisposedException("videoInput");
		return _ptr->getPixels(id, static_cast<unsigned char*>(pixels.ToPointer()), flipRedAndBlue, flipImage);
	}
	/// <summary>
    /// Get the pixels. Pass in a buffer for getPixels to fill returns true if successful.
    /// </summary>
	/// <param name="id"></param>
	/// <param name="pixels">pixel data</param>
	/// <returns>true if successful</returns>
	Boolean VideoInput::GetPixels(Int32 id, array<Byte>^ pixels)
	{
		if(_isDisposed)
			throw gcnew ObjectDisposedException("videoInput");
		if(pixels == nullptr)
			throw gcnew ArgumentNullException("pixels");
		pin_ptr<unsigned char> pixelsPin = &pixels[0];
		return _ptr->getPixels(id, pixelsPin);
	}
	/// <summary>
    /// Get the pixels. Pass in a buffer for getPixels to fill returns true if successful.
    /// </summary>
	/// <param name="id"></param>
	/// <param name="pixels">pixel data</param>
	/// <param name="flipRedAndBlue">toggles RGB/BGR flipping</param>
	/// <returns>true if successful</returns>
	Boolean VideoInput::GetPixels(Int32 id, array<Byte>^ pixels, Boolean flipRedAndBlue)
	{
		if(_isDisposed)
			throw gcnew ObjectDisposedException("videoInput");
		if(pixels == nullptr)
			throw gcnew ArgumentNullException("pixels");
		pin_ptr<unsigned char> pixelsPin = &pixels[0];
		return _ptr->getPixels(id, pixelsPin, flipRedAndBlue);
	}
	/// <summary>
    /// Get the pixels. Pass in a buffer for getPixels to fill returns true if successful.
    /// </summary>
	/// <param name="id"></param>
	/// <param name="pixels">pixel data</param>
	/// <param name="flipRedAndBlue">toggles RGB/BGR flipping</param>
	/// <param name="flipImage">If true, you can flip the image</param>
	/// <returns>true if successful</returns>
	Boolean VideoInput::GetPixels(Int32 id, array<Byte>^ pixels, Boolean flipRedAndBlue, Boolean flipImage)
	{
		if(_isDisposed)
			throw gcnew ObjectDisposedException("videoInput");
		if(pixels == nullptr)
			throw gcnew ArgumentNullException("pixels");
		pin_ptr<unsigned char> pixelsPin = &pixels[0];
		return _ptr->getPixels(id, pixelsPin, flipRedAndBlue, flipImage);
	}
	/// <summary>
    /// Launches a pop up settings window.
	/// For some reason in GLUT you have to call it twice each time.
    /// </summary>
	/// <param name="deviceID"></param>
	void VideoInput::ShowSettingsWindow(Int32 deviceID)
	{
		if(_isDisposed)
			throw gcnew ObjectDisposedException("videoInput");
		_ptr->showSettingsWindow(deviceID);
	}
	/// <summary>
    /// 
    /// </summary>
	/// <param name="deviceID"></param>
	/// <param name="Property"></param>
	/// <param name="lValue"></param>
	/// <returns>true if successful</returns>
	Boolean VideoInput::SetVideoSettingFilter(Int32 deviceID, Int32 Property, Int32 lValue)
	{
		if(_isDisposed)
			throw gcnew ObjectDisposedException("videoInput");
		return _ptr->setVideoSettingFilter(deviceID, Property, lValue);
	}
	/// <summary>
    /// 
    /// </summary>
	/// <param name="deviceID"></param>
	/// <param name="Property"></param>
	/// <param name="lValue"></param>
	/// <param name="Flags"></param>
	/// <returns>true if successful</returns>
	Boolean VideoInput::SetVideoSettingFilter(Int32 deviceID, Int32 Property, Int32 lValue, Int32 Flags)
	{
		if(_isDisposed)
			throw gcnew ObjectDisposedException("videoInput");
		return _ptr->setVideoSettingFilter(deviceID, Property, lValue, Flags);
	}
	/// <summary>
    /// 
    /// </summary>
	/// <param name="deviceID"></param>
	/// <param name="Property"></param>
	/// <param name="lValue"></param>
	/// <param name="Flags"></param>
	/// <param name="useDefaultValue"></param>
	/// <returns>true if successful</returns>
	Boolean VideoInput::SetVideoSettingFilter(Int32 deviceID, Int32 Property, Int32 lValue, Int32 Flags, Boolean useDefaultValue)
	{
		if(_isDisposed)
			throw gcnew ObjectDisposedException("videoInput");
		return _ptr->setVideoSettingFilter(deviceID, Property, lValue, Flags, useDefaultValue);
	}
	/// <summary>
    /// 
    /// </summary>
	/// <param name="deviceID"></param>
	/// <param name="Property"></param>
	/// <param name="pctValue"></param>
	/// <returns>true if successful</returns>
	Boolean VideoInput::SetVideoSettingFilterPct(Int32 deviceID, Int32 Property, Single pctValue)
	{
		if(_isDisposed)
			throw gcnew ObjectDisposedException("videoInput");
		return _ptr->setVideoSettingFilterPct(deviceID, Property, pctValue);
	}
	/// <summary>
    /// 
    /// </summary>
	/// <param name="deviceID"></param>
	/// <param name="Property"></param>
	/// <param name="pctValue"></param>
	/// <param name="Flags"></param>
	/// <returns>true if successful</returns>
	Boolean VideoInput::SetVideoSettingFilterPct(Int32 deviceID, Int32 Property, Single pctValue, Int32 Flags)
	{
		if(_isDisposed)
			throw gcnew ObjectDisposedException("videoInput");
		return _ptr->setVideoSettingFilterPct(deviceID, Property, pctValue, Flags);
	}
	/// <summary>
    /// 
    /// </summary>
	/// <param name="deviceID"></param>
	/// <param name="Property"></param>
	/// <param name="min"></param>
	/// <param name="max"></param>
	/// <param name="SteppingDelta"></param>
	/// <param name="currentValue"></param>
	/// <param name="flags"></param>
	/// <param name="defaultValue"></param>
	/// <returns>true if successful</returns>
	Boolean VideoInput::GetVideoSettingFilter(Int32 deviceID, Int32 Property, [Out] Int32% min, [Out] Int32% max, [Out] Int32% SteppingDelta, [Out] Int32% currentValue, [Out] Int32% flags, [Out] Int32% defaultValue)
	{
		if(_isDisposed)
			throw gcnew ObjectDisposedException("videoInput");
		long min_, max_, SteppingDelta_, currentValue_, flags_, defaultValue_;
		Boolean result = _ptr->getVideoSettingFilter(deviceID, Property, min_, max_, SteppingDelta_, currentValue_, flags_, defaultValue_);
		min = min_;
		max = max_;
		SteppingDelta = SteppingDelta_;
		currentValue = currentValue_;
		flags = flags_;
		defaultValue = defaultValue_;
		return result;
	}
	/// <summary>
    /// 
    /// </summary>
	/// <param name="deviceID"></param>
	/// <param name="Property"></param>
	/// <param name="lValue"></param>
	/// <returns>true if successful</returns>
	Boolean VideoInput::SetVideoSettingCamera(Int32 deviceID, Int32 Property, Int32 lValue)
	{
		if(_isDisposed)
			throw gcnew ObjectDisposedException("videoInput");
		return _ptr->setVideoSettingCamera(deviceID, Property, lValue);
	}
	/// <summary>
    /// 
    /// </summary>
	/// <param name="deviceID"></param>
	/// <param name="Property"></param>
	/// <param name="lValue"></param>
	/// <param name="Flags"></param>
	/// <returns>true if successful</returns>
	Boolean VideoInput::SetVideoSettingCamera(Int32 deviceID, Int32 Property, Int32 lValue, Int32 Flags)
	{
		if(_isDisposed)
			throw gcnew ObjectDisposedException("videoInput");
		return _ptr->setVideoSettingCamera(deviceID, Property, lValue, Flags);
	}
	/// <summary>
    /// 
    /// </summary>
	/// <param name="deviceID"></param>
	/// <param name="Property"></param>
	/// <param name="lValue"></param>
	/// <param name="Flags"></param>
	/// <param name="useDefaultValue"></param>
	/// <returns>true if successful</returns>
	Boolean VideoInput::SetVideoSettingCamera(Int32 deviceID, Int32 Property, Int32 lValue, Int32 Flags, Boolean useDefaultValue)
	{
		if(_isDisposed)
			throw gcnew ObjectDisposedException("videoInput");
		return _ptr->setVideoSettingCamera(deviceID, Property, lValue, Flags, useDefaultValue);
	}
	/// <summary>
    /// 
    /// </summary>
	/// <param name="deviceID"></param>
	/// <param name="Property"></param>
	/// <param name="pctValue"></param>
	/// <returns>true if successful</returns>
	Boolean VideoInput::SetVideoSettingCameraPct(Int32 deviceID, Int32 Property, Single pctValue)
	{
		if(_isDisposed)
			throw gcnew ObjectDisposedException("videoInput");
		return _ptr->setVideoSettingCameraPct(deviceID, Property, pctValue);
	}
	/// <summary>
    /// 
    /// </summary>
	/// <param name="deviceID"></param>
	/// <param name="Property"></param>
	/// <param name="pctValue"></param>
	/// <param name="Flags"></param>
	/// <returns>true if successful</returns>
	Boolean VideoInput::SetVideoSettingCameraPct(Int32 deviceID, Int32 Property, Single pctValue, Int32 Flags)
	{
		if(_isDisposed)
			throw gcnew ObjectDisposedException("videoInput");
		return _ptr->setVideoSettingCameraPct(deviceID, Property, pctValue, Flags);
	}
	/// <summary>
    /// 
    /// </summary>
	/// <param name="deviceID"></param>
	/// <param name="Property"></param>
	/// <param name="min"></param>
	/// <param name="max"></param>
	/// <param name="SteppingDelta"></param>
	/// <param name="currentValue"></param>
	/// <param name="flags"></param>
	/// <param name="defaultValue"></param>
	/// <returns>true if successful</returns>
	Boolean VideoInput::GetVideoSettingCamera(Int32 deviceID, Int32 Property, [Out] Int32% min, Int32% max, [Out] Int32% SteppingDelta, [Out] Int32% currentValue, [Out] Int32% flags, [Out] Int32% defaultValue)
	{
		if(_isDisposed)
			throw gcnew ObjectDisposedException("videoInput");
		long min_, max_, SteppingDelta_, currentValue_, flags_, defaultValue_;
		Boolean result = _ptr->getVideoSettingCamera(deviceID, Property, min_, max_, SteppingDelta_, currentValue_, flags_, defaultValue_);
		min = min_;
		max = max_;
		SteppingDelta = SteppingDelta_;
		currentValue = currentValue_;
		flags = flags_;
		defaultValue = defaultValue_;
		return result;
	}
	//get width, height and number of pixels
	/// <summary>
    /// Get width
    /// </summary>
	/// <param name="deviceID"></param>
	/// <returns></returns>
	Int32 VideoInput::GetWidth(Int32 deviceID)
	{
		if(_isDisposed)
			throw gcnew ObjectDisposedException("videoInput");
		return _ptr->getWidth(deviceID);
	}
	/// <summary>
    /// Get height
    /// </summary>
	/// <param name="deviceID"></param>
	/// <returns></returns>
	Int32 VideoInput::GetHeight(Int32 deviceID)
	{
		if(_isDisposed)
			throw gcnew ObjectDisposedException("videoInput");
		return _ptr->getHeight(deviceID);
	}
	/// <summary>
    /// Get number of pixels
    /// </summary>
	/// <param name="deviceID"></param>
	/// <returns></returns>
	Int32 VideoInput::GetSize(Int32 deviceID)
	{
		if(_isDisposed)
			throw gcnew ObjectDisposedException("videoInput");
		return _ptr->getSize(deviceID);
	}
	/// <summary>
    /// Completely stops and frees a device
    /// </summary>
	/// <param name="deviceID"></param>
	/// <returns></returns>
	void VideoInput::StopDevice(Int32 deviceID)
	{
		if(_isDisposed)
			throw gcnew ObjectDisposedException("videoInput");
		_ptr->stopDevice(deviceID);
	}
	/// <summary>
    /// Completely stops and frees a device but then sets it up with same settings
    /// </summary>
	/// <param name="deviceID"></param>
	/// <returns>true if successful</returns>
	Boolean VideoInput::RestartDevice(Int32 deviceID)
	{
		if(_isDisposed)
			throw gcnew ObjectDisposedException("videoInput");
		return _ptr->restartDevice(deviceID);
	}
	#pragma endregion

	#pragma region Properties
	/// <summary>
	/// Number of devices available
	/// </summary>
	Int32 VideoInput::DevicesFound::get() 
	{	
		if(_isDisposed)
			throw gcnew ObjectDisposedException("videoInput");
		return _ptr->devicesFound;
	}
	void VideoInput::DevicesFound::set(Int32 value) 
	{	
		if(_isDisposed)
			throw gcnew ObjectDisposedException("videoInput");
		_ptr->devicesFound = value;
	}	
	Int32 VideoInput::PropBrightness::get()
	{
		if(_isDisposed)
			throw gcnew ObjectDisposedException("videoInput");
		return _ptr->propBrightness;
	}
	void VideoInput::PropBrightness::set(Int32 value) 
	{
		if(_isDisposed)
			throw gcnew ObjectDisposedException("videoInput");
		_ptr->propBrightness = value;
	}
	Int32 VideoInput::PropContrast::get()
	{
		if(_isDisposed)
			throw gcnew ObjectDisposedException("videoInput");
		return _ptr->propContrast;
	}
	void VideoInput::PropContrast::set(Int32 value) 
	{
		if(_isDisposed)
			throw gcnew ObjectDisposedException("videoInput");
		_ptr->propContrast = value;
	}
	Int32 VideoInput::PropHue::get()
	{ 
		if(_isDisposed)
			throw gcnew ObjectDisposedException("videoInput");
		return _ptr->propHue;
	}
	void VideoInput::PropHue::set(Int32 value) 
	{ 
		if(_isDisposed)
			throw gcnew ObjectDisposedException("videoInput");
		_ptr->propHue = value;
	}
	Int32 VideoInput::PropSaturation::get()
	{ 
		if(_isDisposed)
			throw gcnew ObjectDisposedException("videoInput");
		return _ptr->propSaturation;
	}
	void VideoInput::PropSaturation::set(Int32 value) 
	{ 
		if(_isDisposed)
			throw gcnew ObjectDisposedException("videoInput");
		_ptr->propSaturation = value;
	}
	Int32 VideoInput::PropSharpness::get()
	{
		if(_isDisposed)
			throw gcnew ObjectDisposedException("videoInput");
		return _ptr->propSharpness;
	}
	void VideoInput::PropSharpness::set(Int32 value) 
	{
		if(_isDisposed)
			throw gcnew ObjectDisposedException("videoInput");
		_ptr->propSharpness = value;
	}
	Int32 VideoInput::PropGamma::get()
	{
		if(_isDisposed)
			throw gcnew ObjectDisposedException("videoInput");
		return _ptr->propGamma;
	}
	void VideoInput::PropGamma::set(Int32 value) 
	{
		if(_isDisposed)
			throw gcnew ObjectDisposedException("videoInput");
		_ptr->propGamma = value;
	}
	Int32 VideoInput::PropColorEnable::get()
	{
		if(_isDisposed)
			throw gcnew ObjectDisposedException("videoInput");
		return _ptr->propColorEnable;
	}
	void VideoInput::PropColorEnable::set(Int32 value) 
	{
		if(_isDisposed)
			throw gcnew ObjectDisposedException("videoInput");
		_ptr->propColorEnable = value;
	}
	Int32 VideoInput::PropWhiteBalance::get()
	{ 
		if(_isDisposed)
			throw gcnew ObjectDisposedException("videoInput");
		return _ptr->propWhiteBalance;
	}
	void VideoInput::PropWhiteBalance::set(Int32 value) 
	{ 
		if(_isDisposed)
			throw gcnew ObjectDisposedException("videoInput");
		_ptr->propWhiteBalance = value;
	}
	Int32 VideoInput::PropBacklightCompensation::get()
	{
		if(_isDisposed)
			throw gcnew ObjectDisposedException("videoInput");
		return _ptr->propBacklightCompensation;
	}
	void VideoInput::PropBacklightCompensation::set(Int32 value) 
	{
		if(_isDisposed)
			throw gcnew ObjectDisposedException("videoInput");
		_ptr->propBacklightCompensation = value;
	}
	Int32 VideoInput::PropGain::get()
	{ 
		if(_isDisposed)
			throw gcnew ObjectDisposedException("videoInput");
		return _ptr->propGain;
	}
	void VideoInput::PropGain::set(Int32 value) 
	{ 
		if(_isDisposed)
			throw gcnew ObjectDisposedException("videoInput");
		_ptr->propGain = value;
	}
	Int32 VideoInput::PropPan::get()
	{
		if(_isDisposed)
			throw gcnew ObjectDisposedException("videoInput");
		return _ptr->propPan;
	}
	void VideoInput::PropPan::set(Int32 value) 
	{
		if(_isDisposed)
			throw gcnew ObjectDisposedException("videoInput");
		_ptr->propPan = value;
	}
	Int32 VideoInput::PropTilt::get()
	{
		if(_isDisposed)
			throw gcnew ObjectDisposedException("videoInput");
		return _ptr->propTilt;
	}
	void VideoInput::PropTilt::set(Int32 value) 
	{
		if(_isDisposed)
			throw gcnew ObjectDisposedException("videoInput");
		_ptr->propTilt = value;
	}
	Int32 VideoInput::PropRoll::get()
	{ 
		if(_isDisposed)
			throw gcnew ObjectDisposedException("videoInput");
		return _ptr->propRoll;
	}
	void VideoInput::PropRoll::set(Int32 value) 
	{ 
		if(_isDisposed)
			throw gcnew ObjectDisposedException("videoInput");
		_ptr->propRoll = value;
	}
	Int32 VideoInput::PropZoom::get()
	{
		if(_isDisposed)
			throw gcnew ObjectDisposedException("videoInput");
		return _ptr->propZoom;
	}
	void VideoInput::PropZoom::set(Int32 value) 
	{
		if(_isDisposed)
			throw gcnew ObjectDisposedException("videoInput");
		_ptr->propZoom = value;
	}
	Int32 VideoInput::PropExposure::get()
	{
		if(_isDisposed)
			throw gcnew ObjectDisposedException("videoInput");
		return _ptr->propExposure;
	}
	void VideoInput::PropExposure::set(Int32 value) 
	{
		if(_isDisposed)
			throw gcnew ObjectDisposedException("videoInput");
		_ptr->propExposure = value;
	}
	Int32 VideoInput::PropIris::get()
	{
		if(_isDisposed)
			throw gcnew ObjectDisposedException("videoInput");
		return _ptr->propIris;
	}
	void VideoInput::PropIris::set(Int32 value) 
	{
		if(_isDisposed)
			throw gcnew ObjectDisposedException("videoInput");
		_ptr->propIris = value;
	}
	Int32 VideoInput::PropFocus::get()
	{
		if(_isDisposed)
			throw gcnew ObjectDisposedException("videoInput");
		return _ptr->propFocus;
	}
	void VideoInput::PropFocus::set(Int32 value) 
	{
		if(_isDisposed)
			throw gcnew ObjectDisposedException("videoInput");
		_ptr->propFocus = value;
	}
	#pragma endregion
}