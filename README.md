# IrrKlang sound from Callback
This repo is an attempt to implement sound generation from an arbitrary callback function. Similar to the functionality provided by SDL [SDL_OpenAudio](http://dranger.com/ffmpeg/functions.html#SDL_OpenAudio).

Note that this project was only tested on Windows and Visual Studio 2019.

## Implementation
To pass callbacks to IrrKlang I implemented a new irrklang::IAudioStream(Loader) class that handles all callback sounds.
All callbacks need to be registered with the new IAudioStreamLoader to be found later. Since IrrKlang suggests to distinguish which irrklang::IAudioStreamLoader to use based on extension you will need to add an extension (by default defined to be ".__irrk") to the name of your callback.

Unfortunately, the default IrrKlang FileReader requires an existing file or no sound will be played. I therefore implemented an new irrklang::IFileReader that handles the callback methods. 

I also added a wrapper around irrklang::ISoundEngine that has an additional method **addSoundSourceFromCallback** which handles things like adding the file extension and registering the callback.

## Usage
```C++
#include "MySoundEngine.h"

#pragma comment(lib, "irrKlang.lib") // link with irrKlang.dll

using namespace irrklang;

struct Generator {
    // This function is the as irrklang::IAudioStream::readFrames
    ik_s32 operator()(void* data, ik_s32 framesToGenerate) { ... }
};

...

SAudioFormat format; // Set the correct format

MySoundEngine engine;

// Create the sound source (MySoundEngine will handle adding the name extension and registering the callback)
ISoundSource* source = engine->addSoundSourceFromCallback(Generator(), "soundName", format);

// You may also find use this: engine->play2D(engine->getSoundSource("uniform"));
engine->play2D(source); 
```

A simple example can be found in [main.cpp](./src/main.cpp). 

## Compilation
The provided [./CmakeLists.txt](CMakeLists file)
