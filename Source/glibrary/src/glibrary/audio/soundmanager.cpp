#include "soundmanager.h"

#include "..\console\log.h"

using namespace irrklang;

namespace glaze {
	namespace glibrary {

		ISoundEngine*				SoundManager::_engine;
		std::vector<Playlist*>		SoundManager::_playlists;

		void SoundManager::Init() { 
			_engine = createIrrKlangDevice();
			if (_engine != nullptr)
				Log::AddMessage("Succsessfully initialized sound engine", Message::Type::Success);
			else
				Log::AddMessage("Failed to initialized sound engine", Message::Type::Error);
		}

		void SoundManager::AddPlayList(Playlist *playlist) { 
			_playlists.push_back(playlist);
		}

		Playlist *SoundManager::GetPlaylist(const std::string &name) {
			for (Playlist *playlist : _playlists) {
				if (playlist->getName() == name) {
					return playlist;
				}
			}
			Log::AddMessage("Could not find playlist '" + name + "'", Message::Type::Warning);
			return nullptr;
		}

		void SoundManager::Update() { 
			for (Playlist *playlist : _playlists) {
				playlist->Update();
			}
		}

		void SoundManager::Clean() { 
			for (unsigned int i = 0; i < _playlists.size(); i++) {
				delete _playlists[i];
				_playlists.erase(_playlists.begin() + i);

			}
			_engine->drop();
			_engine = nullptr;
		}

	}
}