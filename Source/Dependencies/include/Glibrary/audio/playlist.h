#pragma once

#include <string>
#include <vector>

#include "sound.h"

using namespace irrklang;

namespace glaze {
	namespace glibrary {

		class PlayList {
		private: // Private fields
			std::string _name;
			bool _looping;
			bool _isPlaying;
			int _currentTrackNumber;
			int _numTracks;
			Sound *_currentSound;
			std::vector<Sound*> _sounds;

		public:
			PlayList();
			PlayList(const std::string& name, const bool& looping, const std::string& filename, const int& num);
			PlayList(const std::string& name, const bool& looping, std::vector<Sound*> sounds);
			~PlayList();

		public: // Public getters
			std::string getName() const { return _name; }
			bool IsPlaying() const { return _isPlaying; }

		public: // Public methods
			void Toggle();
			void Start();
			void Stop();
			void Pause();
			void Resume();

			void Play(const int& index);
			void Play(const std::string& name);
			void PlayNext();
			void PlayRandom(const bool& notSame = false);

			Sound* GetSound(const std::string& name) const;

			void Update();

		private: // Private methods
			void Add(std::vector<Sound*> sounds, const bool& supressLog = false);
			void Add(const std::string& filename, const bool& supressLog = false);
			void Add(Sound* sound, const bool& supressLog = false);
		};


	} // End namespace glibrary
} // End namespace glaze