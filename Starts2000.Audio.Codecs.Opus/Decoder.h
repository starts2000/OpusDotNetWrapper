#pragma once

#include "OpusCommon.h"

using namespace System;
using namespace System::Runtime::InteropServices;

namespace Starts2000
{
	namespace Audio
	{
		namespace Codecs
		{
			namespace Opus
			{
				public ref class Decoder
				{
				public:
					Decoder(SampleRate sampleRate, Channels channels);
					virtual ~Decoder();

					property SampleRate SampleRate
					{
						Starts2000::Audio::Codecs::Opus::SampleRate get()
						{
							return _sampleRate;
						}
					}

					property Channels Channels
					{
						Starts2000::Audio::Codecs::Opus::Channels get()
						{
							return _channels;
						}
					}

				private:
					void Create();

					Starts2000::Audio::Codecs::Opus::SampleRate _sampleRate;
					Starts2000::Audio::Codecs::Opus::Channels _channels;
					OpusDecoder* _decoder;
				};
			}
		}
	}
}