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
		// Delete all files stored
		for (auto [key, _] : _producers) {
#ifdef _DEBUG
			std::cout << "Deleting temporary file " << key << std::endl;;
#endif
			std::filesystem::remove(key);
		}
	}

	bool ProceduralAudioStreamLoader::isALoadableFileExtension(const ik_c8* fileName)
	{
		return std::filesystem::path(fileName).extension() == PROCEDURAL_EXTENSION;
	}

	IAudioStream* ProceduralAudioStreamLoader::createAudioStream(IFileReader* file)
	{
		if (_producers.find(file->getFileName()) != _producers.end()) {
			auto [gen, format] = _producers[file->getFileName()];
			return new ProceduralAudioStream(gen, format);
		}
		return nullptr;
	}

	std::string ProceduralAudioStreamLoader::registerProducer(std::string name, std::function<ik_s32(void*, ik_s32)> gen, SAudioStreamFormat format)
	{
		_producers[name + PROCEDURAL_EXTENSION] = { gen, format };
		// Create a file with this name
		std::string filename = name + PROCEDURAL_EXTENSION;

		if (!std::filesystem::exists(filename)) {
#ifdef _DEBUG
			std::cout << "Creating temporary file " << filename << std::endl;;
#endif
			std::ofstream f(filename);
			if (!f.is_open()) { std::cerr << "Could not create file\n"; }
		}
		return filename;
	}
}
