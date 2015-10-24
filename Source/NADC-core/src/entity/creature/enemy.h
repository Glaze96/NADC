#pragma once

// Glibrary includes
#include <Glibrary/maths/vector2.h>

// Gengine includes
#include "creature.h"
#include "../../system/events/eventhandler.h"

namespace glaze {
	namespace gengine {

		enum AIState {
			Idling,
			Running,
			Chasing,
			Attacking
		};

		class Enemy : public Creature {
		private:
			AIState _aiState;
		public: // Con- & destructor's
			Enemy(const std::string& name, const float& totalDamage, const float& totalArmour, const float& health, const float& speed);
			~Enemy() { }

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
			std::string GetAIStateName(const AIState& state) const;
			void onPlayerMoved(Event* event) override;
			void UpdateMovement(const Vector2i& playerPostion);
			void UpdateState(Player* player);
		};

	} // End namespace gengine
} // End namespace glaze