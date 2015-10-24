#include "enemy.h"

// Glibrary includes
#include <Glibrary/console/io.h>
#include <Glibrary/maths/vector2.h>
#include <Glibrary/audio/soundmanager.h>
#include <Glibrary/graphics/color.h>

// Gengine includes
#include "player.h"
#include "../../system/events/types/playermovedevent.h"

using namespace glaze;
using namespace glibrary;

namespace glaze {
	namespace gengine {

		Enemy::Enemy(const std::string& name, const float& totalDamage, const float& totalArmour, const float& health, const float& speed)
			: Creature(name, 'E', Color::RED, health, totalDamage, totalArmour, speed), _aiState(AIState::Idling) {}

		void Enemy::PrintStats(const Vector2i& position, unsigned int& lines) {

			Creature::PrintStats(position, lines);

			lines += 2;
			Out::PrintlnAt(position.x + 2, position.y + lines, "Enemy");
#ifdef _DEBUG
			lines++;
			Out::PrintlnAt(position.x + 2, position.y + lines, "State: " + GetAIStateName(_aiState));
#endif

		}

		void Enemy::Interact(Player* player) {
			SoundManager::GetPlayList("Ouch")->PlayRandom(true);
			player->Damage(_totalDamage);
			Damage(player->getTotalDamage());
		}

		std::string Enemy::GetAIStateName(const AIState& state) const {
			switch (state) {
			case AIState::Idling:
				return "Idling";
			case AIState::Running:
				return "Running";
			case AIState::Chasing:
				return "Chasing";
			case AIState::Attacking:
				return "Attacking";
			default:
				return "Error";

			}
		}

		void Enemy::onPlayerMoved(Event* event) {
			PlayerMovedEvent* e = static_cast<PlayerMovedEvent*>(event);
			UpdateVisibility(e->_player->getPosition());
			UpdateMovement(e->_toPosition);
			UpdateState(e->_player);
		}

		void Enemy::UpdateMovement(const Vector2i& playerPosition) {

			if (CanSeePlayer(playerPosition)) {
				if (playerPosition == getPosition()) return;

				Vector2f playerDirection = (Vector2f)(playerPosition - getPosition()).Normalized();

				Vector2i finalDirection;

				if (playerDirection.x > 0.0f) {
					finalDirection.x = 1;
				}
				else if (playerDirection.x < 0.0f) {
					finalDirection.x = -1;
				}

				if (playerDirection.y > 0.0f) {
					finalDirection.y = 1;
				}
				else if (playerDirection.y < 0.0f) {
					finalDirection.y = -1;
				}

				if (_aiState == AIState::Running) {
					finalDirection = -finalDirection;
				}

				Move(finalDirection);

			}
		}

		void Enemy::UpdateState(Player* player) {
			if (CanSeePlayer(player->getPosition()))
				_aiState = AIState::Chasing;
			else
				_aiState = AIState::Idling;

			if (player->getPosition() == getPosition()) {
				_aiState = AIState::Attacking;
			}

			if (_health <= _maxHealth / 5.0f)
				_aiState = AIState::Running;
		}

	} // End namespace gengine
} // End namespace glaze