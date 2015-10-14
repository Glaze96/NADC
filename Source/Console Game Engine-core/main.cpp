/*
TODO:
	-fix dual wield

	-fix eyes

	-ranged weapons

	-add monster drop

	-add more stats
		-attack
		-strength
		-dexterity
		-defense
		-

		maybe:
		-agility (will affect speed and dodging)
		-magic

	-expand fighting system
		-dodging
		-damage calculation

	-add leveling system
		-level
		-experience

	-potions
		-health
		-strength
		-other stat boosts

	-make uimanager independent from camera
	-make uis static

	-add item interaction audio
		-pickup
		-wield
		-wear

MAYBE TODO:

	-skills
		-potion making
		-mining
		-smithing
		-cooking
		-crafting

*/

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

	// Testelitest!

	// Fucking test number omg

	Player* player;
	Camera camera;

	// Runs at start of program
	void Init() override {
		EntityTemplate::Init();
		SoundManager::AddPlayList(new Playlist("Background music", true, "BGMusic/BGMusic", 7));
		SoundManager::AddPlayList(new Playlist("Hellos", false, "Hello/Hello", 4));
		SoundManager::AddPlayList(new Playlist("Ouches", false, "Ouch/Ouch", 3));

		camera = Camera(Vector2i(0, 0), Vector2i(0, 0), Vector2i(_gameWidth - 51, _gameHeight));

		UIManager::Init(camera);

		player = new Player("Edward");
		LevelManager::GoDown(player);
	}

	// Runs at targetUPS
	void Update(const float &updateTick, const int &ch) override {

#ifdef DEBUG
		if (ch == (0x108 + (1)))
			Console::Input(player);
		else if (ch == '+')
			LevelManager::GoUp(player);
		else if (ch == '-')
			LevelManager::GoDown(player);
		else if (ch == 'v')
			player->ToggleNoClip();
		else if (ch == 'b')
			LevelManager::getCurrentLevel()->SetAllVisible();
#endif

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
