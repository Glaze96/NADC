#pragma once

// System includes
#include <vector>

// Glibrary includes
#include <Glibrary/maths/vector2.h>

// Gengine includes
#include "tile.h"
#include "../system/events/eventhandler.h"

namespace glaze {
	namespace gengine {

		class Entity;
		class Enemy;
		class Consumable;
		class Player;

		class Level {
		private:
			Vector2i _size;
			int _levelNumber;
			
			std::vector<std::vector<Tile>> _tiles;
			std::vector<Entity*> _entities;
			
			EventHandler _eventHandler;

			unsigned int _numEntities;
			unsigned int _numEntitiesAtPosition;


		public: // Public con -& destructurs
			Level(const Vector2i& size, const bool& allVisible);
			void Fill(const Tile& tile);

		public: // Getters
			const unsigned int&		GetNumEntitiesAtPosition(const Vector2i& position) const;
			const unsigned int&		GetNumEntitiesAtPosition(const int& x, const int& y) const;
			std::vector<Entity*>	GetEntitiesAtPosition(const Vector2i& position) const;
			std::vector<Entity*>	GetEntitiesAtPosition(const int& x, const int& y) const;
			const Tile&				GetTile(const Vector2i& position) const;
			const Tile&				GetTile(const unsigned int& x, const unsigned int& y) const;
			std::vector<Vector2i>	GetTiles(const Tile::Type& tileType) const;
			Entity*					GetStairsDown() const;
			Entity*					GetStairsUp() const;

		public: // getters
			const Vector2i& getSize() const			{ return _size; }
			const int&		getLevelNumber() const	{ return _levelNumber; }
			EventHandler&	getEventHandler() { return _eventHandler; }

		public: // Setters
			void SetTile(const Vector2i& position, const Tile& tile);
			void SetTile(const unsigned& x, const unsigned& y, const Tile& tile);

		public: // Methods
			void SetTileVisible(const Vector2i& position);
			void SetTileVisible(const int& x, const int& y);
			void SetAllVisible();
			bool AddEntity(Entity* item, const Vector2i& position = Vector2i(), const bool& supressLog = false);
			void DestroyEntity(Entity* entity);

			void Draw() const;

		private:
			void DrawLevel() const;

		};

	} // End namespace gengine
} // End namespace glaze