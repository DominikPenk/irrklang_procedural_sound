#pragma once

#include "ik_IAudioStream.h"

#include <functional>

namespace irrklang {

	class ProceduralAudioStream : public IAudioStream {
	public:
		ProceduralAudioStream(const std::function<ik_s32(void*, ik_s32)>& gen, SAudioStreamFormat format);

		virtual ik_s32 readFrames(void* target, ik_s32 frameCountToRead);

		virtual SAudioStreamFormat getFormat();

		virtual bool setPosition(ik_s32);

		virtual bool getIsSeekingSupported();

		bool isOK();

	private:
		SAudioStreamFormat _format;
		std::function<ik_s32(void*, ik_s32)> _gen;
	};

}