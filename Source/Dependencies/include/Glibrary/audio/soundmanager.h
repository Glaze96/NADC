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
			static std::vector<PlayList*> _playLists;

		private: // 'structors
			SoundManager() { }

		public: // Public methods
			static void Init();
			void InitPlayLists();
			static void AddPlayList(PlayList *playlist);
			static PlayList* GetPlayList(const std::string &name);
			static void Update();
			static void Clean();

			friend class Sound;
		};

	}
}