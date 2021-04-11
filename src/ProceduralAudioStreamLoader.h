#pragma once


#include <functional>
#include <unordered_map>

#include "ik_IAudioStreamLoader.h"
#include "ik_IAudioStream.h"

#include "defines.h"

namespace irrklang {

	class ProceduralAudioStreamLoader : public IAudioStreamLoader {
	public:
		ProceduralAudioStreamLoader();
		~ProceduralAudioStreamLoader();
		virtual bool isALoadableFileExtension(const ik_c8* fileName);
		virtual IAudioStream* createAudioStream(irrklang::IFileReader* file);

		bool registerProducer(const ik_c8* name, SoundCallback gen, SAudioStreamFormat format);

	private:
		std::unordered_map<
			std::string, 
			std::pair<
				SoundCallback, 
				SAudioStreamFormat>> _producers;
	};

}