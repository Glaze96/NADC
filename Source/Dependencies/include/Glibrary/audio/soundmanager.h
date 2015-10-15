#pragma once

#include <string>
#include <vector>

#include <IrrKlang\irrKlang.h>

#include "playlist.h"

namespace glaze {
	namespace glibrary {

		class SoundManager {
		private: // Private fields
			static irrklang::ISoundEngine *_engine;
			static std::vector<Playlist*> _playlists;
		
		private: // 'structors
			SoundManager() { }

		public: // Public methods
			static void Init();
			static void AddPlayList(Playlist *playlist);
			static Playlist* GetPlaylist(const std::string &name);
			static void Update();
			static void Clean();

			friend class Sound;
		};

	}
}