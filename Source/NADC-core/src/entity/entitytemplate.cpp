#include "entitytemplate.h"

// System includes
#include <algorithm>

// Glibrary includes
#include <Glibrary/utils/utils.h>

// Gengine includes
#include "items/consumables/alcohol.h"
#include "items/consumables/food.h"
#include "items/equipment.h"
#include "creature/enemy.h"
#include "level/stairs.h"
#include "items/lightsource.h"
#include "newspawnsource.h"
#include "creature/shopkeeper.h"

namespace glaze {
	namespace gengine {

		typedef std::pair<float, SpawnSource> entitySource;

		std::vector<std::pair<float, SpawnSource>> EntityTemplate::allSources;

		std::vector<std::pair<float, SpawnSource>> EntityTemplate::newItemSources;
		std::vector<std::pair<float, SpawnSource>> EntityTemplate::newSpecialItemSources;
		std::vector<std::pair<float, SpawnSource>> EntityTemplate::newEnemySources;

		// Food
		Entity* berries = new Food("Berries", 2.0f);
		Entity* mushrooms = new Food("Mushrooms", 2.5f);
		Entity* cheese = new Food("Cheese", 8.00f);
		Entity* bread = new Food("Bread", 10.0f);
		Entity* chicken = new Food("Chicken", 12.0f);
		Entity* salmon = new Food("Salmon", 15.0f);
		Entity* cod = new Food("Cod", 17.0f);
		Entity* steak = new Food("Steak", 20.0f);

		// Alcohol
		Entity* cider = new Alcohol("Cider", 10.0f, 2.00f);
		Entity* ale = new Alcohol("Ale", 15.0f, 3.00f);
		Entity* mead = new Alcohol("Mead", 15.0f, 3.00f);
		Entity* wine = new Alcohol("Wine", 15.0f, 5.00f);
		Entity* rum = new Alcohol("Rum", 10.0f, 10.0f);
		Entity* whisky = new Alcohol("Whisky", 10.0f, 10.0f);
		Entity* vodka = new Alcohol("Vodka", 10.0f, 10.0f);
		Entity* burbon = new Alcohol("Bourbon", 2.0f, 20.0f);

		// Equipment
		Entity* sword = new Equipment("Sword", 10.0f, 0.0f, Item::Type::Hand);
		Entity* helmet = new Equipment("Helmet", 0.00f, 5.0f, Item::Type::Head);
		Entity* steelBoots = new Equipment("Steel boots", 0.00f, 2.0f, Item::Type::Feet);
		Entity* chainmail = new Equipment("Chain mail", 0.00f, 10.0f, Item::Type::Torso);

		// Other
		Entity* key = new Item("Key", Item::Type::Key);
		Entity* torch = new LightSource("Torch", 15.0f);

		// Stairs
		Entity* stairsUp = new Stairs("Stairs up", 'U', true);
		Entity* stairsDown = new Stairs("Stairs down", 'D', false);

		// Enemies
		Entity* rat = new Enemy("Rat", 2.00f, 1.0f, 10.0f);
		Entity* giantRat = new Enemy("Giant rat", 5.00f, 2.0f, 30.0f);
		Entity* troll = new Enemy("Troll", 8.00f, 4.0f, 50.0f);
		Entity* witch = new Enemy("Witch", 4.0f, 2.0f, 100.0f);
		Entity* orc = new Enemy("Orc", 12.0f, 5.0f, 50.0f);

		// NPCs
		Entity* shopKeeper = new ShopKeeper("Shop Keeper");

		void EntityTemplate::Init() {

			allSources.push_back(entitySource(0.0f, SpawnSource(berries,	2.00f)));
			allSources.push_back(entitySource(0.0f, SpawnSource(mushrooms,	2.00f)));
			allSources.push_back(entitySource(0.0f, SpawnSource(cheese,		1.60f)));
			allSources.push_back(entitySource(0.0f, SpawnSource(bread,		1.50f)));
			allSources.push_back(entitySource(0.0f, SpawnSource(chicken,	1.20f)));
			allSources.push_back(entitySource(0.0f, SpawnSource(salmon,		1.00f)));
			allSources.push_back(entitySource(0.0f, SpawnSource(cod,		0.50f)));
			allSources.push_back(entitySource(0.0f, SpawnSource(steak,		0.50f)));
																
			allSources.push_back(entitySource(0.0f, SpawnSource(cider,		0.70f)));
			allSources.push_back(entitySource(0.0f, SpawnSource(ale,		0.70f)));
			allSources.push_back(entitySource(0.0f, SpawnSource(mead,		0.60f)));
			allSources.push_back(entitySource(0.0f, SpawnSource(wine,		0.40f)));
			allSources.push_back(entitySource(0.0f, SpawnSource(rum,		0.40f)));
			allSources.push_back(entitySource(0.0f, SpawnSource(vodka,		0.30f)));
			allSources.push_back(entitySource(0.0f, SpawnSource(whisky,		0.30f)));
			allSources.push_back(entitySource(0.0f, SpawnSource(burbon,		0.10f)));
																		
			allSources.push_back(entitySource(0.0f, SpawnSource(sword,		0.05f)));
			allSources.push_back(entitySource(0.0f, SpawnSource(helmet,		0.05f)));
			allSources.push_back(entitySource(0.0f, SpawnSource(steelBoots,	0.05f)));
			allSources.push_back(entitySource(0.0f, SpawnSource(chainmail,	0.05f)));
			
			allSources.push_back(entitySource(0.0f, SpawnSource(rat,		3.00f)));
			allSources.push_back(entitySource(0.0f, SpawnSource(giantRat,	1.20f)));
			allSources.push_back(entitySource(0.0f, SpawnSource(orc,		0.20f)));
			allSources.push_back(entitySource(0.0f, SpawnSource(troll,		0.20f)));
			allSources.push_back(entitySource(0.0f, SpawnSource(witch,		0.20f)));
			allSources.push_back(entitySource(0.0f, SpawnSource(shopKeeper,	0.05f)));

			allSources.push_back(entitySource(0.0f, SpawnSource(key,		-1.0f)));
			allSources.push_back(entitySource(0.0f, SpawnSource(stairsUp,	-1.0f)));
			allSources.push_back(entitySource(0.0f, SpawnSource(stairsDown, -1.0f)));


		}

		void EntityTemplate::UpdateSpawnChances(const int& levelNumber) {

			float curve = (levelNumber / 20.0f);
			float constant = 0.25f;

			float currentSpawnChance = 0.0f;


			for (int i = 0; i < allSources.size(); i++) {

				float thisSpawnChance = allSources.at(i).second.getSpawnChance();
				if (thisSpawnChance < 0.0f)
					continue;

				float lastSpawnChance = 0.0f;

				if (i != 0)
					lastSpawnChance = allSources.at(i - 1).second.getSpawnChance();

				currentSpawnChance += (thisSpawnChance + curve) * constant;

				allSources.at(i).first = currentSpawnChance + lastSpawnChance;
			}
						

		}

		Entity* EntityTemplate::TryGetEntity(const float& randomNumber) {

			for (auto& spawnSource : allSources) {
				if (randomNumber < spawnSource.first) {
					return spawnSource.second.GetEntity();
				}
			}

			return nullptr;
		}

		Entity* EntityTemplate::Find(const std::string& name) {

			for (auto& spawnSource : allSources) {
				if (CompareStrings(spawnSource.second.getName(), name, false)) {
					return spawnSource.second.GetEntity();
				}
			}
			
			Log::AddMessage("Could not find '" + name + "' in entity templates", Message::Type::Warning);

			return nullptr;
		}

		void EntityTemplate::SortSources() {





		}

	}
}