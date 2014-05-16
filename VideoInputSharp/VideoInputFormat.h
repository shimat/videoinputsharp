#pragma once

using namespace System;

namespace VideoInputSharp
{
	/// <summary>
    /// Camera resolution
    /// </summary>
	public enum class VideoInputFormat : Int32
	{
		 NTSC_M = VI_NTSC_M,
		 PAL_B = VI_PAL_B,
		 PAL_D = VI_PAL_D,
		 PAL_G = VI_PAL_G,
		 PAL_H = VI_PAL_H,
		 PAL_I = VI_PAL_I,
		 PAL_M = VI_PAL_M,
		 PAL_N = VI_PAL_N,
		 PAL_NC = VI_PAL_NC,
		 SECAM_B = VI_SECAM_B,
		 SECAM_D = VI_SECAM_D,
		 SECAM_G = VI_SECAM_G,
		 SECAM_H = VI_SECAM_H,
		 SECAM_K = VI_SECAM_K,
		 SECAM_K1 = VI_SECAM_K1,
		 SECAM_L = VI_SECAM_L,
		 NTSC_M_J = VI_NTSC_M_J,
		 NTSC_433 = VI_NTSC_433,
	};
}