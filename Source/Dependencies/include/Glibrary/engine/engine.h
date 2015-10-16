#pragma once

namespace glaze {
	namespace glibrary {

		class Engine {
		protected:
			unsigned int _gameWidth;
			unsigned int _gameHeight;
		private:
			unsigned int _targetFPS;
			unsigned int _targetUPS;
			bool _vSync;
			unsigned int _updatesPerSecond;
			unsigned int _framesPerSecond;

		public:
			Engine(const int &gameWidth, const int &gameHeight, const int &fps, const int &ups, const bool &vSync);
			virtual ~Engine();

		protected: // getters
			unsigned int getFPS() const { return _framesPerSecond; }
			unsigned int getUPS() const { return _updatesPerSecond; }

		public: // Public methods
			void Start();

		protected: // Protected methods
			void ShowFPS() const;
			// Runs at start
			virtual void Init() = 0;
			// Runs every targetUPS
			virtual void Update(const float &updateTick, const int &ch) = 0;
			// Runs every second
			virtual void Tick() = 0;
			// Runs every targetFPS
			virtual void Draw() = 0;

		private: // Private methods
			void Run();

		};

	} // End namespace glibrary
} // End namespace glaze