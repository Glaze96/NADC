#pragma once


namespace glaze {
	namespace gengine {

		class Event {
		public:
			enum Type {
				PlayerMoved,
				PlayerAttacked
			};

		private:
			Type _type;
			bool _handled;

		protected:
			explicit Event(const Type& type);

		public: // Public getters
			const Type& getType() const { return _type; }
			const bool& getHandled() const { return _handled; }

		public: // Public setters
			void setHandled(bool handled) { _handled = handled; }

		};

	} // End namespace gengine
} // End namespace glaze