#pragma once

#include <irrKlang.h>

#include <functional>

#include "ProceduralAudioStreamLoader.h"

namespace irrklang {

	class MySoundEngine {
	public:
		MySoundEngine(E_SOUND_OUTPUT_DRIVER driver = ESOD_AUTO_DETECT,
			int options = ESEO_DEFAULT_OPTIONS,
			const char* deviceID = 0,
			const char* sdk_version_do_not_use = IRR_KLANG_VERSION);
		~MySoundEngine();

		const char* getDriverName();
		
		ISound* play2D(const char* soundFileName, bool playLooped = false, bool startPaused = false, bool track = false, E_STREAM_MODE streamMode = ESM_AUTO_DETECT, bool enableSoundEffects = false);
		ISound* play2D(ISoundSource* source, bool playLooped = false, bool startPaused = false, bool track = false, bool enableSoundEffects = false);
		
		ISound* play3D(const char* soundFileName, vec3df pos, bool playLooped = false, bool startPaused = false, bool track = false, E_STREAM_MODE streamMode = ESM_AUTO_DETECT, bool enableSoundEffects = false);
		
		ISound* play3D(ISoundSource* source, vec3df pos, bool playLooped = false, bool startPaused = false, bool track = false, bool enableSoundEffects = false);
		void stopAllSounds();
		void setAllSoundsPaused(bool bPaused = true);
		
		ISoundSource* getSoundSource(const ik_c8* soundName, bool addIfNotFound = true);
		ISoundSource* getSoundSource(ik_s32 index);
		ik_s32 getSoundSourceCount();

		ISoundSource* addSoundSourceFromFile(const ik_c8* fileName, E_STREAM_MODE mode = ESM_AUTO_DETECT, bool preload = false);
		ISoundSource* addSoundSourceFromMemory(void* memory, ik_s32 sizeInBytes, const ik_c8* soundName, bool copyMemory = true);
		ISoundSource* addSoundSourceFromPCMData(void* memory, ik_s32 sizeInBytes, const ik_c8* soundName, SAudioStreamFormat format, bool copyMemory = true);
		ISoundSource* addSoundSourceFromCallback(SoundCallback callback, const ik_c8* soundName, SAudioStreamFormat format);
		ISoundSource* addSoundSourceAlias(ISoundSource* baseSource, const ik_c8* soundName);
		
		void removeSoundSource(ISoundSource* source);
		void removeSoundSource(const ik_c8* name);
		void removeAllSoundSources();
		
		void setSoundVolume(ik_f32 volume);
		ik_f32 getSoundVolume();
		
		void setListenerPosition(const vec3df& pos, const vec3df& lookdir, const vec3df& velPerSecond = vec3df(0, 0, 0), const vec3df& upVector = vec3df(0, 1, 0));
		
		void update();
		
		bool isCurrentlyPlaying(const char* soundName);
		bool isCurrentlyPlaying(ISoundSource* source);
		
		void stopAllSoundsOfSoundSource(ISoundSource* source);
		
		void registerAudioStreamLoader(IAudioStreamLoader* loader);
		
		bool isMultiThreaded() const;
		
		void addFileFactory(IFileFactory* fileFactory);
		
		void setDefault3DSoundMinDistance(ik_f32 minDistance);
		ik_f32 getDefault3DSoundMinDistance();
		
		void setDefault3DSoundMaxDistance(ik_f32 maxDistance);
		ik_f32 getDefault3DSoundMaxDistance();
		
		void setRolloffFactor(ik_f32 rolloff);
		
		void setDopplerEffectParameters(ik_f32 dopplerFactor = 1.0f, ik_f32 distanceFactor = 1.0f);
		
		bool loadPlugins(const ik_c8* path);
		
		const SInternalAudioInterface& getInternalAudioInterface();
		
		bool setMixedDataOutputReceiver(ISoundMixedOutputReceiver* receiver);
	
	private:
		ISoundEngine* _engine;
		ProceduralAudioStreamLoader* _loader;
	};

}