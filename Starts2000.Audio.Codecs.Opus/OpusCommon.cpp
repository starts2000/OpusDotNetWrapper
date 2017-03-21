#include "OpusCommon.h"

namespace Starts2000
{
	namespace Audio
	{
		namespace Codecs
		{
			namespace Opus
			{
				OpusException::OpusException(OpusErrorCode errorCode, String^ errorString)
				{
					_errorCode = errorCode;
					_errorString = errorString;
				}
			}
		}
	}
}
