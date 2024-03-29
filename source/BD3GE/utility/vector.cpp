#include "vector.h"

namespace BD3GE {
	Vector2 Vector2::Zero() {
		return Vector2(0, 0);
	}

	Vector2::Vector2() : v{ 0.0f, 0.0f } {}

	Vector2::Vector2(const float a[2]) : v{ a[0], a[1] } {}

	Vector2::Vector2(const float first, const float second) : v{ first, second } {}

	Vector2::Vector2(const Vector2& source) : v{ source.v.a[0], source.v.a[1] } {}

	float Vector2::dot_product(const Vector2& other) {
		return ((v.a[0] * other.v.a[0]) + (v.a[1] * other.v.a[1]));
	}

	float Vector2::cross_product(const Vector2& other) {
		return (this->v.a[0] * other.v.a[1]) - (other.v.a[0] * this->v.a[1]);
	}

	float Vector2::get_magnitude() {
		return sqrt(dot_product(*this));
	}

	Vector2 Vector2::get_normalized() {
		float magnitude = get_magnitude();
		if (magnitude > EPSILON) {
			return Vector2(*this / magnitude);
		}
	}

	Vector2& Vector2::normalize() {
		float magnitude = get_magnitude();
		if (magnitude > EPSILON) {
			return *this /= magnitude;
		}
	}

	std::string Vector2::get_hash() {
		// TODO: This is pretty slow. Optimize!
		return std::to_string(v.a[0]) + "," + std::to_string(v.a[1]);
	}

	std::string Vector2::to_string() {
		return get_hash();
	}

	Vector2& Vector2::operator=(const Vector2& other) {
		v.a[0] = other.v.a[0];
		v.a[1] = other.v.a[1];

		return *this;
	}

	Vector2& Vector2::operator+=(const Vector2& other) {
		v.a[0] += other.v.a[0];
		v.a[1] += other.v.a[1];

		return *this;
	}

	Vector2 Vector2::operator+(const Vector2& other) const {
		return Vector2(*this) += other;
	}

	Vector2& Vector2::operator-=(const Vector2& other) {
		v.a[0] -= other.v.a[0];
		v.a[1] -= other.v.a[1];

		return *this;
	}

	Vector2 Vector2::operator-(const Vector2& other) const {
		return Vector2(*this) -= other;
	}

	Vector2& Vector2::operator*=(const Vector2& other) {
		v.a[0] *= other.v.a[0];
		v.a[1] *= other.v.a[1];

		return *this;
	}

	Vector2 Vector2::operator*(const Vector2& other) const {
		return Vector2(*this) *= other;
	}

	Vector2& Vector2::operator*=(const float other) {
		v.a[0] *= other;
		v.a[1] *= other;

		return *this;
	}

	Vector2 Vector2::operator*(const float other) const {
		return Vector2(*this) *= other;
	}

	Vector2& Vector2::operator/=(const Vector2& other) {
		v.a[0] /= other.v.a[0];
		v.a[1] /= other.v.a[1];

		return *this;
	}

	Vector2 Vector2::operator/(const Vector2& other) const {
		return Vector2(*this) /= other;
	}

	Vector2& Vector2::operator/=(const float other) {
		v.a[0] /= other;
		v.a[1] /= other;

		return *this;
	}

	Vector2 Vector2::operator/(const float other) const {
		return Vector2(*this) /= other;
	}

	Vector2 Vector2::operator-() const {
		return Vector2(*this) *= -1;
	}

	bool Vector2::operator==(const Vector2& other) const {
		return (
			v.a[0] == other.v.a[0] &&
			v.a[1] == other.v.a[1]
		);
	}

	bool Vector2::operator!=(const Vector2& other) const {
		return !(*this == other);
	}

	std::ostream& operator<<(std::ostream& out, const Vector2& vec) {
		return out << "(" << vec.v.a[0] << ", " << vec.v.a[1] << ")";
	}

	Vector3 Vector3::Zero() {
		return Vector3(0, 0, 0);
	}

	Vector3::Vector3() : v{ 0.0f, 0.0f, 0.0f } {}

	Vector3::Vector3(const float a[3]) : v{ a[0], a[1], a[2] } {}

	Vector3::Vector3(const float first, const float second, const float third) : v{ first, second, third } {}

	Vector3::Vector3(const Vector4& vec4) : v{ vec4.v.a[0], vec4.v.a[1], vec4.v.a[2] } {}

	Vector3::Vector3(const Vector3& source) : v{ source.v.a[0], source.v.a[1], source.v.a[2] } {}

	float Vector3::dot_product(const Vector3& other) {
		return ((v.a[0] * other.v.a[0]) + (v.a[1] * other.v.a[1]) + (v.a[2] * other.v.a[2]));
	}

	Vector3 Vector3::cross_product(const Vector3& other) {
		return Vector3(
			(this->v.a[1] * other.v.a[2]) - (this->v.a[2] * other.v.a[1]),
			(this->v.a[2] * other.v.a[0]) - (this->v.a[0] * other.v.a[2]),
			(this->v.a[0] * other.v.a[1]) - (this->v.a[1] * other.v.a[0])
		);
	}

	float Vector3::get_magnitude(void) {
		return sqrt(dot_product(*this));
	}

	Vector3 Vector3::get_normalized(void) {
		float magnitude = get_magnitude();
		if (magnitude > EPSILON) {
			return Vector3(*this / magnitude);
		} else {
			return Vector3(0, 0, 0);
		}
	}

	Vector3& Vector3::normalize(void) {
		return *this = get_normalized();
	}

	std::string Vector3::get_hash() {
		// TODO: This is pretty slow. Optimize!
		return std::to_string(v.a[0]) + "," + std::to_string(v.a[1]) + "," + std::to_string(v.a[2]);
	}

	std::string Vector3::to_string() {
		return get_hash();
	}

	Vector3& Vector3::operator=(const Vector3& other) {
		v.a[0] = other.v.a[0];
		v.a[1] = other.v.a[1];
		v.a[2] = other.v.a[2];

		return *this;
	}

	Vector3& Vector3::operator+=(const Vector3& other) {
		v.a[0] += other.v.a[0];
		v.a[1] += other.v.a[1];
		v.a[2] += other.v.a[2];

		return *this;
	}

	Vector3 Vector3::operator+(const Vector3& other) const {
		return Vector3(*this) += other;
	}

	Vector3& Vector3::operator-=(const Vector3& other) {
		v.a[0] -= other.v.a[0];
		v.a[1] -= other.v.a[1];
		v.a[2] -= other.v.a[2];

		return *this;
	}

	Vector3 Vector3::operator-(const Vector3& other) const {
		return Vector3(*this) -= other;
	}

	Vector3& Vector3::operator*=(const Vector3& other) {
		v.a[0] *= other.v.a[0];
		v.a[1] *= other.v.a[1];
		v.a[2] *= other.v.a[2];

		return *this;
	}

	Vector3 Vector3::operator*(const Vector3& other) const {
		return Vector3(*this) *= other;
	}

	Vector3& Vector3::operator*=(const float other) {
		v.a[0] *= other;
		v.a[1] *= other;
		v.a[2] *= other;

		return *this;
	}

	Vector3 Vector3::operator*(const float other) const {
		return Vector3(*this) *= other;
	}

	Vector3& Vector3::operator/=(const Vector3& other) {
		v.a[0] /= other.v.a[0];
		v.a[1] /= other.v.a[1];
		v.a[2] /= other.v.a[2];

		return *this;
	}

	Vector3 Vector3::operator/(const Vector3& other) const {
		return Vector3(*this) /= other;
	}

	Vector3& Vector3::operator/=(const float other) {
		v.a[0] /= other;
		v.a[1] /= other;
		v.a[2] /= other;

		return *this;
	}

	Vector3 Vector3::operator/(const float other) const {
		return Vector3(*this) /= other;
	}

	Vector3 Vector3::operator-() const {
		return Vector3(*this) *= -1;
	}

	bool Vector3::operator==(const Vector3& other) const {
		return (
			v.a[0] == other.v.a[0] &&
			v.a[1] == other.v.a[1] &&
			v.a[2] == other.v.a[2]
		);
	}

	bool Vector3::operator!=(const Vector3& other) const {
		return !(*this == other);
	}

	std::ostream& operator<<(std::ostream& out, const Vector3& vec) {
		return out << "(" << vec.v.a[0] << ", " << vec.v.a[1] << ", " << vec.v.a[2] << ")";
	}

	Vector4 Vector4::Zero() {
		return Vector4(0, 0, 0, 0);
	}

	Vector4::Vector4() : v{ 0.0f, 0.0f, 0.0f, 0.0f } {}

	Vector4::Vector4(const float a[4]) : v{ a[0], a[1], a[2], a[3] } {}

	Vector4::Vector4(const float first, const float second, const float third, const float fourth) : v{ first, second, third, fourth } {}

	Vector4::Vector4(const Vector3& vec3, const float fourth) : v{ vec3.v.a[0], vec3.v.a[1], vec3.v.a[2], fourth } {}

	Vector4::Vector4(const Vector4& source) : v{ source.v.a[0], source.v.a[1], source.v.a[2], source.v.a[3] } {}

	float Vector4::dot_product(const Vector4& other) {
		return ((v.a[0] * other.v.a[0]) + (v.a[1] * other.v.a[1]) + (v.a[2] * other.v.a[2]) + (v.a[3] * other.v.a[3]));
	}

	float Vector4::get_magnitude(void) {
		return sqrt(dot_product(*this));
	}

	Vector4 Vector4::get_normalized(void) {
		float magnitude = get_magnitude();
		if (magnitude > EPSILON) {
			return Vector4(*this / magnitude);
		}
		else {
			return Vector4(0, 0, 0, 0);
		}
	}

	Vector4& Vector4::normalize(void) {
		return *this = get_normalized();
	}

	std::string Vector4::get_hash() {
		// TODO: This is pretty slow. Optimize!
		return std::to_string(v.a[0]) + "," + std::to_string(v.a[1]) + "," + std::to_string(v.a[2]) + "," + std::to_string(v.a[3]);
	}

	std::string Vector4::to_string() {
		return get_hash();
	}

	Vector4& Vector4::operator=(const Vector4& other) {
		v.a[0] = other.v.a[0];
		v.a[1] = other.v.a[1];
		v.a[2] = other.v.a[2];
		v.a[3] = other.v.a[3];

		return *this;
	}

	Vector4& Vector4::operator+=(const Vector4& other) {
		v.a[0] += other.v.a[0];
		v.a[1] += other.v.a[1];
		v.a[2] += other.v.a[2];
		v.a[3] += other.v.a[3];

		return *this;
	}

	Vector4 Vector4::operator+(const Vector4& other) const {
		return Vector4(*this) += other;
	}

	Vector4& Vector4::operator-=(const Vector4& other) {
		v.a[0] -= other.v.a[0];
		v.a[1] -= other.v.a[1];
		v.a[2] -= other.v.a[2];
		v.a[3] -= other.v.a[3];

		return *this;
	}

	Vector4 Vector4::operator-(const Vector4& other) const {
		return Vector4(*this) -= other;
	}

	Vector4& Vector4::operator*=(const Vector4& other) {
		v.a[0] *= other.v.a[0];
		v.a[1] *= other.v.a[1];
		v.a[2] *= other.v.a[2];
		v.a[3] *= other.v.a[3];

		return *this;
	}

	Vector4 Vector4::operator*(const Vector4& other) const {
		return Vector4(*this) *= other;
	}

	Vector4& Vector4::operator*=(const float other) {
		v.a[0] *= other;
		v.a[1] *= other;
		v.a[2] *= other;
		v.a[3] *= other;

		return *this;
	}

	Vector4 Vector4::operator*(const float other) const {
		return Vector4(*this) *= other;
	}

	Vector4& Vector4::operator/=(const Vector4& other) {
		v.a[0] /= other.v.a[0];
		v.a[1] /= other.v.a[1];
		v.a[2] /= other.v.a[2];
		v.a[3] /= other.v.a[3];

		return *this;
	}

	Vector4 Vector4::operator/(const Vector4& other) const {
		return Vector4(*this) /= other;
	}

	Vector4& Vector4::operator/=(const float other) {
		v.a[0] /= other;
		v.a[1] /= other;
		v.a[2] /= other;
		v.a[3] /= other;

		return *this;
	}

	Vector4 Vector4::operator/(const float other) const {
		return Vector4(*this) /= other;
	}

	Vector4 Vector4::operator-() const {
		return Vector4(*this) *= -1;
	}

	bool Vector4::operator==(const Vector4& other) const {
		return (
			v.a[0] == other.v.a[0] &&
			v.a[1] == other.v.a[1] &&
			v.a[2] == other.v.a[2] &&
			v.a[3] == other.v.a[3]
		);
	}

	bool Vector4::operator!=(const Vector4& other) const {
		return !(*this == other);
	}

	std::ostream& operator<<(std::ostream& out, const Vector4& vec) {
		return out << "(" << vec.v.a[0] << ", " << vec.v.a[1] << ", " << vec.v.a[2] << ", " << vec.v.a[3] << ")";
	}
}