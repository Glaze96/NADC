#pragma once

// System includes
#include <string>

// Glibrary includes
#include <Glibrary/maths/vector2.h>

// Gengine includes
#include "../entity.h"
#include <Glibrary/graphics/color.h>

namespace glaze {
	namespace gengine {

		class Creature : public Entity {
		protected: // Protected fields
			float _health;
			float _maxHealth;
			float _totalDamage;
			float _totalArmour;

			bool _noClip;
			bool _invincible;

		protected: // Protected 'structors
			Creature(const std::string& name, const char& appearance, const int& color = Color::WHITE, const float& health = 100.0f, const float& totalDamage = 0.0f, const float& totalArmour = 0.0f);
			~Creature() {}

		public: // getters
			const float&	getTotalDamage()	const { return _totalDamage; }
			const float&	getTotalArmour()	const { return _totalArmour; }
			const float&	getHealth()			const { return _health; }

		public: // Public methods
			void			Heal(const float& value);
			void			Damage(const float& value); // If health < 0: Kill()
			bool			ToggleNoClip();
			bool			ToggleInvincibility();
			void			DoAction(Entity* entity, Player* player, const Action& action) override;
			virtual void	Kill(); // Adds corpse to level


		protected: // Protected methods
			bool Move(const Vector2i& direction); // Wall detection integrated
			void PrintStats(const Vector2i& position, unsigned int& lines) override;
		
		};

	} // End namespace gengine
} // End namespace glaze