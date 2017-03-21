#pragma once

#include <opus_defines.h>
#include <opus_types.h>
#include <opus.h>
#include <opus_multistream.h>
#include <opus_custom.h>

using namespace System;

namespace Starts2000
{
	namespace Audio
	{
		namespace Codecs
		{
			namespace Opus
			{
				/// <summary>
				/// Error codes.
				/// </summary>
				public enum class OpusErrorCode
				{
					/// <summary>
					/// No error.
					/// </summary>
					Ok = OPUS_OK,
					/// <summary>
					/// One or more invalid/out of range arguments.
					/// </summary>
					BadArg = OPUS_BAD_ARG,
					/// <summary>
					/// Not enough bytes allocated in the buffer.
					/// </summary>
					BufferTooSmall = OPUS_BUFFER_TOO_SMALL,
					/// <summary>
					/// An internal error was detected.
					/// </summary>
					InternalError = OPUS_INTERNAL_ERROR,
					/// <summary>
					/// The compressed data passed is corrupted.
					/// </summary>
					InvalidPacket = OPUS_INVALID_PACKET,
					/// <summary>
					/// Invalid/unsupported request number.
					/// </summary>
					UnImplemented = OPUS_UNIMPLEMENTED,
					/// <summary>
					/// An encoder or decoder structure is invalid or already freed.
					/// </summary>
					InvalidState = OPUS_INVALID_STATE,
					/// <summary>
					/// Memory allocation has failed.
					/// </summary>
					AllocFail = OPUS_ALLOC_FAIL
				};

				/// <summary>
				/// Sample rate to decode or encode at (Hz).
				/// </summary>
				public enum class SampleRate
				{
					/// <summary>
					/// 8000 Hz.
					/// </summary>
					Hz_8K = 8000,
					/// <summary>
					/// 12000 Hz.
					/// </summary>
					Hz_12K = 12000,
					/// <summary>
					/// 16000 Hz.
					/// </summary>
					Hz_16K = 16000,
					/// <summary>
					/// 24000 Hz.
					/// </summary>
					Hz_24K = 24000,
					/// <summary>
					/// 48000 Hz.
					/// </summary>
					Hz_48K = 48000
				};

				/// <summary>
				/// Number of channels (1 or 2) in input signal.
				/// </summary>
				public enum class Channels
				{
					/// <summary>
					/// 1.
					/// </summary>
					Mono = 1,
					// <summary>
					/// 2.
					/// </summary>
					Stereo = 2
				};
         
				public enum class OpusApplication
				{
					Voip = OPUS_APPLICATION_VOIP,
					Audio = OPUS_APPLICATION_AUDIO,
					RestrictedLowDelay = OPUS_APPLICATION_RESTRICTED_LOWDELAY
				};

				public ref class OpusException : Exception
				{
				public:
					OpusException(OpusErrorCode errorCode, String^ errorString);

					property OpusErrorCode ErrorCode
					{
						OpusErrorCode get()
						{
							return _errorCode;
						}
					}

					property String^ ErrorString
					{
						String^ get()
						{
							return _errorString;
						}
					}

				private:
					OpusErrorCode _errorCode;
					String^ _errorString;
				};
			}
		}
	}
}

