#include "MyFileFactory.h"

#include <filesystem>
#include <iostream>

#include "defines.h"
#include "MyFileReader.h"

irrklang::IFileReader* irrklang::MyFileFactory::createFileReader(const ik_c8* filename)
{
	std::filesystem::path path(filename);

	// Check if this is a callback
	if (path.extension() != PROCEDURAL_EXTENSION) {
		// If we return nullptr, the default file reader will handle this file
		return nullptr;
	}
	else {
		// TODO: Check if this name was registered
		return new CallbackFileReader(filename);
	}
}
