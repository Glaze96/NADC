#pragma once

// Glibrary includes
#include <Glibrary/maths/vector2.h>

namespace glaze {
	using namespace glibrary;
	namespace gengine {
		
		class Tile {
		public:
			enum Type {
				Del,
				Floor,
				Wall,
				Door
			};

		private: // Private fields
			char _appearance;
			Type _type;
			bool _visible;

		public: // Con- & destructor's	
			Tile(const char& appearance, const Type& type);
			~Tile() { }

		public: // Public getters
			const char&			getAppearence() const { return _appearance; }
			const Type&			getType() const { return _type; }
			const bool&			getVisible() const { return _visible; }

		public: // Public setters
			void setVisible(const bool& value) { _visible = value; }
		};


	} // End namespace gengine
} // End namespace glaze