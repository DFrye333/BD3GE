#ifndef BD3GE_VECTOR_H
#define BD3GE_VECTOR_H

#include <cmath>

#include "../system/globals.h"

namespace BD3GE {
	class Vector3 {
		public:

			Vector3(void);
			Vector3(const float a[3]);
			Vector3(const float first, const float second, const float third);
			Vector3(const Vector3& source);
			const float dot_product(const Vector3& other);
			const Vector3 cross_product(const Vector3& other);
			const float get_magnitude(void);
			const Vector3 get_normalized(void);
			const Vector3& normalize(void);
			const Vector3& operator=(const Vector3& other);
			const Vector3& operator+=(const Vector3& other);
			const Vector3 operator+(const Vector3& other);
			const Vector3& operator-=(const Vector3& other);
			const Vector3 operator-(const Vector3& other);
			const Vector3& operator*=(const Vector3& other);
			const Vector3 operator*(const Vector3& other);
			const Vector3& operator*=(const float other);
			const Vector3 operator*(const float other);
			const Vector3& operator/=(const Vector3& other);
			const Vector3 operator/(const Vector3& other);
			const Vector3& operator/=(const float other);
			const Vector3 operator/(const float other);

			static constexpr float EPSILON = 1.0e-12f;

			union // Union allows different Vector3 notation in different contexts. {
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

				float a[3];	// Vector3 as generic array.
			} v;
	};
}

#endif // BD3GE_VECTOR_H
