#pragma once

#include <string>

#include <IrrKlang\irrKlang.h>

namespace glaze {
	namespace glibrary {
		class Sound {
		private:
			std::string _name;
			std::string _filename;

			irrklang::ISoundSource* _soundSource;
			irrklang::ISound* _sound;

			bool _playing;
			float _gain;

		public:
			Sound(const std::string& name, const std::string& filename);
			~Sound();

			void Play(const bool &playPaused = false);
			void Loop();
			void Pause();
			void Resume();
			void Stop();

			void SetGain(float gain);

			irrklang::ISound* GetSound();
			const bool& IsPlaying() const { return _playing; }
			const float& GetGain() const { return _gain; }
			const std::string& GetName() const { return _name; }
			const std::string& GetFileName() const { return _filename; }

			//friend void destroy_on_finish(ga_Handle* in_handle, void* in_context);
			//friend void loop_on_finish(ga_Handle* in_handle, void* in_context);

		};
	}
}