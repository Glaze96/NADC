#pragma once

#include <vector>
#include <string>

#include <IrrKlang\irrKlang.h>
#include "playlist.h"

using namespace irrklang;

namespace glaze {
	namespace glibrary {

		class AudioManager {
		private:
			static std::vector<Playlist*> _playLists;
			static ISoundEngine *_engine;

		public:

			static void Init();

			static void AddPlayList(Playlist *playlist);

			inline static ISoundEngine* getEngine() {
				if (_engine == nullptr) {
					Init();
				}
				return _engine;
			}

			static Playlist* GetPlaylist(std::string name);

			//static bool Play(std::string filename);
		};


	} // End namespace glibrary
} // End namespace glaze