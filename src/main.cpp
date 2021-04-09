#include <irrKlang.h>

#include <algorithm>
#include <iostream>
#include <mutex>

#include "ProceduralAudioStreamLoader.h"
#include "ProceduralAudioStream.h"

#pragma comment(lib, "irrKlang.lib") // link with irrKlang.dll

using namespace irrklang;

float smoothstep(float x, float lower, float upper) {
	float t = std::clamp((x - lower) / (upper - lower), 0.f, 1.f);
	return t * t * (3.0f - 2.0f * t);
}

struct Generator {
	Generator(float length = 1.0f, uint32_t a0 = 137) : 
		t(0),
		aCurr(a0),
		length(length * 44100),
		fac (1e-4f)
	{
		aNext = nextHailstoneNumber(aCurr);
	}


	uint32_t nextHailstoneNumber(uint32_t x) {
		return x % 2 == 0 ? x / 2 : 3 * x + 1;
 	}

	ik_s32 operator()(void* data, ik_s32 framesToGenerate) {
		int16_t* buffer = (int16_t*)data;
		for (ik_s32 f = 0; f < framesToGenerate; ++f) {
			int limit = 0.75f * length;
			float w = smoothstep(t, limit, length);

			float s0 = std::sin(t * fac * aCurr);
			float s1 = std::sin(t * fac * aNext);

			buffer[2 * f] = buffer[2 * f + 1] = ((1.0f - w) * s0 + w * s1) * 800;
			t += 1;
			if (t == length) {
				aCurr = aNext;
				aNext = nextHailstoneNumber(aCurr);
				t = 0;
			}
		}
		return framesToGenerate;
	}

	int32_t t;
	uint32_t aCurr, aNext;
	float fac;
	int length;
};

int main() {
	// Define format for procedural sound
	SAudioStreamFormat format;
	format.ChannelCount = 2;
	format.FrameCount = -1;
	format.SampleFormat = ESampleFormat::ESF_S16;
	format.SampleRate = 44100;

	// Register generator

	// start the sound engine with default parameters
	ISoundEngine* engine = createIrrKlangDevice();
	if (!engine) {
		return EXIT_FAILURE;
	}

	// Create and register loader
	ProceduralAudioStreamLoader* loader = new ProceduralAudioStreamLoader();
	engine->registerAudioStreamLoader(loader);
	int t = 0;
	std::string name = loader->registerProducer("Uniform", Generator(), format);
	loader->drop();

	engine->play2D(name.c_str());

	char i = 0;
	while (i != 'q')
	{
		std::cout << "Enter 'q' to quit.\n";
		std::cin >> i; // wait for user to press some key
	}

	engine->drop();

	return EXIT_SUCCESS;
}