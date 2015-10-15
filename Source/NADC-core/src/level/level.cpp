#include "level.h"

// Glibrary includes
#include <Glibrary/console/log.h>
#include <Glibrary/console/io.h>

// Gengine includes
#include "../entity/items/equipment.h"
#include "levelgenerator.h"
#include "levelmanager.h"
#include <assert.h>

namespace glaze {
	using namespace glibrary;
	namespace gengine {

		Level::Level(const Vector2i& size, const bool& allVisible) {
			_levelNumber = LevelManager::getNumLevels();
			_size = size;

			LevelGenerator::GenerateLevel(this, 1000);

			if (allVisible)
				SetAllVisible();
		}

		void Level::Fill(const Tile& tile) {
			for (int x = 0; x < _size.x; x++)
				_tiles.push_back(std::vector<Tile>(_size.y, tile));
		}

		void Level::SetTile(const Vector2i& position, const Tile& tile) {
			SetTile(position.x, position.y, tile);
		}

		void Level::SetTile(const unsigned int& x, const unsigned int& y, const Tile& tile) {

			try {
				_tiles.at(x).at(y) = tile;
			}
			catch (...) {
				Log::AddMessage("Tried to set tile out of bounds!", Message::Type::Error);
			}

		}

		void Level::SetTileVisible(const Vector2i& position) {
			SetTileVisible(position.x, position.y);
		}

		void Level::SetTileVisible(const int& x, const int& y) {
			_tiles.at(x).at(y).setVisible(true);
		}

		const Tile& Level::GetTile(const Vector2i& position) const {
			return GetTile(position.x, position.y);
		}

		const Tile& Level::GetTile(const unsigned int& x, const unsigned int& y) const {

			try {
				return _tiles.at(x).at(y);
			}
			catch (...) {
				Log::AddMessage("Tried to get tile out of bounds!", Message::Type::Error);
			}
			return Tile('£', Tile::Type::Wall);
		}

		std::vector<Vector2i> Level::GetTiles(const Tile::Type& tileType) const {

			std::vector<Vector2i> tiles;

			for (int y = 0; y < _size.y; y++) {
				for (int x = 0; x < _size.x; x++) {

					if (_tiles.at(x).at(y).getType() == tileType) {
						tiles.push_back(Vector2i(x, y));
					}

				}
			}

			return tiles;
		}

		Entity* Level::GetStairsDown() const {

			for (Entity* entity : _entities) {
				if (entity->getName() == "Stairs down") {
					return entity;
				}
			}

			return nullptr;
		}

		Entity* Level::GetStairsUp() const {
			for (Entity* entity : _entities) {
				if (entity->getName() == "Stairs up") {
					return entity;
				}
			}
			return nullptr;
		}


		void Level::SetAllVisible() {
			for (int y = 0; y < _size.y; y++) {
				for (int x = 0; x < _size.x; x++) {
					SetTileVisible(x, y);
				}
			}

			for (auto* entity : _entities) {
				entity->setVisible(true);
			}

		}

		std::vector<Entity*> Level::GetEntitiesAtPosition(const Vector2i& position) const {

			std::vector<Entity*> e;

			for (auto* entity : _entities) {
				if (entity->getPosition() == position) {
					e.push_back(entity);
				}

			}

			return e;
		}

		std::vector<Entity*> Level::GetEntitiesAtPosition(const int& x, const int& y) const {
			return GetEntitiesAtPosition(Vector2i(x, y));
		}

		bool Level::AddEntity(Entity* entity, const Vector2i& position, const bool& supressLog) {
			if (entity != nullptr) {
				if (!supressLog)
					Log::AddMessage("Added '" + entity->getName() + "' to level");
				entity->setLevel(this);
				entity->setPosition(position);
				entity->setInInventory(false);

				_eventHandler.Subscribe(entity, { Event::Type::PlayerMoved });

				_entities.push_back(entity);
				return true;
			}

			Log::AddMessage("Failed to add entity to level");
			return false;
		}

		void Level::DestroyEntity(Entity* entity) {

			for (unsigned int i = 0; i < _entities.size(); i++) {
				if (_entities.at(i)->getId() == entity->getId()) {
					_entities.erase(_entities.begin() + i);
					break;
				}
			}
			_eventHandler.UnSubscribe(entity);
			delete entity;
		}

		void Level::Draw() const {
			DrawLevel();
			for (auto* entity : _entities) entity->Draw();
		}

		void Level::DrawLevel() const {
			for (int y = 0; y < _size.y; y++) {
				for (int x = 0; x < _size.x; x++) {

					const Tile currentTile = GetTile(x, y);

					if (currentTile.getVisible()) {
						Out::PrintchAt(x, y, currentTile.getAppearence());
					}


				}
			}
		}

	} // End namespace gengine
} // End namespace glaze