#include "MyFileReader.h"

#include <filesystem>
#include <iostream>

#include "defines.h"

irrklang::CallbackFileReader::CallbackFileReader(const ik_c8* filename)
{

	_filename = std::string(filename);
}

irrklang::CallbackFileReader::~CallbackFileReader()
{
}

irrklang::ik_s32 irrklang::CallbackFileReader::read(void* buffer, ik_u32 sizeToRead)
{
#ifdef _DEBUG
	std::cout << "CallbackFileReader::read()\n";
#endif
	return 0;
}

bool irrklang::CallbackFileReader::seek(ik_s32 finalPos, bool relativeMovement)
{
#ifdef _DEBUG
	std::cout << "CallbackFileReader::seek()\n";
#endif
	return true;
} 

irrklang::ik_s32 irrklang::CallbackFileReader::getSize() {
#ifdef _DEBUG
	std::cout << "CallbackFileReader::getSize()\n";
#endif
	return 0;
}

irrklang::ik_s32 irrklang::CallbackFileReader::getPos() {
#ifdef _DEBUG
	std::cout << "CallbackFileReader::getPose()\n";
#endif
	return 0;
}

const irrklang::ik_c8* irrklang::CallbackFileReader::getFileName() {
	return _filename.c_str();
}
