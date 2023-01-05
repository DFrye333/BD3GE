#ifndef BD3GE_VECTOR_H
#define BD3GE_VECTOR_H

#include <cmath>
#include <iostream>
#include <string>

#include "../system/api.h"

namespace BD3GE {
	// Forward declarations
	class Vector2;
	class Vector3;
	class Vector4;

	class BD3GE_API Vector2 {
		public:
			static Vector2 Zero();

			Vector2();
			Vector2(const float a[2]);
			Vector2(const float first, const float second);
			Vector2(const Vector2& source);
			float dot_product(const Vector2& other);
			float cross_product(const Vector2& other);
			float get_magnitude();
			Vector2 get_normalized();
			Vector2& normalize();
			std::string get_hash();
			std::string to_string();
			Vector2& operator=(const Vector2& other);
			Vector2& operator+=(const Vector2& other);
			Vector2 operator+(const Vector2& other) const;
			Vector2& operator-=(const Vector2& other);
			Vector2 operator-(const Vector2& other) const;
			Vector2& operator*=(const Vector2& other);
			Vector2 operator*(const Vector2& other) const;
			Vector2& operator*=(const float other);
			Vector2 operator*(const float other) const;
			Vector2& operator/=(const Vector2& other);
			Vector2 operator/(const Vector2& other) const;
			Vector2& operator/=(const float other);
			Vector2 operator/(const float other) const;
			Vector2 operator-() const;
			bool operator==(const Vector2& other) const;
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
			static Vector3 Zero();

			Vector3();
			Vector3(const float a[3]);
			Vector3(const float first, const float second, const float third);
			Vector3(const Vector4& vec4);
			Vector3(const Vector3& source);
			float dot_product(const Vector3& other);
			Vector3 cross_product(const Vector3& other);
			float get_magnitude();
			Vector3 get_normalized();
			Vector3& normalize();
			std::string get_hash();
			std::string to_string();
			Vector3& operator=(const Vector3& other);
			Vector3& operator+=(const Vector3& other);
			Vector3 operator+(const Vector3& other) const;
			Vector3& operator-=(const Vector3& other);
			Vector3 operator-(const Vector3& other) const;
			Vector3& operator*=(const Vector3& other);
			Vector3 operator*(const Vector3& other) const;
			Vector3& operator*=(const float other);
			Vector3 operator*(const float other) const;
			Vector3& operator/=(const Vector3& other);
			Vector3 operator/(const Vector3& other) const;
			Vector3& operator/=(const float other);
			Vector3 operator/(const float other) const;
			Vector3 operator-() const;
			bool operator==(const Vector3& other) const;
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

	class BD3GE_API Vector4 {
		public:
			static Vector4 Zero();

			Vector4();
			Vector4(const float a[4]);
			Vector4(const float first, const float second, const float third, const float fourth);
			Vector4(const Vector3& vec3, const float fourth);
			Vector4(const Vector4& source);
			float dot_product(const Vector4& other);
			float get_magnitude();
			Vector4 get_normalized();
			Vector4& normalize();
			std::string get_hash();
			std::string to_string();
			Vector4& operator=(const Vector4& other);
			Vector4& operator+=(const Vector4& other);
			Vector4 operator+(const Vector4& other) const;
			Vector4& operator-=(const Vector4& other);
			Vector4 operator-(const Vector4& other) const;
			Vector4& operator*=(const Vector4& other);
			Vector4 operator*(const Vector4& other) const;
			Vector4& operator*=(const float other);
			Vector4 operator*(const float other) const;
			Vector4& operator/=(const Vector4& other);
			Vector4 operator/(const Vector4& other) const;
			Vector4& operator/=(const float other);
			Vector4 operator/(const float other) const;
			Vector4 operator-() const;
			bool operator==(const Vector4& other) const;
			friend BD3GE_API std::ostream& operator<<(std::ostream& out, const Vector4& vec);

			static constexpr float EPSILON = 1.0e-12f;
			union {				// Union allows different Vector4 notation in different contexts.
				struct {		// Vector4 as geometry.
					float x;
					float y;
					float z;
					float w;
				} g;

				struct {		// Vector4 as color.
					float r;
					float g;
					float b;
					float a;
				} c;

				float a[4];		// Vector4 as generic array.
			} v;
	};
}

#endif // BD3GE_VECTOR_H