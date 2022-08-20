#include "quaternion.h"

namespace BD3GE {
	Quaternion Quaternion::identity() {
		return Quaternion(1.0f, Vector3(0.0f, 0.0f, 0.0f));
	}

	Quaternion::Quaternion() : Quaternion(Quaternion::identity()) {}

	Quaternion::Quaternion(float scalar, Vector3 vector) : scalar(scalar), vector(vector) {}

	Quaternion::Quaternion(Matrix4 matrix) {
		float trace = matrix(0, 0) + matrix(1, 1) + matrix(2, 2);
		if (trace > 0.0f) {
			float s = sqrt(trace + 1.0f);
			scalar = 0.5f * s;

			float t = 0.5f / s;
			vector = Vector3(
				t * (matrix(2, 1) - matrix(1, 2)),
				t * (matrix(0, 2) - matrix(2, 0)),
				t * (matrix(1, 0) - matrix(0, 1))
			);
		} else {
			int i = 0;
			if (matrix(1, 1) > matrix(0, 0)) i = 1;
			if (matrix(2, 2) > matrix(i, i)) i = 2;

			static const int NEXT[3] = {1, 2, 0};
			int j = NEXT[i];
			int k = NEXT[j];

			float s = sqrt((matrix(i, i) - (matrix(j, j) + matrix(k, k))) + 1.0f);
			float t = s != 0.0f ? 0.5f / s : s;
			
			scalar = t * (matrix(k, j) - matrix(j, k));

			float v[3];
			v[i] = 0.5f * s;
			v[j] = t * (matrix(j, i) + matrix(i, j));
			v[k] = t * (matrix(k, i) + matrix(i, k));

			vector = Vector3(v[0], v[1], v[2]);
		}
	}

	Quaternion::Quaternion(Vector3 euler) {
		float x = euler.v.g.x;
		float y = euler.v.g.y;
		float z = euler.v.g.z;

		this->scalar = cos(x / 2) * cos(y / 2) * cos(z / 2) + sin(x / 2) * sin(y / 2) * sin(z / 2);
		this->vector = Vector3(
			sin(x / 2) * cos(y / 2) * cos(z / 2) - cos(x / 2) * sin(y / 2) * sin(z / 2),
			cos(x / 2) * sin(y / 2) * cos(z / 2) + sin(x / 2) * cos(y / 2) * sin(z / 2),
			cos(x / 2) * cos(y / 2) * sin(z / 2) - sin(x / 2) * sin(y / 2) * cos(z / 2)
		);
	}

	const Quaternion& Quaternion::operator+=(const Quaternion& other) {
		scalar += other.scalar;
		vector += other.vector;

		return *this;
	}

	const Quaternion Quaternion::operator+(const Quaternion& other) const {
		return Quaternion(*this) += other;
	}

	const Quaternion& Quaternion::operator-=(const Quaternion& other) {
		scalar -= other.scalar;
		vector -= other.vector;

		return *this;
	}

	const Quaternion Quaternion::operator-(const Quaternion& other) const {
		return Quaternion(*this) -= other;
	}

	const Quaternion& Quaternion::operator*=(const Quaternion& other) {
		float scalar = (this->scalar * other.scalar) - vector.dot_product(other.vector);
		vector = (other.vector * this->scalar) + (vector * other.scalar) + vector.cross_product(other.vector);
		this->scalar = scalar;

		return *this;
	}

	const Quaternion Quaternion::operator*(const Quaternion& other) const {
		return Quaternion(*this) *= other;
	}

	const Quaternion& Quaternion::operator*=(const float other) {
		scalar *= other;
		vector *= other;

		return *this;
	}

	const Quaternion Quaternion::operator*(const float other) const {
		return Quaternion(*this) *= other;
	}

	const Quaternion Quaternion::normalize() const {
		return (*this) * (1 / magnitude());
	}

	const Quaternion Quaternion::conjugate() const {
		return Quaternion(scalar, -vector);
	}

	const Quaternion Quaternion::inverse() const {
		float squared_magnitude = this->squared_magnitude();
		Quaternion conjugate = this->conjugate();
		return Quaternion(conjugate.scalar / squared_magnitude, conjugate.vector / squared_magnitude);
	}

	const float Quaternion::magnitude() const {
		return sqrt(squared_magnitude());
	}

	const float Quaternion::squared_magnitude() const {
		return (scalar * scalar) + (vector.v.g.x * vector.v.g.x) + (vector.v.g.y * vector.v.g.y) + (vector.v.g.z * vector.v.g.z);
	}

	Matrix4 Quaternion::get_rotation_matrix() const {
		float s = scalar;
		float x = vector.v.g.x;
		float y = vector.v.g.y;
		float z = vector.v.g.z;

		return Matrix4(
			1 - (2 * ((y * y) + (z * z))), 2 * ((x * y) + (s * z)), 2 * ((x * z) - (s * y)), 0,
			2 * ((x * y) - (s * z)), 1 - (2 * ((x * x) + (z * z))), 2 * ((y * z) + (s * x)), 0,
			2 * ((x * z) + (s * y)), 2 * ((y * z) - (s * x)), 1 - (2 * ((x * x) + (y * y))), 0,
			0, 0, 0, 1
		);
	}

	std::ostream& operator<<(std::ostream& out, const Quaternion& quaternion) {
		return out << quaternion.scalar << ", (" << quaternion.vector.v.a[0] << ", " << quaternion.vector.v.a[1] << ", " << quaternion.vector.v.a[2] << ")";
	}
}