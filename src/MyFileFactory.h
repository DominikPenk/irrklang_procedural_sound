#pragma once

#include "ik_IFileFactory.h"

namespace irrklang {
	class MyFileFactory : public IFileFactory {
	public:
		virtual irrklang::IFileReader* createFileReader(const ik_c8* filename) override;
	};
}