#include "sound.h"

#include "..\console\log.h"

#include "soundmanager.h"

using namespace irrklang;

namespace glaze {
	namespace glibrary {

		Sound::Sound(const std::string & name, const std::string & filename) {

			if (filename.find(".mp3") != -1) {
				Log::AddMessage("You should not add '.mp3' to filename!! Sound in question: " + name);
			}

			_name = name;
			_filename = "media/audio/" + filename + ".mp3";

			if (SoundManager::_engine == nullptr) {
				Log::AddMessage("Sound engine not initialized, initializing..");
				SoundManager::Init();
			}

			_soundSource = SoundManager::_engine->addSoundSourceFromFile(_filename.c_str(), ESM_AUTO_DETECT, true);
		}

		Sound::~Sound() {
			if (_sound != nullptr) {
				_sound->drop();
				delete _sound;
			}
			_soundSource->drop();
			delete _soundSource;
		}

		void Sound::Play(const bool &playPaused) {

			_sound = SoundManager::_engine->play2D(_soundSource, false, playPaused, true, false);

			if (!playPaused) {
				Log::AddMessage("Playing sound '" + _name + "'");
				_playing = true;
			}
		}

		void Sound::Loop() {
			Log::AddMessage("Looping sound '" + _name + "'");
			if (_sound == nullptr) {
				Play(true);
			}
			_sound->setIsLooped(true);
		}

		void Sound::Pause() {
			if (_sound == nullptr) {
				Play(true);
			}
			Log::AddMessage("Pausing sound '" + _name + "'");
			_playing = false;
			_sound->setIsPaused(true);
		}

		void Sound::Resume() {
			Log::AddMessage("Resuming sound '" + _name + "'");
			if (_sound == nullptr) {
				Play(true);
			}
			_playing = true;
			_sound->setIsPaused(false);
		}

		void Sound::Stop() {
			Log::AddMessage("Stopping sound '" + _name + "'");
			if (_sound == nullptr) {
				Play(true);
			}
			_playing = false;
			_sound->stop();
			_sound->drop();
			_sound = nullptr;
		}

		void Sound::SetGain(float gain) {
			Log::AddMessage("Setting gain of sound '" + _name + "' " + " to " + std::to_string(gain));
			if (_sound == nullptr) {
				Play(true);
			}
			_sound->setVolume(gain);
		}

		ISound* Sound::GetSound() {
			if (_sound == nullptr) {
				Play(true);
			}
			return _sound;
		}

	}
}