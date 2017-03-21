#include <msclr\marshal.h>
#include "Decoder.h"

using namespace msclr::interop;

namespace Starts2000
{
	namespace Audio
	{
		namespace Codecs
		{
			namespace Opus
			{
				Decoder::Decoder(
					Starts2000::Audio::Codecs::Opus::SampleRate sampleRate,
					Starts2000::Audio::Codecs::Opus::Channels channels) 
					: _sampleRate(sampleRate), _channels(channels)
				{
				}

				Decoder::~Decoder()
				{
					if (_decoder != nullptr)
					{
						opus_decoder_destroy(_decoder);
						_decoder = nullptr;
					}
				}

				void Decoder::Create()
				{
					int err;
					_decoder = opus_decoder_create(
						static_cast<int>(_sampleRate), static_cast<int>(_channels), &err);
					if (err != OPUS_OK) {
						auto pStr = opus_strerror(err);
						throw gcnew OpusException(static_cast<OpusErrorCode>(err), marshal_as<String^>(pStr));
					}
				}
			}
		}
	}
}