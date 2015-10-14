#include "entity.h"

// Glibrary includes
#include <Glibrary/console/io.h>
#include <Glibrary/graphics/color.h>

// Gengine includes
#include "creature/player.h"
#include "../level/levelgenerator.h"
#include "../system/events/types/playermovedevent.h"

namespace glaze {
	namespace gengine {

		int Entity::_idCounter = 0;

		Entity::Entity(const std::string& name, const char& appearance, const int& color)
			: _level(nullptr), _name(name), _appearance(appearance), _color(color), _visible(false),
			_inInventory(false), _equipped(false), _position(Vector2i(-1, -1)), _id(getIdCounter()) { }

		void Entity::PrintStats(const Vector2i& position, unsigned int& lines) {
#ifdef _DEBUG
			lines += 2;
			Out::PrintlnAt(position.x + 2, position.y + lines, "Entity");

			lines++;
			Out::PrintlnAt(position.x + 2, position.y + lines, "Name: %s", _name.c_str());

			lines++;
			Out::PrintlnAt(position.x + 2, position.y + lines, "In iventory: %s", _inInventory ? "true" : "false");

			lines++;
			Out::PrintlnAt(position.x + 2, position.y + lines, "Equipped: %s", _equipped ? "true" : "false");

			lines++;
			Out::PrintlnAt(position.x + 2, position.y + lines, "Position: %s", _position.ToString().c_str());

			lines++;
			Out::PrintlnAt(position.x + 2, position.y + lines, "Id: %i", _id);
#endif

		}

		bool Entity::onEvent(Event& event) {
			if(event.getType() == Event::Type::PlayerMoved)
				onPlayerMoved(&event);

			return false;
		}

		void Entity::Draw() const {

			if (_visible) {
				Color::SetColor(_color);

				Out::PrintchAt(_position.x, _position.y, _appearance);

				Color::ResetColor();
			}
		}

		bool Entity::CanSeePlayer(const Vector2i& playerPosition) const {

			int visibilityRange = 20;

			Vector2f delta(playerPosition - _position);

			if (delta.Mag() < visibilityRange) {

				bool foundWall = false;

				for (float pos = 0.0f; pos < delta.Mag(); pos += 1.0f) {

					Vector2f position(((delta.Normalized() * pos) + _position) + 0.5f);

					if (_level->GetTile(position.x, position.y).getType() == Tile::Type::Wall)
						foundWall = true;
				}

				if (!foundWall)
					return true;

			}
			return false;
		}

		void Entity::UpdateVisibility(const Vector2i& playerPosition) {
			if (!_visible)
				_visible = CanSeePlayer(playerPosition);
		}

		void Entity::onPlayerMoved(Event* event) {
			PlayerMovedEvent* e = static_cast<PlayerMovedEvent*>(event);
			UpdateVisibility(e->_player->getPosition());

		}

	} // End namespace gengine
} // End namespace glaze