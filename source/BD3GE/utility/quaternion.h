#ifndef BD3GE_QUATERNION_H
#define BD3GE_QUATERNION_H

#include <cmath>

#include "../system/api.h"
#include "../utility/matrix.h"
#include "../utility/vector.h"

namespace BD3GE {
	class Quaternion {
		public:

			static Quaternion identity();

			Quaternion();
			Quaternion(float scalar, Vector3 vector);
			Quaternion(Matrix4 matrix);
			Quaternion(Vector3 euler);
			const Quaternion& operator+=(const Quaternion& other);
			const Quaternion operator+(const Quaternion& other) const;
			const Quaternion& operator-=(const Quaternion& other);
			const Quaternion operator-(const Quaternion& other) const;
			const Quaternion& operator*=(const Quaternion& other);
			const Quaternion operator*(const Quaternion& other) const;
			const Quaternion& operator*=(const float other);
			const Quaternion operator*(const float other) const;
			const Quaternion normalize() const;
			const Quaternion conjugate() const;
			const Quaternion inverse() const;
			const float magnitude() const;
			const float squared_magnitude() const;
			Matrix4 get_rotation_matrix() const;
			friend std::ostream& operator<<(std::ostream& out, const Quaternion& quaternion);

		private:

			float scalar;
			Vector3 vector;
	};
}

#endif BD3GE_QUATERNION_H