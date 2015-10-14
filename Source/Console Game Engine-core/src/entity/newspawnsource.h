#pragma once
#include "entity.h"

namespace glaze {
	namespace gengine {
		
		class SpawnSource {
		// fields
		private:
			Entity* _entity;
			std::string _name;
			float _spawnChance;

		// 'structors
		public:
			explicit SpawnSource(Entity* entity, SpawnSource* lastSpawnSource = nullptr, const float& spawnChance = 0.0f);

		// getters
		public:
			const std::string&	getName()			const { return _name; }
			const float&		getSpawnChance()	const { return _spawnChance; }

		// setters
		public:
			void setSpawnChance(const float& value) { _spawnChance = value; }

		// Getters
		public:
			Entity* GetEntity() const;

		};


	} // End namespace gengine
} // End namespace glaze