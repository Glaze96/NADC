#include "playlist.h"

#include "..\console\log.h"

using namespace irrklang;

namespace glaze {
	namespace glibrary {

		Playlist::Playlist(const std::string & name, const bool & looping, const std::string & filename, const int & num) {
			_name = name;
			_looping = looping;

			_numTracks = 0;
			_isPlaying = false;
			_currentTrackNumber = 0;

			Log::AddMessage("Created playlist '" + _name + "'");

			for (int i = 1; i < num + 1; i++) {
				Add(filename + std::to_string(i));
			}
		}

		Playlist::Playlist(const std::string &name, const bool &looping, std::vector<Sound*> sounds) {

			_name = name;
			_looping = looping;

			_numTracks = 0;
			_isPlaying = false;
			_currentTrackNumber = 0;


			Log::AddMessage("Created playlist '" + _name + "'");

			Add(sounds);
		}

		Playlist::~Playlist() {

			for (unsigned int i = 0; i < _sounds.size(); i++) {
				delete _sounds[i];
				_sounds.erase(_sounds.begin() + i);

			}

		}

		void Playlist::Toggle() {
			if (_isPlaying) {
				Pause();
			}
			else {
				Resume();
			}
		}

		void Playlist::Start() {
			Log::AddMessage("Starting playlist '" + _name + "'");
			Play(0);
		}

		void Playlist::Play(const int &index) {

			if (index < _numTracks) {
				_currentSound = _sounds.at(index);
				_currentSound->Play();
				_currentTrackNumber = index;
				_isPlaying = true;
			}
			else {
				Log::AddMessage("Tried to play a sound out of bounds in playlist '" + _name + "'");
			}
		}

		void Playlist::Play(const std::string & name) {
			for (unsigned int i = 0; i < _sounds.size(); i++) {
				Sound *sound = _sounds.at(i);
				if (sound->GetName() == name) {
					sound->Play();
					_currentSound = sound;
					_currentTrackNumber = i;
					_isPlaying = true;
					return;
				}
			}
			Log::AddMessage("Could not find sound '" + name + "' in playlist '" + _name + "'");
		}

		void Playlist::Add(std::vector<Sound*> sounds) {
			for (Sound *sound : sounds) {
				Add(sound);
			}
		}

		void Playlist::Add(const std::string &filename) {

			Sound *sound = new Sound(filename, filename);
			_numTracks++;
			Log::AddMessage("Added sound '" + sound->GetName() + "' to playlist '" + _name + "', current number of tracks is '" + std::to_string(_numTracks) + "'");
			_sounds.push_back(sound);
		}

		void Playlist::Add(Sound *sound) {
			_numTracks++;
			Log::AddMessage("Added sound '" + sound->GetName() + "' to playlist '" + _name + "', current number of tracks is '" + std::to_string(_numTracks) + "'");
			_sounds.push_back(sound);
		}


		void Playlist::Stop() {
			if (_currentSound != nullptr) {
				Log::AddMessage("Stopping playlist '" + _name + "'");
				_currentSound->Stop();
				_currentSound = nullptr;
				_isPlaying = false;
			}
		}

		void Playlist::Pause() {
			if (_currentSound != nullptr) {
				Log::AddMessage("Pausing playlist '" + _name + "'");
				_currentSound->Pause();
				_isPlaying = false;
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

			if (_currentTrackNumber + 1 >= _numTracks) {
				Log::AddMessage("Looping playlist '" + _name + "'");
				_currentTrackNumber = -1;
			}

			_currentTrackNumber++;
			Log::AddMessage("Playing next sound in playlist '" + _name + "', current track number '" + std::to_string((_currentTrackNumber)) + "'");
			Play(_currentTrackNumber);
		}

		void Playlist::PlayRandom(const bool &notSame) {
			Stop();

			Log::AddMessage("Playing random sound from playlist '" + _name + "'");

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

		Sound *Playlist::GetSound(const std::string &name) {
			for (Sound *sound : _sounds) {
				if (sound->GetName() == name) {
					return sound;
				}
			}
			Log::AddMessage("Could not find sound '" + name + "'");
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