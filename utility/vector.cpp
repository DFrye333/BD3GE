#include "vector.h"

namespace BD3GE {
	/*
	 * 	Vector3 class
	 */

	Vector3::Vector3(void) {
		v.a[0] = 0.0f;
		v.a[1] = 0.0f;
		v.a[2] = 0.0f;
	}

	Vector3::Vector3(const float a[3]) {
		v.a[0] = a[0];
		v.a[1] = a[1];
		v.a[2] = a[2];
	}

	Vector3::Vector3(const float first, const float second, const float third) {
		v.a[0] = first;
		v.a[1] = second;
		v.a[2] = third;
	}

	Vector3::Vector3(const Vector3& source) {
		v.a[0] = source.v.a[0];
		v.a[1] = source.v.a[1];
		v.a[2] = source.v.a[2];
	}

	const float Vector3::dot_product(const Vector3& other) {
		return ((v.a[0] * other.v.a[0]) + (v.a[1] * other.v.a[1]) + (v.a[2] + other.v.a[2]));
	}

	const Vector3 Vector3::cross_product(const Vector3& other) {
		return Vector3(
			(this->v.a[1] * other.v.a[2]) - (this->v.a[2] * other.v.a[1]),
			(this->v.a[2] * other.v.a[0]) - (this->v.a[0] * other.v.a[2]),
			(this->v.a[0] * other.v.a[1]) - (this->v.a[1] * other.v.a[0])
		);
	}

	const float Vector3::get_magnitude(void) {
		return sqrt(dot_product(*this));
	}

	const Vector3 Vector3::get_normalized(void) {
		float magnitude = get_magnitude();
		if (magnitude > EPSILON) {
			return Vector3(*this / magnitude);
		}
		else {
			g_log.write(BD3GE::LOG_TYPE::ERR, "Vector magnitude <= EPSILON");
		}
	}

	const Vector3& Vector3::normalize(void) {
		float magnitude = get_magnitude();
		if (magnitude > EPSILON) {
			return *this /= magnitude;
		} else {
			g_log.write(BD3GE::LOG_TYPE::ERR, "Vector magnitude <= EPSILON");
		}
	}

	const Vector3& Vector3::operator=(const Vector3& other) {
		v.a[0] = other.v.a[0];
		v.a[1] = other.v.a[1];
		v.a[2] = other.v.a[2];

		return *this;
	}

	const Vector3& Vector3::operator+=(const Vector3& other) {
		v.a[0] += other.v.a[0];
		v.a[1] += other.v.a[1];
		v.a[2] += other.v.a[2];

		return *this;
	}

	const Vector3 Vector3::operator+(const Vector3& other) {
		return Vector3(*this) += other;
	}

	const Vector3& Vector3::operator-=(const Vector3& other) {
		v.a[0] -= other.v.a[0];
		v.a[1] -= other.v.a[1];
		v.a[2] -= other.v.a[2];

		return *this;
	}

	const Vector3 Vector3::operator-(const Vector3& other) {
		return Vector3(*this) -= other;
	}

	const Vector3& Vector3::operator*=(const Vector3& other) {
		v.a[0] *= other.v.a[0];
		v.a[1] *= other.v.a[1];
		v.a[2] *= other.v.a[2];

		return *this;
	}

	const Vector3 Vector3::operator*(const Vector3& other) {
		return Vector3(*this) *= other;
	}

	const Vector3& Vector3::operator*=(const float other) {
		v.a[0] *= other;
		v.a[1] *= other;
		v.a[2] *= other;

		return *this;
	}

	const Vector3 Vector3::operator*(const float other) {
		return Vector3(*this) *= other;
	}

	const Vector3& Vector3::operator/=(const Vector3& other) {
		v.a[0] /= other.v.a[0];
		v.a[1] /= other.v.a[1];
		v.a[2] /= other.v.a[2];

		return *this;
	}

	const Vector3 Vector3::operator/(const Vector3& other) {
		return Vector3(*this) /= other;
	}

	const Vector3& Vector3::operator/=(const float other) {
		v.a[0] /= other;
		v.a[1] /= other;
		v.a[2] /= other;

		return *this;
	}

	const Vector3 Vector3::operator/(const float other) {
		return Vector3(*this) /= other;
	}

	const Vector3 Vector3::operator-() {
		return Vector3(*this) *= -1;
	}

	std::ostream& operator<<(std::ostream& out, const Vector3& vec) {
		return out << "(" << vec.v.a[0] << ", " << vec.v.a[1] << ", " << vec.v.a[2] << ")";
	}
}