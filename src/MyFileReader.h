#pragma once

#include "ik_IFileReader.h"

#include <fstream>

namespace irrklang {
	class CallbackFileReader : public IFileReader
	{
	public:

		// constructor, store size of file and filename
		CallbackFileReader(const ik_c8* filename);

		~CallbackFileReader();

		//! reads data, returns how much was read
		ik_s32 read(void* buffer, ik_u32 sizeToRead);

		//! changes position in file, returns true if successful
		bool seek(ik_s32 finalPos, bool relativeMovement);

		//! returns size of file
		ik_s32 getSize();

		//! returns where in the file we are.
		ik_s32 getPos();

		//! returns name of file
		const ik_c8* getFileName();

		std::string _filename;
	};
}