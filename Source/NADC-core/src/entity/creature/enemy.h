#pragma once

// Glibrary includes
#include <Glibrary/maths/vector2.h>

// Gengine includes
#include "creature.h"
#include "../../system/events/eventhandler.h"

namespace glaze {
	namespace gengine {


		class Enemy : public Creature {
		private:
			enum State { Idling, Running, Chasing, Attacking };

			State _state;

		public: // Con- & destructor's
			Enemy(const std::string& name, const float& totalDamage, const float& totalArmour, const float& health, const float& speed);
			~Enemy() {}

		public: // Public methods
			void	PrintStats(const Vector2i& position, unsigned int& lines) override;
			void	Interact(Player* player) override;

			Entity* clone() const override { return new Enemy(*this); }
			Entity* newClone() override {
				Enemy* newEnemy = new Enemy(*this);
				newEnemy->setId(getIdCounter());
				return newEnemy;
			}

		private: // Private methods
			void UpdateMovement(const Vector2i& playerPostion);
			void UpdateState(const Vector2i& playerPosition);
			void UpdateState(Player* player);
			void onPlayerMoved(Event* event) override;

			std::string GetAIStateName(const State& state) const;
		};

	} // End namespace gengine
} // End namespace glaze