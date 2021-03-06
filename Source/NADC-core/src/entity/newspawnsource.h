#pragma once
#include "entity.h"

namespace glaze {
	namespace gengine {
		
		class SpawnSource {
		private: // Private fields
			Entity* _entity;
			std::string _name;
			float _spawnChance;

		public: // Con- & destructor's
			explicit SpawnSource(Entity* entity, const float& spawnChance = 0.0f);
			~SpawnSource() {}
		
		public: // getters
			const std::string&	getName()			const { return _name; }
			const float&		getSpawnChance()	const { return _spawnChance; }

		public: // Getters
			Entity* GetEntity() const;

		public: // setters
			void setSpawnChance(const float& value) { _spawnChance = value; }

		};


	} // End namespace gengine
} // End namespace glaze