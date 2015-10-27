#include "engine.h"

// System includes
#include <thread>
#include <chrono>

// Glibrary includes
#include "../../curses/curses.h"
#include "../utils/timer.h"
#include "../console/io.h"
#include "../console/log.h"
#include "../graphics/color.h"
#include "../audio/soundmanager.h"

#include "../system/system.h"

using namespace std::chrono_literals;

namespace glaze {
	namespace glibrary {

		Engine::Engine(const int &gamwWidth, const int &gameHeight, const int &targetFPS, const int &targetUPS, const bool &vSync) {
			_gameWidth = gamwWidth;
			_gameHeight = gameHeight;
			_targetFPS = targetFPS;
			_targetUPS = targetUPS;
			_vSync = vSync;
			_updatesPerSecond = 0;
			_framesPerSecond = 0;
		}

		Engine::~Engine() {
			endwin();
		}

		void Engine::Start() {
			System::Init(_gameWidth, _gameHeight, true, true, false);

			SoundManager::Init();

			Init();
			Run();

		}

		void Engine::ShowFPS() const {
#ifdef _DEBUG
			Out::PrintlnAt(0, 0, "FPS: %i", getFPS());
#endif
		}

		void Engine::Run() {

			Timer *timer = new Timer();

			float tickTimer = 0.0f;
			float updateTimer = 0.0f;
			float drawTimer = 0.0f;

			float tickTick = 1.0f;
			float updateTick = 1.0f / _targetUPS;
			float drawTick = 1.0f / _targetFPS;

			unsigned int _updates = 0;
			unsigned int _frames = 0;


			while (1) {

				if (timer->Elapsed() - updateTimer > updateTick) {
					int ch = getch();
					Update(updateTick, ch);
					Log::Update(updateTick);
					SoundManager::Update();
					updateTimer += updateTick;
					_updates++;
				}

				if (timer->Elapsed() - drawTimer > drawTick) {
					clear();
					
					/* Begin drawing..*/
					Draw();
					Log::Print();
					ShowFPS();
					/* End drawing..*/

					refresh();
					
					Color::ResetCounter();
					drawTimer += drawTick;
					_frames++;
				}

				if (timer->Elapsed() - tickTimer > tickTick) {
					Tick();
					_framesPerSecond = _frames;
					_updatesPerSecond = _updates;
					_updates = 0;
					_frames = 0;
					tickTimer += tickTick;
				}
				

				if (_vSync) {
					std::this_thread::sleep_for(16ms);
				}

			}
			delete timer;
		}

	} // End namespace glibrary
} // End namespace glaze