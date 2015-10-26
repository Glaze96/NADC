#include "creature.h"

// Glibrary includes
#include <Glibrary/console/io.h>
#include <Glibrary/graphics/color.h>
#include <Glibrary/console/log.h>

namespace glaze {
using namespace glibrary;
	namespace gengine {

		Creature::Creature(const std::string& name, const char& appearance, const int& color, 
			const float& health, const float& totalDamage, const float& totalArmour, const float & speed)
			: Entity(name, appearance, color),
			_health(health), _maxHealth(health), _totalDamage(totalDamage), 
			_totalArmour(totalArmour), _speed(speed), _stepCounter(0.0f), _noClip(false), _invincible(false) {}
		
		void Creature::DoAction(Entity* entity, Player* player, const Action& action) {
			entity->Interact(player);
		}

		bool Creature::Move(const Vector2i& direction) {

			_stepCounter += _speed;

			if (_stepCounter < 1.0f) return false;
			
			_stepCounter = 0.0f;

			Vector2i newPosition = getPosition() + direction;

			if (getCurrentLevel()->GetTile(newPosition).getType() == Tile::Type::Wall && !_noClip) {
				return false;
			}

			setPosition(newPosition);
			return true;
		}

		bool Creature::ToggleNoClip() {
			if (!_noClip)
				_noClip = true;
			else
				_noClip = false;

			Log::AddMessage(_noClip ? "Noclip on" : "Noclip off");

			return _noClip;
		}

		bool Creature::ToggleInvincibility() {
			if (!_invincible)
				_invincible = true;
			else
				_invincible = false;

			Log::AddMessage(_invincible ? "Invincibility on" : "Invincibility off");

			return _invincible;

		}
		void Creature::Damage(const float& value) {
			if (value > 0.0f) {
				if (!_invincible) {
					if (_health - value <= 0.0f)
						Kill();
					else
						_health -= value;
				}
			}
		}

		void Creature::Kill() {
			if (!_invincible) {
				_level->AddEntity(new Entity("Dead " + getName(), 'E', Color::WHITE), getPosition(), true);
				_level->DestroyEntity(this);
			}
		}

		void Creature::Heal(const float& value) {
			if (value > 0.0f) {
				if (_health + value > _maxHealth)
					_health = _maxHealth;
				else
					_health += value;
			}
		}

		void Creature::PrintStats(const Vector2i& position, unsigned int& lines) {

			Entity::PrintStats(position, lines);

			lines += 2;
			Out::PrintlnAt(position.x + 2, position.y + lines, "Creature");

			lines++;
			Color::SetColor(Color::GREEN);
			Out::PrintlnAt(position.x + 2, position.y + lines, "Health: %.1f/%.1f", _health, _maxHealth);
			Color::ResetColor();

			lines++;
			Color::SetColor(Color::RED);
			Out::PrintlnAt(position.x + 2, position.y + lines, "Damage: %.1f", _totalDamage);
			Color::ResetColor();

			lines++;
			Color::SetColor(Color::YELLOW);
			Out::PrintlnAt(position.x + 2, position.y + lines, "Armour: %.1f", _totalArmour);
			Color::ResetColor();



		}

		float Creature::CalulateDamage() {
			
			return 0.0f;
		}


	} // End namespace gengine
} // End namespace glaze