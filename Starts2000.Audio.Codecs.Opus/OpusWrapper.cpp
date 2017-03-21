#include <msclr\marshal.h>
#include "OpusWrapper.h"

using namespace msclr::interop;

namespace Starts2000 {
	namespace Audio {
		namespace Codecs {
			namespace Opus {
#pragma region OpusEncoder
				String^ OpusWrapper::OpusGetVersionString()
				{
					auto ver = opus_get_version_string();					
					return marshal_as<String^>(ver);
				}

				String^ OpusWrapper::OpusStrError(OpusErrorCode errorCode)
				{
					auto errStr = opus_strerror(static_cast<int>(errorCode));
					return marshal_as<String^>(errStr);
				}

				int OpusWrapper::OpusEncoderGetSize(Channels channels)
				{
					return opus_encoder_get_size(static_cast<int>(channels));
				}

				IntPtr OpusWrapper::OpusEncoderCreate(
					SampleRate fs,
					Channels channels,
					OpusApplication application,
					[Out]OpusErrorCode^% errorCode)
				{
					int err;

					auto encoder = opus_encoder_create(
						static_cast<opus_int32>(fs),
						static_cast<int>(channels),
						static_cast<int>(application),
						&err);
					errorCode = static_cast<OpusErrorCode>(err);

					return static_cast<IntPtr>(encoder);
				}

				OpusErrorCode OpusWrapper::OpusEncoderInit(IntPtr encoder,
					SampleRate fs, Channels channels, OpusApplication application)
				{
					auto errorCode = opus_encoder_init(
						static_cast<OpusEncoder*>(encoder.ToPointer()),
						static_cast<opus_int32>(fs),
						static_cast<int>(channels),
						static_cast<int>(application));

					return static_cast<OpusErrorCode>(errorCode);
				}

				OpusErrorCode OpusWrapper::OpusEncode(IntPtr encoder,
					array<Byte>^ pcm, int frameSize, [Out]array<Byte>^% data, Int32 maxDataBytes)
				{
					data = nullptr;
					pin_ptr<void> pPcm = &pcm[0];
					unsigned char* pData = new unsigned char[maxDataBytes];

					auto ret = opus_encode(
						static_cast<OpusEncoder*>(encoder.ToPointer()),
						static_cast<const opus_int16*>(pPcm),
						frameSize,
						pData,
						maxDataBytes);

					if (ret > 0)
					{
						data = gcnew array<Byte>(ret);
						pin_ptr<Byte> pDataArr = &data[0];
						memcpy(pDataArr, pData, ret);
						ret = 0;
					}

					delete[] pData;

					return static_cast<OpusErrorCode>(ret);
				}

				OpusErrorCode OpusWrapper::OpusEncodeFloat(IntPtr encoder, 
					array<Single>^ pcm, int frameSize, array<Byte>^% data, Int32 maxDataBytes)
				{
					data = nullptr;
					pin_ptr<void> pPcm = &pcm[0];
					unsigned char* pData = new unsigned char[maxDataBytes];

					auto ret = opus_encode_float(
						static_cast<OpusEncoder*>(encoder.ToPointer()),
						static_cast<const float*>(pPcm),
						frameSize,
						pData,
						maxDataBytes);

					if (ret > 0)
					{
						data = gcnew array<Byte>(ret);
						pin_ptr<Byte> pDataArr = &data[0];
						memcpy(pDataArr, pData, ret);
						ret = 0;
					}

					delete[] pData;

					return static_cast<OpusErrorCode>(ret);
				}

				OpusErrorCode OpusWrapper::OpusEncoderCtl(IntPtr encoder, int request, int value)
				{
					auto ret = opus_encoder_ctl(
						static_cast<OpusEncoder *>(encoder.ToPointer()),
						request,
						value);
					return static_cast<OpusErrorCode>(ret);
				}

				OpusErrorCode OpusWrapper::OpusEncoderCtl(IntPtr encoder, int request, int ^% value)
				{
					value = nullptr;
					int outValue;

					auto ret = opus_encoder_ctl(
						static_cast<OpusEncoder *>(encoder.ToPointer()),
						request,
						&outValue);

					if (ret == OPUS_OK)
					{
						value = outValue;
					}

					return static_cast<OpusErrorCode>(ret);
				}

				void OpusWrapper::OpusEncoderDestroy(IntPtr encoder)
				{
					opus_encoder_destroy(static_cast<OpusEncoder *>(encoder.ToPointer()));
				}
#pragma endregion

#pragma region OpusDecoder
				int OpusWrapper::OpusDecoderGetSize(Channels channels)
				{
					return opus_decoder_get_size(static_cast<int>(channels));
				}

				IntPtr OpusWrapper::OpusDecoderCreate(
					SampleRate fs,
					Channels channels,
					[Out]OpusErrorCode^% errorCode)
				{
					int err;

					auto decoder = opus_decoder_create(
						static_cast<opus_int32>(fs),
						static_cast<int>(channels),
						&err);
					errorCode = static_cast<OpusErrorCode>(err);

					return static_cast<IntPtr>(decoder);
				}

				OpusErrorCode OpusWrapper::OpusDecoderInit(IntPtr decoder, SampleRate fs, Channels channels)
				{
					auto errorCode = opus_decoder_init(
						static_cast<OpusDecoder*>(decoder.ToPointer()),
						static_cast<opus_int32>(fs),
						static_cast<int>(channels));

					return static_cast<OpusErrorCode>(errorCode);
				}

				OpusErrorCode OpusWrapper::OpusDecode(IntPtr decode,
					array<Byte>^ data, int len, IntPtr pcm, int frameSize, int decodeFec)
				{
					pin_ptr<void> pData = &data[0];
					int ret = opus_decode(
						static_cast<OpusDecoder *>(decode.ToPointer()),
						static_cast<const unsigned char *>(pData),
						len,
						static_cast<opus_int16 *>(pcm.ToPointer()),
						frameSize,
						decodeFec);

					return static_cast<OpusErrorCode>(ret);
				}

				OpusErrorCode OpusWrapper::OpusDecodeFloat(IntPtr decode,
					array<Byte>^ data, int len, IntPtr pcm, int frameSize, int decodeFec)
				{
					pin_ptr<void> pData = &data[0];
					int ret = opus_decode_float(
						static_cast<OpusDecoder *>(decode.ToPointer()),
						static_cast<const unsigned char *>(pData),
						len,
						static_cast<float *>(pcm.ToPointer()),
						frameSize,
						decodeFec);

					return static_cast<OpusErrorCode>(ret);
				}

				OpusErrorCode OpusWrapper::OpusDecoderCtl(IntPtr decoder, int request, int value)
				{
					auto ret = opus_decoder_ctl(
						static_cast<OpusDecoder *>(decoder.ToPointer()),
						request,
						value);
					return static_cast<OpusErrorCode>(ret);
				}

				OpusErrorCode OpusWrapper::OpusDecoderCtl(IntPtr decoder, int request, int ^% value)
				{
					value = nullptr;
					int outValue;

					auto ret = opus_decoder_ctl(
						static_cast<OpusDecoder *>(decoder.ToPointer()),
						request,
						&outValue);

					if (ret == OPUS_OK)
					{
						value = outValue;
					}

					return static_cast<OpusErrorCode>(ret);
				}

				void OpusWrapper::OpusDecoderDestroy(IntPtr decoder)
				{
					opus_decoder_destroy(static_cast<OpusDecoder *>(decoder.ToPointer()));
				}
#pragma endregion
			}
		}
	}
}
