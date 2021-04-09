#include "ProceduralAudioStream.h"


namespace irrklang {
	ProceduralAudioStream::ProceduralAudioStream(const std::function<ik_s32(void*, ik_s32)>& gen, SAudioStreamFormat format) :
		_gen(gen),
		_format(format)
	{
	}

	ik_s32 ProceduralAudioStream::readFrames(void* target, ik_s32 frameCountToRead) {
		return _gen(target, frameCountToRead);
	}

	SAudioStreamFormat ProceduralAudioStream::getFormat() {
		return _format;
	}

	bool ProceduralAudioStream::setPosition(ik_s32) {
		return false;
	}

	bool ProceduralAudioStream::getIsSeekingSupported() {
		return false;
	}

	bool ProceduralAudioStream::isOK() {
		return true;
	}

}