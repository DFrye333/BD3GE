#ifndef BD3GE_VECTOR_H
#define BD3GE_VECTOR_H

#include <cmath>
#include <iostream>
#include <string>

#include "../system/api.h"

namespace BD3GE {
	class BD3GE_API Vector2 {
		public:
			Vector2();
			Vector2(const float a[2]);
			Vector2(const float first, const float second);
			Vector2(const Vector2& source);
			const float dot_product(const Vector2& other);
			const float cross_product(const Vector2& other);
			const float get_magnitude();
			const Vector2 get_normalized();
			const Vector2& normalize();
			const std::string get_hash();
			const Vector2& operator=(const Vector2& other);
			const Vector2& operator+=(const Vector2& other);
			const Vector2 operator+(const Vector2& other) const;
			const Vector2& operator-=(const Vector2& other);
			const Vector2 operator-(const Vector2& other) const;
			const Vector2& operator*=(const Vector2& other);
			const Vector2 operator*(const Vector2& other) const;
			const Vector2& operator*=(const float other);
			const Vector2 operator*(const float other) const;
			const Vector2& operator/=(const Vector2& other);
			const Vector2 operator/(const Vector2& other) const;
			const Vector2& operator/=(const float other);
			const Vector2 operator/(const float other) const;
			const Vector2 operator-() const;
			const bool operator==(const Vector2& other) const;
			friend BD3GE_API std::ostream& operator<<(std::ostream& out, const Vector2& vec);

			static constexpr float EPSILON = 1.0e-12f;
			union {				// Union allows different Vector2 notation in different contexts.
				struct {		// Vector2 as geometry.
					float x;
					float y;
				} g;

				struct {		// Vector2 as UV.
					float u;
					float v;
				} c;

				float a[2];		// Vector2 as generic array.
			} v;
	};

	class BD3GE_API Vector3 {
		public:
			Vector3();
			Vector3(const float a[3]);
			Vector3(const float first, const float second, const float third);
			Vector3(const Vector3& source);
			const float dot_product(const Vector3& other);
			const Vector3 cross_product(const Vector3& other);
			const float get_magnitude();
			const Vector3 get_normalized();
			const Vector3& normalize();
			const std::string get_hash();
			const Vector3& operator=(const Vector3& other);
			const Vector3& operator+=(const Vector3& other);
			const Vector3 operator+(const Vector3& other) const;
			const Vector3& operator-=(const Vector3& other);
			const Vector3 operator-(const Vector3& other) const;
			const Vector3& operator*=(const Vector3& other);
			const Vector3 operator*(const Vector3& other) const;
			const Vector3& operator*=(const float other);
			const Vector3 operator*(const float other) const;
			const Vector3& operator/=(const Vector3& other);
			const Vector3 operator/(const Vector3& other) const;
			const Vector3& operator/=(const float other);
			const Vector3 operator/(const float other) const;
			const Vector3 operator-() const;
			const bool operator==(const Vector3& other) const;
			friend BD3GE_API std::ostream& operator<<(std::ostream& out, const Vector3& vec);

			static constexpr float EPSILON = 1.0e-12f;
			union {				// Union allows different Vector3 notation in different contexts.
				struct {		// Vector3 as geometry.
					float x;
					float y;
					float z;
				} g;

				struct {		// Vector3 as color.
					float r;
					float g;
					float b;
				} c;

				float a[3];		// Vector3 as generic array.
			} v;
	};
}

#endif // BD3GE_VECTOR_H