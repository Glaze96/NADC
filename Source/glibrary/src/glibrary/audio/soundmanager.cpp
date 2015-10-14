#include "soundmanager.h"

#include "..\console\log.h"

using namespace irrklang;

namespace glaze {
	namespace glibrary {

		irrklang::ISoundEngine*		SoundManager::_engine;
		std::vector<Playlist*>		SoundManager::_playlists;

		void SoundManager::Init() { 
			_engine = createIrrKlangDevice();
			if (_engine == nullptr) {
				Log::AddMessage("Failed to initialized sound engine");
			}
			else {
				Log::AddMessage("Succsessfully initialized sound engine");
			}
		}

		void SoundManager::AddPlayList(Playlist *playlist) { 
			_playlists.push_back(playlist);
			Log::AddMessage("Added playlist '" + playlist->getName() + "'");
		}

		Playlist *SoundManager::GetPlaylist(const std::string &name) {
			for (Playlist *playlist : _playlists) {
				if (playlist->getName() == name) {
					return playlist;
				}
			}
			Log::AddMessage("Could not find playlist '" + name + "'");
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