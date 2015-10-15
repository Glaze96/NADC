#include "playlist.h"

#include "..\console\log.h"

using namespace irrklang;

namespace glaze {
	namespace glibrary {

		Playlist::Playlist() 
			: _isPlaying(false), _currentTrackNumber(0), _numTracks(0) {
		}

		Playlist::Playlist(const std::string& name, const bool& looping, const std::string& filename, const int& num)
		: Playlist() {

			Log::AddMessage("Created playlist '" + name + "'; added '" + std::to_string(num) + "' sounds");
			
			_name = name;
			_looping = looping;

			for (int i = 1; i <= num; i++)
				Add(filename + std::to_string(i), true);

		}

		Playlist::Playlist(const std::string& name, const bool& looping, std::vector<Sound*> sounds)
			: Playlist() {

			Log::AddMessage("Created playlist '" + name + "'");

			_name = name;
			_looping = looping;

			Add(sounds);
		}

		Playlist::~Playlist() {
			for (auto& sound : _sounds)
				delete sound;

			_sounds.clear();
		}

		void Playlist::Toggle() {
			if (_isPlaying)
				Pause();
			else
				Resume();
		}

		void Playlist::Start() {
			Log::AddMessage("Starting playlist '" + _name + "'");
			Play(0);
		}

		void Playlist::Play(const int& index) {

			if (index < _numTracks) {
				_currentSound = _sounds.at(index);
				_currentSound->Play();
				_currentTrackNumber = index;
				_isPlaying = true;
			}
			else {
				Log::AddMessage("Tried to play a sound out of bounds in playlist '" + _name + "'", Message::Type::Warning);
			}
		}

		void Playlist::Play(const std::string& name) {
			int index = 0;
			for (auto& sound : _sounds) {
				if (sound->GetName() == name) {
					sound->Play();
					_currentSound = sound;
					_currentTrackNumber = index;
					_isPlaying = true;
					return;
				}
			}

			Log::AddMessage("Could not find sound '" + name + "' in playlist '" + _name + "'", Message::Type::Warning);
		}

		void Playlist::Add(std::vector<Sound*> sounds, const bool& supressLog) {
			for (auto& sound : sounds)
				Add(sound, supressLog);
		}

		void Playlist::Add(const std::string& filename, const bool& supressLog) {
			Add(new Sound(filename, filename), supressLog);
		}

		void Playlist::Add(Sound* sound, const bool& supressLog) {
			_numTracks++;
			_sounds.push_back(sound);
			
			if (!supressLog)
				Log::AddMessage("Added sound '" + sound->GetName() + "' to playlist '" + _name + "', current number of tracks is '" + std::to_string(_numTracks) + "'");
		}


		void Playlist::Stop() {
			if (_currentSound != nullptr) {
				_currentSound->Stop();
				_currentSound = nullptr;
				_isPlaying = false;

				Log::AddMessage("Stopping playlist '" + _name + "'");
			}
		}

		void Playlist::Pause() {
			if (_currentSound != nullptr) {
				_currentSound->Pause();
				_isPlaying = false;

				Log::AddMessage("Pausing playlist '" + _name + "'");
			}
		}

		void Playlist::Resume() {
			if (_currentSound != nullptr) {

				Log::AddMessage("Resuming playlist '" + _name + "'");

				_currentSound->Resume();
				_isPlaying = true;
			}
		}

		void Playlist::PlayNext() {
			Stop();

			_currentTrackNumber++;

			if (_currentTrackNumber >= _numTracks) {
				_currentTrackNumber = -1;

				Log::AddMessage("Looping playlist '" + _name + "'");
			}

			Play(_currentTrackNumber);
		}

		void Playlist::PlayRandom(const bool& notSame) {
			Stop();

			int randomNumber = 0;

			if (notSame) {
				while (true) {
					randomNumber = rand() % _numTracks;
					if (randomNumber != _currentTrackNumber) {
						break;
					}
				}
			}

			Play(randomNumber);
		}

		Sound* Playlist::GetSound(const std::string& name) const {
			for (Sound *sound : _sounds) {
				if (sound->GetName() == name) {
					return sound;
				}
			}

			Log::AddMessage("Could not find sound '" + name + "'", Message::Type::Warning);

			return nullptr;
		}

		void Playlist::Update() {
			if (_looping) {
				if (_currentSound != nullptr) {
					if (_currentSound->GetSound()->isFinished()) {
						PlayNext();
					}
				}
			}

		}

	} // End namespace glibrary
} // End namespace glaze