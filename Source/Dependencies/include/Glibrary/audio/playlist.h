#pragma once

#include <string>
#include <vector>

#include "sound.h"

using namespace irrklang;

namespace glaze {
	namespace glibrary {

		class Playlist {
		private: // Private fields
			std::string _name;
			bool _looping;
			bool _isPlaying;
			int _currentTrackNumber;
			int _numTracks;
			Sound *_currentSound;
			std::vector<Sound*> _sounds;

		public:
			Playlist(const std::string &name, const bool &looping, const std::string &filename, const int &num);
			Playlist(const std::string &name, const bool &looping, std::vector<Sound*> sounds);
			~Playlist();

		private: // Private methods
			void Add(const std::string &filename);
			void Add(Sound* sound);
			void Add(std::vector<Sound*> sounds);

		public: // Public methods
			void Toggle();
			void Start();
			void Stop();
			void Pause();
			void Resume();

			void Play(const int &index);
			void Play(const std::string& name);
			void PlayNext();
			void PlayRandom(const bool &notSame = false);

			Sound* GetSound(const std::string& name);

			void Update();

		public: // Public getters
			inline std::string getName() const { return _name; }
			inline bool IsPlaying() const { return _isPlaying; }
		};


	} // End namespace glibrary
} // End namespace glaze