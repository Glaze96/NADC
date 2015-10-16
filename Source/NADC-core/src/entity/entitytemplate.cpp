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

		typedef std::pair<std::string, SpawnSource> entitySource;

		std::map<std::string, SpawnSource> EntityTemplate::itemSources;
		std::map<std::string, SpawnSource> EntityTemplate::enemySources;
		std::map<std::string, SpawnSource> EntityTemplate::specialItemSources;

		// Food
		Entity* berries =		new Food("Berries",		2.0f);
		Entity* mushrooms =		new Food("Mushrooms",	2.5f);
		Entity* cheese =		new Food("Cheese",		8.00f);
		Entity* bread =			new Food("Bread",		10.0f);
		Entity* chicken =		new Food("Chicken",		12.0f);
		Entity* salmon =		new Food("Salmon",		15.0f);
		Entity* cod =			new Food("Cod",			17.0f);
		Entity* steak =			new Food("Steak",		20.0f);

		//TODO: add variations of fish!

		// Alcohol
		Entity* cider =		new Alcohol("Cider", 10.0f, 2.00f);
		Entity* ale =		new Alcohol("Ale", 15.0f, 3.00f);
		Entity* mead =		new Alcohol("Mead", 15.0f, 3.00f);
		Entity* wine =		new Alcohol("Wine", 15.0f, 5.00f);
		Entity* rum =		new Alcohol("Rum", 10.0f, 10.0f);
		Entity* whisky =	new Alcohol("Whisky", 10.0f, 10.0f);
		Entity* vodka =		new Alcohol("Vodka", 10.0f, 10.0f);
		Entity* burbon =	new Alcohol("Bourbon", 2.0f, 20.0f);

		// Equipment
		Entity* sword =			new Equipment("Sword", 10.0f, 0.0f, Item::Type::Hand);
		Entity* helmet =		new Equipment("Helmet", 0.00f, 5.0f, Item::Type::Head);
		Entity* steelBoots =	new Equipment("Steel boots", 0.00f, 2.0f, Item::Type::Feet);
		Entity* chainmail =		new Equipment("Chain mail", 0.00f, 10.0f, Item::Type::Torso);

		// Other
		Entity* key =	new Item("Key", Item::Type::Key);
		Entity* torch = new LightSource("Torch", 15.0f);

		// Stairs
		Entity* stairsUp =		new Stairs("Stairs up", 'U', true);
		Entity* stairsDown =	new Stairs("Stairs down", 'D', false);

		// Enemies
		Entity* rat =		new Enemy("Rat", 2.00f, 1.0f, 10.0f);
		Entity* giantRat =	new Enemy("Giant rat", 5.00f, 2.0f, 30.0f);
		Entity* troll =		new Enemy("Troll", 8.00f, 4.0f, 50.0f);
		Entity* witch =		new Enemy("Witch", 4.0f, 2.0f, 100.0f);
		Entity* orc =		new Enemy("Orc", 12.0f, 5.0f, 50.0f);

		// NPCs
		Entity* shopKeeper = new ShopKeeper("Shop Keeper");

		void EntityTemplate::Init() {


			itemSources.insert(entitySource("Berries",				SpawnSource(berries)));
			itemSources.insert(entitySource("Mushrooms",			SpawnSource(mushrooms)));
			itemSources.insert(entitySource("Cheese",				SpawnSource(cheese)));
			itemSources.insert(entitySource("Bread",				SpawnSource(bread)));
			itemSources.insert(entitySource("Chicken",				SpawnSource(chicken)));
			itemSources.insert(entitySource("Salmon",				SpawnSource(salmon)));
			itemSources.insert(entitySource("Cod",					SpawnSource(cod)));
			itemSources.insert(entitySource("Steak",				SpawnSource(steak)));

			itemSources.insert(entitySource("Cider",				SpawnSource(cider)));
			itemSources.insert(entitySource("Ale",					SpawnSource(ale)));
			itemSources.insert(entitySource("Mead",					SpawnSource(mead)));
			itemSources.insert(entitySource("Rum",					SpawnSource(rum)));
			itemSources.insert(entitySource("Vodka",				SpawnSource(vodka)));
			itemSources.insert(entitySource("Whisky",				SpawnSource(whisky)));
			itemSources.insert(entitySource("Wine",					SpawnSource(wine)));
			itemSources.insert(entitySource("Bourbon",				SpawnSource(burbon)));

			itemSources.insert(entitySource("Helmet",				SpawnSource(helmet)));
			itemSources.insert(entitySource("SteelBoots",			SpawnSource(steelBoots)));
			itemSources.insert(entitySource("Sword",				SpawnSource(sword)));
			itemSources.insert(entitySource("ChainMail",			SpawnSource(chainmail)));

			specialItemSources.insert(entitySource("Key",			SpawnSource(key)));
			specialItemSources.insert(entitySource("StairsUp",		SpawnSource(stairsUp)));
			specialItemSources.insert(entitySource("StairsDown",	SpawnSource(stairsDown)));

			enemySources.insert(entitySource("Rat",					SpawnSource(rat)));
			enemySources.insert(entitySource("GiantRat",			SpawnSource(giantRat)));
			enemySources.insert(entitySource("Orc",					SpawnSource(orc)));
			enemySources.insert(entitySource("Troll",				SpawnSource(troll)));
			enemySources.insert(entitySource("Witch",				SpawnSource(witch)));


			enemySources.insert(entitySource("ShopKeeper",			SpawnSource(shopKeeper)));

		}

		void EntityTemplate::UpdateSpawnChances(const int& levelNumber) {

			std::vector<float> chances = { };

			float curve = (levelNumber / 20.0f) + 1.0f;
			float chance = 0.0f;
			unsigned int i = -1;

			try {
				i++; chance += curve * 3.0f;		itemSources.at("Berries").setSpawnChance(chance);	
				i++; chance += curve * 2.0f;		itemSources.at("Mushrooms").setSpawnChance(chance);	
				i++; chance += curve * 1.2f;		itemSources.at("Cheese").setSpawnChance(chance);
				i++; chance += curve * 1.2f;		itemSources.at("Bread").setSpawnChance(chance);		
				i++; chance += curve * 1.0f;		itemSources.at("Chicken").setSpawnChance(chance);	
				i++; chance += curve * 1.0f;		itemSources.at("Salmon").setSpawnChance(chance);	
				i++; chance += curve * 1.0f;		itemSources.at("Cod").setSpawnChance(chance);		
				i++; chance += curve * 0.6f;		itemSources.at("Steak").setSpawnChance(chance);		

				i++; chance += curve * 2.0f;		itemSources.at("Cider").setSpawnChance(chance);		
				i++; chance += curve * 2.0f;		itemSources.at("Ale").setSpawnChance(chance);		
				i++; chance += curve * 1.8f;		itemSources.at("Mead").setSpawnChance(chance);		
				i++; chance += curve * 1.5f;		itemSources.at("Wine").setSpawnChance(chance);		
				i++; chance += curve * 1.0f;		itemSources.at("Rum").setSpawnChance(chance);		
				i++; chance += curve * 1.0f;		itemSources.at("Vodka").setSpawnChance(chance);		
				i++; chance += curve * 1.0f;		itemSources.at("Whisky").setSpawnChance(chance);	
				i++; chance += curve * 0.3f;		itemSources.at("Bourbon").setSpawnChance(chance);	

				i++; chance += curve * 0.5f;		itemSources.at("Helmet").setSpawnChance(chance);	
				i++; chance += curve * 0.5f;		itemSources.at("SteelBoots").setSpawnChance(chance);
				i++; chance += curve * 0.3f;		itemSources.at("Sword").setSpawnChance(chance);		
				i++; chance += curve * 0.1f;		itemSources.at("ChainMail").setSpawnChance(chance);	

				if (i < itemSources.size() - 1)
					Log::AddMessage("Forgot to add spawnchance to all item templates!", Message::Type::Warning);

				i = -1;
				i++; chance = 0.0f;
				i++; chance += curve * 5.0f;		enemySources.at("Rat").setSpawnChance(chance);
				i++; chance += curve * 3.5f;		enemySources.at("GiantRat").setSpawnChance(chance);
				i++; chance += curve * 2.0f;		enemySources.at("Orc").setSpawnChance(chance);
				i++; chance += curve * 1.0f;		enemySources.at("Troll").setSpawnChance(chance);
				i++; chance += curve * 0.9f;		enemySources.at("Witch").setSpawnChance(chance);

				if (i < enemySources.size() - 1)
					Log::AddMessage("Forgot to add spawnchance to all enemy templates!", Message::Type::Warning);
			}
			catch (...) {
				Log::AddMessage("Tried to update spawn chance of nonexistent entity!", Message::Type::Error);
			}

		}

		Entity* EntityTemplate::TryGetItem(const int& randomNumber) {
			for (auto& spawnSource : itemSources) {
				if (spawnSource.second.getSpawnChance() > randomNumber) {
					return spawnSource.second.GetEntity();
				}
			}
			return nullptr;
		}

		Entity* EntityTemplate::TryGetEnemy(const int& randomNumber) {

			for (auto& spawnSource : enemySources) {
				if (randomNumber < spawnSource.second.getSpawnChance()) {
					return spawnSource.second.GetEntity();
				}
			}
			return nullptr;
		}

		Entity* EntityTemplate::Find(const std::string& name) {

			for (auto& spawnSource : itemSources) {
				if (CompareStrings(spawnSource.first, name, false)) {
					return spawnSource.second.GetEntity();
				}
			}

			for (auto& spawnSource : enemySources) {
				if (CompareStrings(spawnSource.first, name, false)) {
					return spawnSource.second.GetEntity();
				}
			}

			for (auto& spawnSource : specialItemSources) {
				if (CompareStrings(spawnSource.first, name, false)) {
					return spawnSource.second.GetEntity();
				}
			}

			Log::AddMessage("Could not find '" + name + "' in entity templates", Message::Type::Warning);

			return nullptr;
		}
	}
}


//// Alcohol
//Entity* SpawnFunctionCider() { return			new Alcohol("Cider", 10.0_hp, 2.0_abv); }
//Entity* SpawnFunctionAle() { return				new Alcohol("Ale", 15.0_hp, 3.0_abv); }
//Entity* SpawnFunctionMead() { return			new Alcohol("Mead", 15.0_hp, 3.0_abv); }
//Entity* SpawnFunctionWine() { return			new Alcohol("Wine", 15.0_hp, 5.0_abv); }
//Entity* SpawnFunctionRum() { return				new Alcohol("Rum", 10.0_hp, 10.0_abv); }
//Entity* SpawnFunctionWhisky() { return			new Alcohol("Whisky", 10.0_hp, 10.0_abv); }
//Entity* SpawnFunctionVodka() { return			new Alcohol("Vodka", 10.0_hp, 10.0_abv); }

//// Food
//Entity* SpawnFunctionBread() { return			new Food("Bread", 10.0_hp); }
//Entity* SpawnFunctionCheese() { return			new Food("Cheese", 8.0_hp); }
//Entity* SpawnFunctionFish() { return			new Food("Fish", 15.0_hp); }
//Entity* SpawnFunctionSteak() { return			new Food("Steak", 20.0_hp); }

//// Equipment
//Entity* SpawnFunctionSword() { return			new Equipment("Sword", 10.0_d, 0.0_a, ItemType::Hand); }
//Entity* SpawnFunctionHelmet() { return			new Equipment("Helmet", 0.0_d, 5.0_a, ItemType::Head); }
//Entity* SpawnFunctionSteelBoots() { return		new Equipment("Steel boots", 0.0_d, 2.0_a, ItemType::Feet); }

//// Enemies
//Entity* SpawnFunctionRat() { return				new Enemy("Rat", 2.0_d, 1.0_a, 10.0_hp); }
//Entity* SpawnFunctionGiantRat() { return		new Enemy("Giant rat", 5.0_d, 2.0_a, 30.0_hp); }
//Entity* SpawnFunctionTroll() { return			new Enemy("Troll", 8.0_d, 4.0_a, 50.0_hp); }
//Entity* SpawnFunctionOrc() { return				new Enemy("Orc", 12.0_d, 5.0_a, 50.0_hp); }

//// Stairs
//Entity* SpawnFunctionStairsUp() { return		new Stairs("Stairs up", 'U', true); }
//Entity* SpawnFunctionStairsDown() { return		new Stairs("Stairs down", 'D', false); }

//// Other
//Entity* SpawnFunctionKey() { return				new Item("Key", ItemType::Key); }
//Entity* SpawnFunctionTorch() { return			new LightSource("Torch", 15.0f); }

//std::vector<SpawnSource*> EntityTemplate::consumableSpawnSources = {
//	// Alcohol
//	new SpawnSource(0.0020f,	SpawnFunctionCider),
//	new SpawnSource(0.0020f,	SpawnFunctionAle),
//	new SpawnSource(0.0015f,	SpawnFunctionMead),
//	new SpawnSource(0.0010f,	SpawnFunctionWine),
//	new SpawnSource(0.0005f,	SpawnFunctionRum),
//	new SpawnSource(0.0005f,	SpawnFunctionWhisky),
//	new SpawnSource(0.0005f,	SpawnFunctionVodka),
//					  
//	// Food			  
//	new SpawnSource(0.0020f,	SpawnFunctionBread),
//	new SpawnSource(0.0020f,	SpawnFunctionCheese),
//	new SpawnSource(0.0015f,	SpawnFunctionFish),
//	new SpawnSource(0.0010f,	SpawnFunctionSteak)
//};


//std::vector<SpawnSource*> EntityTemplate::equipmentSpawnSources = {
//	// Equipment
//	new SpawnSource(0.0005f,	SpawnFunctionSword),
//	new SpawnSource(0.0007f,	SpawnFunctionHelmet),
//	new SpawnSource(0.0009f,	SpawnFunctionSteelBoots)
//};


//std::vector<SpawnSource*> EntityTemplate::enemySpawnSources = {
//	// Enemies
//	new SpawnSource(0.0020f,	SpawnFunctionRat),
//	new SpawnSource(0.0010f,	SpawnFunctionGiantRat),
//	new SpawnSource(0.0005f,	SpawnFunctionTroll),
//	new SpawnSource(0.0002f,	SpawnFunctionOrc),
//};

//int i = -1;
//// Alcohol
//itemSpawnSources.push_back(new SpawnSource((curve * 5.0f), SpawnFunctionCider));
//i++;
//itemSpawnSources.push_back(new SpawnSource(itemSpawnSources[i]->_spawnChance + (curve * 5.0f), SpawnFunctionMead));
//i++;
//itemSpawnSources.push_back(new SpawnSource(itemSpawnSources[i]->_spawnChance + (curve * 3.0f), SpawnFunctionWine));
//i++;
//itemSpawnSources.push_back(new SpawnSource(itemSpawnSources[i]->_spawnChance + (curve * 2.0f), SpawnFunctionRum));
//i++;
//itemSpawnSources.push_back(new SpawnSource(itemSpawnSources[i]->_spawnChance + (curve * 1.0f), SpawnFunctionWhisky));
//i++;
//itemSpawnSources.push_back(new SpawnSource(itemSpawnSources[i]->_spawnChance + (curve * 1.0f), SpawnFunctionVodka));
//i++;
//
//// Food
//itemSpawnSources.push_back(new SpawnSource(itemSpawnSources[i]->_spawnChance + (curve * 4.0f), SpawnFunctionBread));
//i++;
//itemSpawnSources.push_back(new SpawnSource(itemSpawnSources[i]->_spawnChance + (curve * 5.0f), SpawnFunctionCheese));
//i++;
//itemSpawnSources.push_back(new SpawnSource(itemSpawnSources[i]->_spawnChance + (curve * 4.0f), SpawnFunctionFish));
//i++;
//itemSpawnSources.push_back(new SpawnSource(itemSpawnSources[i]->_spawnChance + (curve * 3.0f), SpawnFunctionSteak));
//i++;
//
//// Equipment
//itemSpawnSources.push_back(new SpawnSource(itemSpawnSources[i]->_spawnChance + (curve * 0.5f), SpawnFunctionSword));
//i++;
//itemSpawnSources.push_back(new SpawnSource(itemSpawnSources[i]->_spawnChance + (curve * 0.9f), SpawnFunctionHelmet));
//i++;
//itemSpawnSources.push_back(new SpawnSource(itemSpawnSources[i]->_spawnChance + (curve * 1.0f), SpawnFunctionSteelBoots));
//i++;
//
//// Other
//itemSpawnSources.push_back(new SpawnSource(itemSpawnSources[i]->_spawnChance + (curve * 1.0f), SpawnFunctionTorch));
//i++;
//
//i = -1;
//// Enemies
//enemySpawnSources.push_back(new SpawnSource((curve * 2.0f), SpawnFunctionGiantRat));
//i++;
//enemySpawnSources.push_back(new SpawnSource(enemySpawnSources[i]->_spawnChance + (curve * 1.0f), SpawnFunctionTroll));
//i++;
//enemySpawnSources.push_back(new SpawnSource(enemySpawnSources[i]->_spawnChance + (curve * 0.9f), SpawnFunctionOrc));
//i++;