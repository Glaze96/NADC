#pragma once

#include <string>

namespace glaze {
	namespace glibrary {

		class Vector2i;

		class Vector2f {
		public: // Public fields
			float x, y;

		public: // Con -& Destructors
			Vector2f();
			explicit Vector2f(const Vector2i& v);
			Vector2f(const float& x, const float& y);
			Vector2f(const int& x, const int& y);

		public: // Public methods
			float Mag() const;
			Vector2f Normalized() const;
			std::string ToString() const;

		public: // Public static functions
			static Vector2f AngleToVector(const float& angle);

		public: // Public operators
			Vector2f operator+(const Vector2f& v) const;
			Vector2f operator+(const Vector2i& v) const;
			Vector2f operator-(const Vector2f& v) const;
			Vector2f operator-(const Vector2i& v) const;

			Vector2f operator+(const float& f) const;
			Vector2f operator-(const float& f) const;
			Vector2f operator*(const float& f) const;
			Vector2f operator/(const float& f) const;

			void operator+=(const Vector2f& v);
			void operator-=(const Vector2f& v);
			void operator*=(const float& f);
			void operator/=(const float& f);

			bool operator==(const Vector2f& v) const;
		};

		class Vector2i {
		public: // Public fields
			int x, y;

		public: // Con -& Destructors
			Vector2i();
			explicit Vector2i(const Vector2f& v);
			explicit Vector2i(const int& i);
			Vector2i(const int& x, const int& y);

		public: // Public methods
			float Mag() const;
			Vector2f Normalized() const;
			std::string ToString() const;

		public: // Public operators
			Vector2i operator-() const;

			Vector2i operator+(const Vector2i& v) const;
			Vector2i operator-(const Vector2i& v) const;
			Vector2i operator+(const int& i) const;
			Vector2i operator*(const int& i) const;

			Vector2f operator+(const Vector2f& v) const;
			Vector2f operator-(const Vector2f& v) const;
			Vector2f operator+(const float& f) const;
			Vector2f operator-(const float& f) const;
			Vector2f operator*(const float& f) const;
			Vector2f operator/(const float& f) const;

			void operator+=(const Vector2i& v);
			void operator-=(const Vector2i& v);
			void operator*=(const int& i);
			void operator+=(const int& i);

			bool operator==(const Vector2i& v) const;
		};

	}
}