#pragma once

// System includes
#include <string>
#include <vector>

// Glibrary includes
#include <Glibrary/maths/vector2.h>
#include <Glibrary/console/log.h>

// Gengine includes
#include "../level/level.h"
#include "../system/events/eventlistener.h"

namespace glaze {
	namespace gengine {

		enum Action {
			Right,
			Left
		};

		class Entity : public EventListener {
		protected: // Protected fields
			Level* _level;

		private: // Private fields
			std::string _name;
			char		_appearance;
			int			_color;
			bool		_visible;
			bool		_inInventory;
			bool		_equipped;
			Vector2i	_position;
			int			_id;
			static int	_idCounter;

		public: // Con- & destructor's
			
			Entity(const std::string& name, const char& appearance, const int& color);
			virtual ~Entity() {}

		public: // getters
			const std::string&	getName()			const { return _name; }
			const Vector2i&		getPosition()		const { return _position; }
			const int&			getId()				const { return _id; }
			const bool&			getEquipped()		const { return _equipped; }
			Level*				getLevel()			const { return _level; }
			const bool&			getInInventory()	const { return _inInventory; }
			const int&			getIdCounter()		const { _idCounter++; return _idCounter; }

		public: // Getters
			std::string			GetUniqueName()		const { return _name + " #" + std::to_string(_id); }

		public: // setters
			void setInInventory(const bool& value)		{ _inInventory = value; }
			void setPosition(const Vector2i& position)	{ _position = position; }
			void setVisible(const bool& value)			{ _visible = value; }
			void setLevel(Level* level)					{ _level = level; }
			void setEquipped(const bool& value)			{ _equipped = value; }
			void setId(const int& value)				{ _id = value; }

		public: // Public methods
			void			Draw() const;
			virtual void	PrintStats(const Vector2i& position, unsigned int& lines);
			virtual void	DoAction(Entity* entity, Player* player, const Action& action) { Log::AddMessage("Unimplemented action"); }
			virtual void	Interact(Player* player) { Log::AddMessage("Unimplemented interaction"); }

			virtual Entity* clone() const { return new Entity(*this); }
			virtual Entity* newClone() { setId(getIdCounter()); return new Entity(*this); }

		protected: // Protected methods
			void UpdateVisibility(const Vector2i& playerPosition);
			bool CanSeePlayer(const Vector2i& playerPosition) const;
			virtual bool onEvent(Event& event) override;
			virtual void onPlayerMoved(Event* event);
		};



	} // End namespace gengine
} // End namespace glaze
