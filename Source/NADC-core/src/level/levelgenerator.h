#pragma once

// System includes
#include <vector>

// Glibrary includes
#include <Glibrary/maths/vector2.h>
#include <Glibrary/maths/geometry.h>

// Gengine includes
#include "level.h"
#include "tile.h"
#include "room.h"

namespace glaze {
	namespace gengine {

		class LevelGenerator {
		private: // Private fields
			static Level* _level;
			static Vector2i _levelSize;
			static Boxi _roomMask;
			static std::vector<Room>* _rooms;
			static float _windingPrecent;

		public: // Public methods
			static void GenerateLevel(Level *level, const int& numberOfRooms);

		private: // Private methods
			static void SetBorders(const Boxi& box, const Tile& tile);
			static void MakeDoors();
			static bool CanCarve(const Vector2i& position, const Vector2i& direction);
			static void AddRandomRooms(const int& numberOfRooms, const int& maxSize, const int& minSize);
			static void AddPassages(const Vector2i& start);
			static void DeleteDeadEnds();
			static void DeleteNonWalls();
			static void PushRoomsToLevel();
			static void SpawnEntities();
			static void SpawnStairs();
			static Vector2i GetWalkableTile(const Boxi& box = _roomMask);
			static Vector2i GetTileInRandomRoom();

		};


	} // End namespace gengine
} // End namespace glaze
