#include "MySoundEngine.h"

#include "MyFileFactory.h"
#include "ProceduralAudioStreamLoader.h"

using namespace irrklang;

irrklang::MySoundEngine::MySoundEngine(E_SOUND_OUTPUT_DRIVER driver,
	int options,
	const char* deviceID,
	const char* sdk_version_do_not_use)
{
	_engine = createIrrKlangDevice(driver, options, deviceID, sdk_version_do_not_use);
	
	if (_engine) {
		MyFileFactory* factory = new MyFileFactory();
		_engine->addFileFactory(factory);
		factory->drop();

		_loader = new ProceduralAudioStreamLoader();
		_engine->registerAudioStreamLoader(_loader);
	}
}

irrklang::MySoundEngine::~MySoundEngine()
{
	if (_engine) {
		_engine->drop();
	}
	if (_loader) {
		_loader->drop();
	}
}

const char* MySoundEngine::getDriverName()
{
	return _engine->getDriverName();
}

ISound* MySoundEngine::play2D(const char* soundFileName, bool playLooped, bool startPaused, bool track, E_STREAM_MODE streamMode, bool enableSoundEffects)
{
	return _engine->play2D(soundFileName, playLooped, startPaused, track, streamMode);
}

ISound* MySoundEngine::play2D(ISoundSource* source, bool playLooped, bool startPaused, bool track, bool enableSoundEffects)
{
	return _engine->play2D(source, playLooped, startPaused, track, enableSoundEffects);
}

ISound* MySoundEngine::play3D(const char* soundFileName, vec3df pos, bool playLooped, bool startPaused, bool track, E_STREAM_MODE streamMode, bool enableSoundEffects)
{
	return _engine->play3D(soundFileName, pos, playLooped, startPaused, track, streamMode, enableSoundEffects);
}

ISound* MySoundEngine::play3D(ISoundSource* source, vec3df pos, bool playLooped, bool startPaused, bool track, bool enableSoundEffects)
{
	return _engine->play3D(source, pos, playLooped, startPaused, track, enableSoundEffects);
}

void MySoundEngine::stopAllSounds()
{
	_engine->stopAllSounds();
}

void MySoundEngine::setAllSoundsPaused(bool bPaused)
{
	_engine->setAllSoundsPaused(bPaused);
}

ISoundSource* MySoundEngine::getSoundSource(const ik_c8* soundName, bool addIfNotFound)
{
	return _engine->getSoundSource(soundName, addIfNotFound);
}

ISoundSource* MySoundEngine::getSoundSource(ik_s32 index)
{
	return _engine->getSoundSource(index);
}

ik_s32 MySoundEngine::getSoundSourceCount()
{
	return _engine->getSoundSourceCount();
}

ISoundSource* MySoundEngine::addSoundSourceFromFile(const ik_c8* fileName, E_STREAM_MODE mode, bool preload)
{
	return _engine->addSoundSourceFromFile(fileName, mode, preload);
}

ISoundSource* MySoundEngine::addSoundSourceFromMemory(void* memory, ik_s32 sizeInBytes, const ik_c8* soundName, bool copyMemory)
{
	return _engine->addSoundSourceFromMemory(memory, sizeInBytes, soundName, copyMemory);
}

ISoundSource* MySoundEngine::addSoundSourceFromPCMData(void* memory, ik_s32 sizeInBytes, const ik_c8* soundName, SAudioStreamFormat format, bool copyMemory)
{
	return _engine->addSoundSourceFromPCMData(memory, sizeInBytes, soundName, format, copyMemory);
}

ISoundSource* irrklang::MySoundEngine::addSoundSourceFromCallback(SoundCallback callback, const ik_c8* soundName, SAudioStreamFormat format)
{
	if (!_loader->registerProducer(soundName, callback, format)) {
		return nullptr;
	}
	std::string filename = std::string(soundName) + PROCEDURAL_EXTENSION;
	ISoundSource *source = addSoundSourceFromFile(filename.c_str());
	_engine->addSoundSourceAlias(source, soundName);	// So we can later find it again with the same name
}

ISoundSource* MySoundEngine::addSoundSourceAlias(ISoundSource* baseSource, const ik_c8* soundName)
{
	return _engine->addSoundSourceAlias(baseSource, soundName);
}

void MySoundEngine::removeSoundSource(ISoundSource* source)
{
	_engine->removeSoundSource(source);
}

void MySoundEngine::removeSoundSource(const ik_c8* name)
{
	_engine->removeSoundSource(name);
}

void MySoundEngine::removeAllSoundSources()
{
	_engine->removeAllSoundSources();
}

void MySoundEngine::setSoundVolume(ik_f32 volume)
{
	_engine->setSoundVolume(volume);
}

ik_f32 MySoundEngine::getSoundVolume()
{
	return _engine->getSoundVolume();
}

void MySoundEngine::setListenerPosition(const vec3df& pos, const vec3df& lookdir, const vec3df& velPerSecond, const vec3df& upVector)
{
	_engine->setListenerPosition(pos, lookdir, velPerSecond, upVector);
}

void MySoundEngine::update()
{
	_engine->update();
}

bool MySoundEngine::isCurrentlyPlaying(const char* soundName)
{
	return _engine->isCurrentlyPlaying(soundName);
}

bool MySoundEngine::isCurrentlyPlaying(ISoundSource* source)
{
	return _engine->isCurrentlyPlaying(source);
}

void MySoundEngine::stopAllSoundsOfSoundSource(ISoundSource* source)
{
	_engine->stopAllSoundsOfSoundSource(source);
}

void MySoundEngine::registerAudioStreamLoader(IAudioStreamLoader* loader)
{
	_engine->registerAudioStreamLoader(loader);
}

bool MySoundEngine::isMultiThreaded() const
{
	return _engine->isMultiThreaded();
}

void MySoundEngine::addFileFactory(IFileFactory* fileFactory)
{
	_engine->addFileFactory(fileFactory);
}

void MySoundEngine::setDefault3DSoundMinDistance(ik_f32 minDistance)
{
	_engine->setDefault3DSoundMinDistance(minDistance);
}

ik_f32 MySoundEngine::getDefault3DSoundMinDistance()
{
	return _engine->getDefault3DSoundMinDistance();
}

void MySoundEngine::setDefault3DSoundMaxDistance(ik_f32 maxDistance)
{
	_engine->setDefault3DSoundMaxDistance(maxDistance);
}

ik_f32 MySoundEngine::getDefault3DSoundMaxDistance()
{
	return _engine->getDefault3DSoundMaxDistance();
}

void MySoundEngine::setRolloffFactor(ik_f32 rolloff)
{
	return _engine->setRolloffFactor(rolloff);
}

void MySoundEngine::setDopplerEffectParameters(ik_f32 dopplerFactor, ik_f32 distanceFactor)
{
	_engine->setDopplerEffectParameters(dopplerFactor, distanceFactor);
}

bool MySoundEngine::loadPlugins(const ik_c8* path)
{
	return _engine->loadPlugins(path);
}

const SInternalAudioInterface& MySoundEngine::getInternalAudioInterface()
{
	return _engine->getInternalAudioInterface();
}

bool MySoundEngine::setMixedDataOutputReceiver(ISoundMixedOutputReceiver* receiver)
{
	return _engine->setMixedDataOutputReceiver(receiver);
}
