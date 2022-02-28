#include "vector.h"

namespace BD3GE {
	Vector2::Vector2() : v{0.0f, 0.0f} {}

	Vector2::Vector2(const float a[2]) : v{a[0], a[1]} {}

	Vector2::Vector2(const float first, const float second) : v{first, second} {}

	Vector2::Vector2(const Vector2& source) : v{source.v.a[0], source.v.a[1]} {}

	const float Vector2::dot_product(const Vector2& other) {
		return ((v.a[0] * other.v.a[0]) + (v.a[1] * other.v.a[1]));
	}

	const float Vector2::cross_product(const Vector2& other) {
		return (this->v.a[0] * other.v.a[1]) - (other.v.a[0] * this->v.a[1]);
	}

	const float Vector2::get_magnitude() {
		return sqrt(dot_product(*this));
	}

	const Vector2 Vector2::get_normalized() {
		float magnitude = get_magnitude();
		if (magnitude > EPSILON) {
			return Vector2(*this / magnitude);
		}
	}

	const Vector2& Vector2::normalize() {
		float magnitude = get_magnitude();
		if (magnitude > EPSILON) {
			return *this /= magnitude;
		}
	}

	const Vector2& Vector2::operator=(const Vector2& other) {
		v.a[0] = other.v.a[0];
		v.a[1] = other.v.a[1];

		return *this;
	}

	const Vector2& Vector2::operator+=(const Vector2& other) {
		v.a[0] += other.v.a[0];
		v.a[1] += other.v.a[1];

		return *this;
	}

	const Vector2 Vector2::operator+(const Vector2& other) const {
		return Vector2(*this) += other;
	}

	const Vector2& Vector2::operator-=(const Vector2& other) {
		v.a[0] -= other.v.a[0];
		v.a[1] -= other.v.a[1];

		return *this;
	}

	const Vector2 Vector2::operator-(const Vector2& other) const {
		return Vector2(*this) -= other;
	}

	const Vector2& Vector2::operator*=(const Vector2& other) {
		v.a[0] *= other.v.a[0];
		v.a[1] *= other.v.a[1];

		return *this;
	}

	const Vector2 Vector2::operator*(const Vector2& other) const {
		return Vector2(*this) *= other;
	}

	const Vector2& Vector2::operator*=(const float other) {
		v.a[0] *= other;
		v.a[1] *= other;

		return *this;
	}

	const Vector2 Vector2::operator*(const float other) const {
		return Vector2(*this) *= other;
	}

	const Vector2& Vector2::operator/=(const Vector2& other) {
		v.a[0] /= other.v.a[0];
		v.a[1] /= other.v.a[1];

		return *this;
	}

	const Vector2 Vector2::operator/(const Vector2& other) const {
		return Vector2(*this) /= other;
	}

	const Vector2& Vector2::operator/=(const float other) {
		v.a[0] /= other;
		v.a[1] /= other;

		return *this;
	}

	const Vector2 Vector2::operator/(const float other) const {
		return Vector2(*this) /= other;
	}

	const Vector2 Vector2::operator-() const {
		return Vector2(*this) *= -1;
	}

	std::ostream& operator<<(std::ostream& out, const Vector2& vec) {
		return out << "(" << vec.v.a[0] << ", " << vec.v.a[1] << ")";
	}

	Vector3::Vector3() : v{0.0f, 0.0f, 0.0f} {}

	Vector3::Vector3(const float a[3]) : v{a[0], a[1], a[2]} {}

	Vector3::Vector3(const float first, const float second, const float third) : v{first, second, third} {}

	Vector3::Vector3(const Vector3& source) : v{source.v.a[0], source.v.a[1], source.v.a[2]} {}

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
	}

	const Vector3& Vector3::normalize(void) {
		float magnitude = get_magnitude();
		if (magnitude > EPSILON) {
			return *this /= magnitude;
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

	const Vector3 Vector3::operator+(const Vector3& other) const {
		return Vector3(*this) += other;
	}

	const Vector3& Vector3::operator-=(const Vector3& other) {
		v.a[0] -= other.v.a[0];
		v.a[1] -= other.v.a[1];
		v.a[2] -= other.v.a[2];

		return *this;
	}

	const Vector3 Vector3::operator-(const Vector3& other) const {
		return Vector3(*this) -= other;
	}

	const Vector3& Vector3::operator*=(const Vector3& other) {
		v.a[0] *= other.v.a[0];
		v.a[1] *= other.v.a[1];
		v.a[2] *= other.v.a[2];

		return *this;
	}

	const Vector3 Vector3::operator*(const Vector3& other) const {
		return Vector3(*this) *= other;
	}

	const Vector3& Vector3::operator*=(const float other) {
		v.a[0] *= other;
		v.a[1] *= other;
		v.a[2] *= other;

		return *this;
	}

	const Vector3 Vector3::operator*(const float other) const {
		return Vector3(*this) *= other;
	}

	const Vector3& Vector3::operator/=(const Vector3& other) {
		v.a[0] /= other.v.a[0];
		v.a[1] /= other.v.a[1];
		v.a[2] /= other.v.a[2];

		return *this;
	}

	const Vector3 Vector3::operator/(const Vector3& other) const {
		return Vector3(*this) /= other;
	}

	const Vector3& Vector3::operator/=(const float other) {
		v.a[0] /= other;
		v.a[1] /= other;
		v.a[2] /= other;

		return *this;
	}

	const Vector3 Vector3::operator/(const float other) const {
		return Vector3(*this) /= other;
	}

	const Vector3 Vector3::operator-() const {
		return Vector3(*this) *= -1;
	}

	std::ostream& operator<<(std::ostream& out, const Vector3& vec) {
		return out << "(" << vec.v.a[0] << ", " << vec.v.a[1] << ", " << vec.v.a[2] << ")";
	}
}