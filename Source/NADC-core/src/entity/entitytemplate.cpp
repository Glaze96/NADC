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

		/* Collections */
		std::map<std::string, SpawnSource> EntityTemplate::itemS;
		std::map<std::string, SpawnSource> EntityTemplate::enemyS;
		std::map<std::string, SpawnSource> EntityTemplate::specialItemS;

		/* Factory items */
		// Food													//hp
		Entity* item_berries =		new Food("Berries",		2.0f);
		Entity* item_mushrooms =	new Food("Mushrooms",	2.5f);
		Entity* item_cheese =		new Food("Cheese",		8.00f);
		Entity* item_bread =		new Food("Bread",		10.0f);
		Entity* item_chicken =		new Food("Chicken",		12.0f);
		Entity* item_fish =			new Food("Fish",		15.0f);
		Entity* item_steak =		new Food("Steak",		20.0f);


		//TODO: add variations of fish!

		// Alcohol													//hp   //abv
		Entity* item_cider = new Alcohol("Cider", 10.0f, 2.00f);
		Entity* item_ale = new Alcohol("Ale", 15.0f, 3.00f);
		Entity* item_mead = new Alcohol("Mead", 15.0f, 3.00f);
		Entity* item_wine = new Alcohol("Wine", 15.0f, 5.00f);
		Entity* item_rum = new Alcohol("Rum", 10.0f, 10.0f);
		Entity* item_whisky = new Alcohol("Whisky", 10.0f, 10.0f);
		Entity* item_vodka = new Alcohol("Vodka", 10.0f, 10.0f);
		Entity* item_burbon = new Alcohol("Burbon", -2.0f, 20.0f);

		// Equipment														//d	   //a
		Entity* item_sword = new Equipment("Sword", 10.0f, 0.0f, ItemType::Hand);
		Entity* item_helmet = new Equipment("Helmet", 0.00f, 5.0f, ItemType::Head);
		Entity* item_steelBoots = new Equipment("Steel boots", 0.00f, 2.0f, ItemType::Feet);
		Entity* item_chainmail = new Equipment("Chain mail", 0.00f, 10.0f, ItemType::Torso);

		// Other
		Entity* item_key = new Item("Key", ItemType::Key);
		Entity* item_torch = new LightSource("Torch", 15.0f);

		// Stairs
		Entity* stairs_up = new Stairs("Stairs up", 'U', true);
		Entity* stairs_down = new Stairs("Stairs down", 'D', false);

		// Enemies													//d	   //a	 //hp
		Entity* enemy_rat = new Enemy("Rat", 2.00f, 1.0f, 10.0f);
		Entity* enemy_giantRat = new Enemy("Giant rat", 5.00f, 2.0f, 30.0f);
		Entity* enemy_troll = new Enemy("Troll", 8.00f, 4.0f, 50.0f);
		Entity* enemy_orc = new Enemy("Orc", 12.0f, 5.0f, 50.0f);



		Entity* shopKeeper = new ShopKeeper("Shop Keeper");

		void EntityTemplate::UpdateSpawnChances(const int& levelNumber) {

			float curve = (levelNumber / 20.0f) + 1.0f;
			float chance = 0.0f;

			try {
				chance =  curve * 3.0f;		itemS.at("Cheese").setSpawnChance(chance);
				chance += curve * 3.0f;		itemS.at("Bread").setSpawnChance(chance);
				chance += curve * 1.2f;		itemS.at("Chicken").setSpawnChance(chance);
				chance += curve * 2.0f;		itemS.at("Fish").setSpawnChance(chance);
				chance += curve * 1.5f;		itemS.at("Steak").setSpawnChance(chance);
				chance += curve * 1.5f;		itemS.at("Berries").setSpawnChance(chance);
				chance += curve * 1.5f;		itemS.at("Mushroom").setSpawnChance(chance);
														  
				chance += curve * 2.0f;		itemS.at("Cider").setSpawnChance(chance);
				chance += curve * 2.0f;		itemS.at("Ale").setSpawnChance(chance);
				chance += curve * 1.8f;		itemS.at("Mead").setSpawnChance(chance);
				chance += curve * 1.5f;		itemS.at("Wine").setSpawnChance(chance);
				chance += curve * 1.0f;		itemS.at("Rum").setSpawnChance(chance);
				chance += curve * 1.0f;		itemS.at("Vodka").setSpawnChance(chance);
				chance += curve * 1.0f;		itemS.at("Whisky").setSpawnChance(chance);
				chance += curve * 0.3f;		itemS.at("Burbon").setSpawnChance(chance);
														  
				chance += curve * 0.5f;		itemS.at("Helmet").setSpawnChance(chance);
				chance += curve * 0.5f;		itemS.at("SteelBoots").setSpawnChance(chance);
				chance += curve * 0.3f;		itemS.at("Sword").setSpawnChance(chance);
				chance += curve * 0.1f;		itemS.at("ChainMail").setSpawnChance(chance);
			  
				chance = 0.0f;
				chance += curve * 5.0f;		enemyS.at("Rat").setSpawnChance(chance);
				chance += curve * 3.5f;		enemyS.at("GiantRat").setSpawnChance(chance); 
				chance += curve * 2.0f;		enemyS.at("Orc").setSpawnChance(chance); 
				chance += curve * 1.0f;		enemyS.at("Troll").setSpawnChance(chance);

			}
			catch (...) {
				Log::AddMessage("Tried to update spawnchance of nonexcistent entity!", Message::Type::Error);
			}

		}

		void EntityTemplate::Init() {

			itemS.insert(entitySource("Cheese", SpawnSource(item_cheese)));
			itemS.insert(entitySource("Fish", SpawnSource(item_fish)));
			itemS.insert(entitySource("Bread", SpawnSource(item_bread)));
			itemS.insert(entitySource("Steak", SpawnSource(item_steak)));
			itemS.insert(entitySource("Chicken", SpawnSource(item_chicken)));

			itemS.insert(entitySource("Cider", SpawnSource(item_cider)));
			itemS.insert(entitySource("Ale", SpawnSource(item_ale)));
			itemS.insert(entitySource("Mead", SpawnSource(item_mead)));
			itemS.insert(entitySource("Rum", SpawnSource(item_rum)));
			itemS.insert(entitySource("Vodka", SpawnSource(item_vodka)));
			itemS.insert(entitySource("Whisky", SpawnSource(item_whisky)));
			itemS.insert(entitySource("Wine", SpawnSource(item_wine)));
			itemS.insert(entitySource("Burbon", SpawnSource(item_burbon)));

			itemS.insert(entitySource("Helmet", SpawnSource(item_helmet)));
			itemS.insert(entitySource("SteelBoots", SpawnSource(item_steelBoots)));
			itemS.insert(entitySource("Sword", SpawnSource(item_sword)));
			itemS.insert(entitySource("ChainMail", SpawnSource(item_chainmail)));

			specialItemS.insert(entitySource("Key", SpawnSource(item_key)));
			specialItemS.insert(entitySource("StairsUp", SpawnSource(stairs_up)));
			specialItemS.insert(entitySource("StairsDown", SpawnSource(stairs_down)));

			enemyS.insert(entitySource("Rat", SpawnSource(enemy_rat)));
			enemyS.insert(entitySource("GiantRat", SpawnSource(enemy_giantRat)));
			enemyS.insert(entitySource("Orc", SpawnSource(enemy_orc)));
			enemyS.insert(entitySource("Troll", SpawnSource(enemy_troll)));


			enemyS.insert(entitySource("ShopKeeper", SpawnSource(shopKeeper)));

		}

		Entity* EntityTemplate::TryGetItem(const int& randomNumber) {
			for (auto& spawnSource : itemS) {
				if (randomNumber < spawnSource.second.getSpawnChance()) {
					return spawnSource.second.GetEntity();
				}
			}
			return nullptr;
		}

		Entity* EntityTemplate::TryGetEnemy(const int& randomNumber) {

			for (auto& spawnSource : enemyS) {
				if (randomNumber < spawnSource.second.getSpawnChance()) {
					return spawnSource.second.GetEntity();
				}
			}
			return nullptr;
		}

		Entity* EntityTemplate::Find(const std::string& name) {

			for (auto& spawnSource : itemS) {
				if (CompareStrings(spawnSource.first, name, false)) {
					return spawnSource.second.GetEntity();
				}
			}

			for (auto& spawnSource : enemyS) {
				if (CompareStrings(spawnSource.first, name, false)) {
					return spawnSource.second.GetEntity();
				}
			}

			for (auto& spawnSource : specialItemS) {
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