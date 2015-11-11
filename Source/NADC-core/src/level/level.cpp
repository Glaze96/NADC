#include "level.h"

// Glibrary includes
#include <Glibrary/console/log.h>
#include <Glibrary/console/io.h>

// Gengine includes
#include "levelgenerator.h"
#include "levelmanager.h"
#include "../entity/creature/enemy.h"
#include "../entity/items/item.h"

namespace glaze {
	using namespace glibrary;
	namespace gengine {

		Level::Level(const Vector2i& size)
		: _size(size), _levelNumber(LevelManager::getNumLevels()) {

			LevelGenerator::GenerateLevel(this, 1000);

			UpdateCollections();

		}

		void Level::Fill(const Tile& tile) {
			for (int x = 0; x < _size.x; x++)
				_tiles.push_back(std::vector<Tile>(_size.y, tile));
		}

		unsigned int Level::GetNumEntitiesAtPosition(const Vector2i& position) const {
			return GetNumEntitiesAtPosition(position.x, position.y);
		}

		unsigned int Level::GetNumEntitiesAtPosition(const int& x, const int& y) const {
			return GetEntitiesAtPosition(x, y).size();
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
			try {
			_tiles.at(x).at(y).setVisible(true);
			}
			catch (...) {
				Log::AddMessage("Tried to set tile visible out of bounds", Message::Type::Warning);
			}
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
			return _tiles.at(0).at(0);
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

				UpdateCollections();
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
			UpdateCollections();
		}

		void Level::Draw() const {
			DrawLevel();

			Color::SetBold();

			Color::SetColor(Color::YELLOW);
			for (const auto* item : _items) {
				item->Draw();
			}
			Color::ResetColor();

			Color::SetColor(Color::RED);
			for (const auto* enemy: _enemies) {
				enemy->Draw();
			}
			Color::ResetColor();

			for (const auto* other : _other) {
				other->Draw();
			}

			Color::ResetBold();

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

		void Level::UpdateCollections() {

			_enemies.clear();
			_items.clear();
			_other.clear();

			for (auto* entity : _entities) {

				if (dynamic_cast<Item*>(entity) != NULL) {
					_items.push_back((Item*)entity);
				}
				else if (dynamic_cast<Enemy*>(entity) != NULL) {
					_enemies.push_back((Enemy*)entity);
				}
				else {
					_other.push_back(entity);
				}

			}

		}

	} // End namespace gengine
} // End namespace glaze