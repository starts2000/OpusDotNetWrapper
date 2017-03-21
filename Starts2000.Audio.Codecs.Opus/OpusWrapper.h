#pragma once

#include "OpusCommon.h"

using namespace System;
using namespace System::Runtime::InteropServices;

namespace Starts2000 {
	namespace Audio {
		namespace Codecs {
			namespace Opus {
				public ref class OpusWrapper abstract sealed
				{
				public:
					static String^ OpusGetVersionString();
					static String^ OpusStrError(OpusErrorCode errorCode);

					static int OpusEncoderGetSize(Channels channels);
					static IntPtr OpusEncoderCreate(
						SampleRate fs,
						Channels channels,
						OpusApplication application,
						[Out]OpusErrorCode^% errorCode);
					static OpusErrorCode OpusEncoderInit(
						IntPtr encoder,
						SampleRate fs,
						Channels channels,
						OpusApplication application);
					static OpusErrorCode OpusEncode(
						IntPtr encoder,
						array<byte>^ pcm,
						int frameSize,
						[Out]array<Byte>^% data,
						Int32 maxDataBytes);
					static OpusErrorCode OpusEncodeFloat(
						IntPtr encoder,
						array<Single>^ pcm,
						int frameSize,
						[Out]array<Byte>^% data,
						Int32 maxDataBytes);
					static OpusErrorCode OpusEncoderCtl(IntPtr encoder, int request, int value);
					static OpusErrorCode OpusEncoderCtl(IntPtr encoder, int request, [Out]int^% value);
					static void OpusEncoderDestroy(IntPtr encoder);

					static int OpusDecoderGetSize(Channels channels);
					static IntPtr OpusDecoderCreate(
						SampleRate fs,
						Channels channels,
						[Out]OpusErrorCode^% errorCode);
					static OpusErrorCode OpusDecoderInit(
						IntPtr decode,
						SampleRate fs,
						Channels channels);
					static OpusErrorCode OpusDecode(
						IntPtr decode,
						array<Byte>^ data,
						int len,
						IntPtr pcm,
						int frameSize,
						int decodeFec);
					static OpusErrorCode OpusDecodeFloat(
						IntPtr decode,
						array<Byte>^ data,
						int len,
						IntPtr pcm,
						int frameSize,
						int decodeFec);
					static OpusErrorCode OpusDecoderCtl(IntPtr decode, int request, int value);
					static OpusErrorCode OpusDecoderCtl(IntPtr decode, int request, [Out]int^% value);
					static void OpusDecoderDestroy(IntPtr decode);
				};
			}
		}
	}
}

