#pragma once


#include <functional>
#include <unordered_map>

#include "ik_IAudioStreamLoader.h"
#include "ik_IAudioStream.h"

#ifndef PROCEDURAL_EXTENSION
#define PROCEDURAL_EXTENSION ".__irrk"
#endif

namespace irrklang {

	class ProceduralAudioStreamLoader : public IAudioStreamLoader {
	public:
		ProceduralAudioStreamLoader();
		~ProceduralAudioStreamLoader();
		virtual bool isALoadableFileExtension(const ik_c8* fileName);
		virtual IAudioStream* createAudioStream(irrklang::IFileReader* file);

		std::string registerProducer(std::string name, std::function<ik_s32(void*, ik_s32)> gen, SAudioStreamFormat format);

	private:
		std::unordered_map<
			std::string, 
			std::pair<
				std::function<ik_s32(void*, ik_s32)>, 
				SAudioStreamFormat>> _producers;
	};

}