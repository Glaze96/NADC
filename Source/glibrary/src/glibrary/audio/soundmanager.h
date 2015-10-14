#pragma once

#include <string>
#include <vector>

#include <IrrKlang\irrKlang.h>

#include "playlist.h"

namespace glaze {
	namespace glibrary {

		class SoundManager {
		private:
			friend class Sound;

			static irrklang::ISoundEngine *_engine;
			static std::vector<Playlist*> _playlists;

		public:
			static void Init();
			static void AddPlayList(Playlist *playlist);
			static Playlist* GetPlaylist(const std::string &name);
			static void Update();
			static void Clean();

		private:
			SoundManager() { }
		};

	}
}