#include "soundmanager.h"

#include "..\console\log.h"

using namespace irrklang;

namespace glaze {
	namespace glibrary {

		ISoundEngine*				SoundManager::_engine;
		std::vector<PlayList*>		SoundManager::_playLists;

		void SoundManager::InitPlayLists() {
			AddPlayList(new PlayList("Background music", true, "BGMusic/BGMusic", 7));
			AddPlayList(new PlayList("Hellos", false, "Hello/Hello", 4));
			AddPlayList(new PlayList("Ouches", false, "Ouch/Ouch", 3));
		}

		void SoundManager::Init() { 
			_engine = createIrrKlangDevice();
			if (_engine != nullptr)
				Log::AddMessage("Successfully initialized sound engine", Message::Type::Success);
			else
				Log::AddMessage("Failed to initialized sound engine", Message::Type::Error);
		}

		void SoundManager::AddPlayList(PlayList *playlist) { 
			_playLists.push_back(playlist);
		}

		PlayList *SoundManager::GetPlayList(const std::string &name) {
			for (PlayList *playlist : _playLists) {
				if (playlist->getName() == name) {
					return playlist;
				}
			}
			Log::AddMessage("Could not find play list '" + name + "'", Message::Type::Warning);
			return nullptr;
		}

		void SoundManager::Update() { 
			for (PlayList *playlist : _playLists) {
				playlist->Update();
			}
		}

		void SoundManager::Clean() { 
			for (unsigned int i = 0; i < _playLists.size(); i++) {
				delete _playLists[i];
				_playLists.erase(_playLists.begin() + i);

			}
			_engine->drop();
			_engine = nullptr;
		}

	}
}