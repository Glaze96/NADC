
#define DEBUG

// Glibrary includes
#include <Glibrary/engine/engine.h>
#include <Glibrary/audio/soundmanager.h>

// Gengine includes
#include "src/level/levelmanager.h"
#include "src/entity/creature/player.h"
#include "src/ui/uimanager.h"
#include "src/system/console.h"
#include "src/entity/entitytemplate.h"

using namespace glaze;
using namespace glibrary;
using namespace gengine;

class Game : public Engine {
private:

	Player* player;
	Vector2i gameWindowSize;
	Vector2i uiWindowSize;

	void InitSound() const {

	}

	// Runs at start of program
	void Init() override {
		Console::Init();
		EntityTemplate::Init();
		InitSound();

		player = new Player("Edward");
		LevelManager::GoDown(player);

		gameWindowSize = Vector2i(99, 99);

		UIManager::Init(99, 99, 51);
	}



	// Runs at targetUPS
	void Update(const float &updateTick, const int &ch) override {

		if (ch == (0x108 + (1)))
			Console::Input(player);
		
		// Update player
		player->Update(updateTick, ch);

	}

	// Runs at targetFPS
	void Draw() override {

		// Draw level, including entities
		LevelManager::getCurrentLevel()->Draw();

		// Draw player
		player->Draw();

		// Draw UI
		UIManager::Draw(player);
	}

	// Rus every second
	void Tick() override {

	}

public:
	Game(const int &gameWidth, const int &gameHeight, const int &targetFPS, const int &targetUPS, const bool &vSync)
		: Engine(gameWidth, gameHeight, targetFPS, targetUPS, vSync) { }
	~Game() { }
};

int main() {
	Game game(150, 99, 30, 35, true);

	game.Start();

	return 0;
}
