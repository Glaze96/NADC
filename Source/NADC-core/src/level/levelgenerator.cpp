#include "levelgenerator.h"

// System includes
#include <vector>
#include <time.h>

// Glibrary includes
#include <Glibrary/maths/geometry.h>

// Gengine includes
#include "room.h"
#include "tile.h"
#include "../entity/creature/shopkeeper.h"
#include "../entity/level/stairs.h"
#include "../entity/entitytemplate.h"

namespace glaze {
	using namespace glibrary;
	namespace gengine {

		Level* LevelGenerator::_level;

		Vector2i LevelGenerator::_levelSize;

		Boxi LevelGenerator::_roomMask;

		std::vector<Room>* LevelGenerator::_rooms;

		float LevelGenerator::_windingPrecent = 20;

		void LevelGenerator::GenerateLevel(Level* level, const int& numberOfRooms) {

			srand((unsigned int)time(nullptr) + rand());

			_level = level;

			_level->Fill(Tile('#', Tile::Type::Wall));

			_levelSize = _level->getSize();

			EntityTemplate::UpdateSpawnChances(_level->getLevelNumber());

			Vector2i size = Vector2i((int)(41 + _level->getLevelNumber() * 1.2f));

			// Make uneven
			if (size.x % 2 == 0)
				size += 1;

			// Cap size to 99, TODO: Fix hard code
			if (size.x > 99)
				size = Vector2i(99);

			_roomMask = Boxi(size);
			_roomMask.Center(_levelSize / 2);



			_rooms = new std::vector<Room>;
			AddRandomRooms(numberOfRooms, 12, 6);
			PushRoomsToLevel();

			for (int y = _roomMask.getTop(); y < _roomMask.getBottom(); y += 2) {
				for (int x = _roomMask.getLeft(); x < _roomMask.getRight(); x += 2) {
					if (level->GetTile(x, y).getType() != Tile::Type::Floor) {
						continue;
					}
					AddPassages(Vector2i(x, y));
				}
			}

			MakeDoors();

			DeleteDeadEnds();

			SpawnEntities();
			SpawnStairs();

			delete _rooms;
		}

		void LevelGenerator::SetBorders(const Boxi& box, const Tile& tile) {

			for (int y = box.getTop(); y < box.getBottom(); y++) {
				_level->SetTile(box.getLeft(), y, tile); // Fill left side
			}
			for (int y = box.getTop(); y < box.getBottom(); y++) {
				_level->SetTile(box.getRight() - 1, y, tile); // Fill right side
			}
			for (int x = box.getLeft(); x < box.getRight(); x++) {
				_level->SetTile(x, box.getTop(), tile); // Fill top side
			}
			for (int x = box.getLeft(); x < box.getRight(); x++) {
				_level->SetTile(x, box.getBottom() - 1, tile); // Fill bottom side
			}
		}

		Vector2i fourway[4] = { Vector2i(0, -1), Vector2i(1, 0), Vector2i(0, 1), Vector2i(-1, 0) };
		Vector2i eightway[8] = { Vector2i(0, -1), Vector2i(1, 0), Vector2i(0, 1), Vector2i(-1, 0), Vector2i(-1, -1), Vector2i(-1, 1), Vector2i(1, -1), Vector2i(1, 1) };

		void LevelGenerator::MakeDoors() {

			std::vector<Room*> roomsLeft;

			for (Room& room : *_rooms) {
				roomsLeft.push_back(&room);
			}

			while (roomsLeft.size() > 0) {

				Room* currentRoom(roomsLeft[roomsLeft.size() - 1]);

				int numDoors = 1;
				int currentNumDoors = 0;
				int numTries = 0;

				if (rand() % 100 < 20) {
					numDoors = 2;
				}

				while (numDoors > currentNumDoors) {

					if (numTries > 1000) {
						break;
					}

					switch (rand() % 4) {
					case 0: {
						int randomX = rand() % currentRoom->getSize().x + currentRoom->getPosition().x;
						int y = currentRoom->getPosition().y - 1;

						if (_level->GetTile(randomX, y - 1).getType() == Tile::Type::Floor) {
							_level->SetTile(randomX, y, Tile('.', Tile::Type::Floor));
							currentNumDoors++;
						}
						numTries++;
						break;
					}
					case 1: {
						int randomX = rand() % currentRoom->getSize().x + currentRoom->getPosition().x;
						int y = currentRoom->getPosition().y + currentRoom->getSize().y;

						if (_level->GetTile(randomX, y + 1).getType() == Tile::Type::Floor) {
							_level->SetTile(randomX, y, Tile('.', Tile::Type::Floor));
							currentNumDoors++;
						}
						numTries++;
						break;
					}
					case 2: {
						int randomY = rand() % currentRoom->getSize().y + currentRoom->getPosition().y;
						int x = currentRoom->getPosition().x - 1;

						if (_level->GetTile(x - 1, randomY).getType() == Tile::Type::Floor) {
							_level->SetTile(x, randomY, Tile('.', Tile::Type::Floor));
							currentNumDoors++;
						}
						numTries++;
						break;
					}
					case 3: {
						int randomY = rand() % currentRoom->getSize().y + currentRoom->getPosition().y;
						int x = currentRoom->getPosition().x + currentRoom->getSize().x;

						if (_level->GetTile(x + 1, randomY).getType() == Tile::Type::Floor) {
							_level->SetTile(x, randomY, Tile('.', Tile::Type::Floor));
							currentNumDoors++;
						}
						numTries++;
						break;
					}
					}

				}

				roomsLeft.pop_back();

			}

			roomsLeft.clear();
		}

		bool Overlap(const Room& a, const Room& b, const int& padding) {

			Vector2i aPosition = a.getPosition();
			Vector2i aSize = a.getSize();

			Vector2i bPosition = b.getPosition();
			Vector2i bSize = b.getSize();

			if (aPosition.x < bPosition.x + bSize.x + padding&&
				aPosition.x + aSize.x + padding > bPosition.x &&
				aPosition.y < bPosition.y + bSize.y + padding &&
				aSize.y + aPosition.y + padding> bPosition.y) {
				return true;
			}
			else {
				return false;
			}
		}


		bool LevelGenerator::CanCarve(const Vector2i& position, const Vector2i& direction) {

			Vector2i newPosition2 = position + (direction * 2);
			Vector2i newPosition3 = position + (direction * 3);


			if (newPosition3.x < _roomMask.Position.x ||
				newPosition3.x > _roomMask.Size.x + _roomMask.Position.x - 1 ||
				newPosition3.y < _roomMask.Position.y ||
				newPosition3.y > _roomMask.Size.y + _roomMask.Position.y - 1) {
				return false;
			}

			for (Vector2i dir : fourway)
				if (_level->GetTile(newPosition2 + dir).getType() == Tile::Type::Floor)
					return false;


			if (_level->GetTile(newPosition2).getType() != Tile::Type::Floor)
				return true;
			else
				return false;

		}

		void LevelGenerator::DeleteDeadEnds() {

			bool done = false;

			while (!done) {
				done = true;

				for (int y = 0; y < _roomMask.Size.y - 1; y++) {
					for (int x = 0; x < _roomMask.Size.x - 1; x++) {

						Vector2i position(_roomMask.Position.x + x, _roomMask.Position.y + y);

						if (_level->GetTile(position).getType() != Tile::Type::Floor) {
							continue;
						}

						int exits = 0;

						for (Vector2i direction : fourway) {
							if (_level->GetTile(position + direction).getType() == Tile::Type::Floor) {
								exits++;
							}
						}

						if (exits == 1) {
							_level->SetTile(position, Tile('#', Tile::Type::Wall));
							done = false;
						}
					}
				}
			}


		}



		void LevelGenerator::DeleteNonWalls() {

			for (int y = 0; y < _roomMask.Size.y; y++) {
				for (int x = 0; x < _roomMask.Size.x; x++) {

					if (_level->GetTile(_roomMask.Position.x + x, _roomMask.Position.y + y).getType() == Tile::Type::Del) {
						_level->SetTile(_roomMask.Position.x + x, _roomMask.Position.y + y, Tile(' ', Tile::Type::Wall));
					}


				}
			}
		}

		void LevelGenerator::AddPassages(const Vector2i& start) {

			std::vector<Vector2i> cells = { start };
			Vector2i lastDirection;

			_level->SetTile(cells[0], Tile('.', Tile::Type::Floor));

			while (cells.size() > 0) {

				Vector2i cell(cells[cells.size() - 1]);

				std::vector<Vector2i> unmadeCells;

				for (Vector2i& direction : fourway) {
					if (CanCarve(cell, direction)) {
						unmadeCells.push_back(direction);
					}
				}


				if (unmadeCells.size() > 0) {

					Vector2i direction;

					if (CanCarve(cell, lastDirection)) {

						if (rand() % 100 > _windingPrecent) {
							direction = lastDirection;
						}
					}
					else {
						direction = Vector2i(unmadeCells[rand() % unmadeCells.size()]);
					}

					_level->SetTile(cell + direction, Tile('.', Tile::Type::Floor));
					_level->SetTile(cell + (direction * 2), Tile('.', Tile::Type::Floor));

					cells.push_back(cell + (direction * 2));
					lastDirection = direction;
				}
				else {
					cells.pop_back();
					lastDirection = Vector2i(0, 0);
				}

			}

		}


		void LevelGenerator::AddRandomRooms(const int& numberOfRooms, const int& maxSize, const int& minSize) {

			for (int i = 0; i < numberOfRooms; i++) {

				int randomWidth = (rand() * 2) % maxSize + minSize + 1;
				int randomHeight = (rand() * 2) % maxSize + minSize + 1;

				int randomX = ((rand() * 2) % (((int)_roomMask.Size.x - 4) - randomWidth)) + _roomMask.Position.x + 2;
				int randomY = ((rand() * 2) % (((int)_roomMask.Size.y - 4) - randomHeight)) + _roomMask.Position.y + 2;

				Room room(Vector2i(randomX, randomY), Vector2i(randomWidth, randomHeight));

				bool overlap = false;

				for (Room& otherRoom : *_rooms) {
					if (&room != &otherRoom)
						if (Overlap(room, otherRoom, 2)) {
							overlap = true;
						}

				}

				if (!overlap)
					_rooms->push_back(room);
			}
		}

		void LevelGenerator::PushRoomsToLevel() {
			for (Room& room : *_rooms) {
				room.PushTilesToLevel(_level);
			}
		}

		void LevelGenerator::SpawnEntities() {

			for (Room& room : *_rooms) {

				for (int y = 0; y < room.getSize().y; y++) {
					for (int x = 0; x < room.getSize().x; x++) {

						Vector2i position = room.getPosition() + Vector2i(x, y);

						int random = rand() % 10000;

						Entity* item = EntityTemplate::TryGetItem(random);
						if (item != nullptr) {
							_level->AddEntity(item, position, true);
							continue;
						}

						Entity* enemy = EntityTemplate::TryGetEnemy(random);
						if (enemy != nullptr) {
							_level->AddEntity(enemy, position, true);
							continue;
						}
					}
				}

			}

		}

		void LevelGenerator::SpawnStairs() {
			_level->AddEntity(EntityTemplate::Find("StairsDown"), GetTileInRandomRoom(), true);
			_level->AddEntity(EntityTemplate::Find("StairsUp"), GetTileInRandomRoom(), true);
		}

		Vector2i LevelGenerator::GetWalkableTile(const Boxi& box) {

			while (true) {
				Vector2i randomPosition((rand() % box.Size.x) + box.Position.x, (rand() % box.Size.y) + box.Position.y);

				if (_level->GetTile(randomPosition).getType() == Tile::Type::Floor) {
					return randomPosition;
				}
			}

		}

		Vector2i LevelGenerator::GetTileInRandomRoom() {

			int randomRoomNumber = rand() % _rooms->size();

			Room room = _rooms->at(randomRoomNumber);

			Boxi box = Boxi(room.getPosition(), room.getSize());

			return GetWalkableTile(box);

		}
	} // End namespace gengine
} // End namespace glaze


  //void LevelGenerator::MarkWalls() {
  //	
  //	for (int y = 1; y < _roomMask.Size.y - 1; y++) {
  //		for (int x = 1; x < _roomMask.Size.x - 1; x++) {

  //			if (_level->GetTile(_roomMask.Position.x + x, _roomMask.Position.y + y).getType() == Tile::TileType::Floor) {
  //				for (Vector2i& direction : eight way) {

  //					Vector2i pos = Vector2i(_roomMask.Position.x + x + direction.x, _roomMask.Position.y + y + direction.y);

  //					if (_level->GetTile(pos).getType() != Tile::TileType::Floor) {
  //						_level->SetTile(pos, Tile('#', Tile::TileType::Wall));
  //					}

  //				}
  //			}

  //		}
  //	}

  //}