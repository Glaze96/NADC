#include "enemy.h"

// Glibrary includes
#include <Glibrary/console/io.h>
#include <Glibrary/maths/vector2.h>
#include <Glibrary/audio/soundmanager.h>
#include <Glibrary/graphics/color.h>

// Gengine includes
#include "player.h"
#include "../../system/events/types/playermovedevent.h"
#include "../../system/events/types/playerattackedevent.h"

using namespace glaze;
using namespace glibrary;

namespace glaze {
	namespace gengine {

		Enemy::Enemy(const std::string& name, const float& totalDamage, const float& totalArmour, const float& health)
			: Creature(name, 'E', Color::RED, health, totalDamage, totalArmour), _aiState(AIState::Idling) { }

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
			SoundManager::GetPlaylist("Ouches")->PlayRandom(true);
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
			UpdateMovement(e->_player);
			UpdateState(e->_player);
		}

		void Enemy::UpdateMovement(Player* player) {
			if (_aiState == AIState::Running) {
				int randomX = rand() % 3 - 1;
				int randomY = rand() % 3 - 1;
				Move(Vector2i(randomX, randomY));
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