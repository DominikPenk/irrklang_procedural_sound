#include "ProceduralAudioStreamLoader.h"

#include "ProceduralAudioStream.h"

#include <filesystem>
#include <fstream>
#include <iostream>

namespace irrklang {
	ProceduralAudioStreamLoader::ProceduralAudioStreamLoader()
	{
	}

	ProceduralAudioStreamLoader::~ProceduralAudioStreamLoader()
	{
	}

	bool ProceduralAudioStreamLoader::isALoadableFileExtension(const ik_c8* fileName)
	{
#ifdef _DEBUG
		std::cout << "ProceduralAudioStreamLoader::isALoadableFileExtension(\"" << fileName << "\")\n";
#endif
		return std::filesystem::path(fileName).extension() == PROCEDURAL_EXTENSION;
	}

	IAudioStream* ProceduralAudioStreamLoader::createAudioStream(IFileReader* file)
	{
		std::string name = std::string(file->getFileName());
		name = name.substr(0, name.length() - std::strlen(PROCEDURAL_EXTENSION));
		if (_producers.find(name) != _producers.end()) {
			auto [gen, format] = _producers[name];
			return new ProceduralAudioStream(gen, format);
		}
		return nullptr;
	}

	bool ProceduralAudioStreamLoader::registerProducer(const ik_c8* name, SoundCallback gen, SAudioStreamFormat format)
	{
		std::string _name = name;
		if (_producers.find(_name) != _producers.end()) { return false; }
		_producers[_name] = { gen, format };
		return true;
	}
}
