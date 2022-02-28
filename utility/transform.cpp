#include "transform.h"

namespace BD3GE {
	/*
	 *	Transform class
	 */

	Transform::Transform() {
		this->matrix = Matrix4::identity();
	}

	Transform::Transform(const Matrix4& matrix) {
		this->matrix = matrix;
	}

	Transform::Transform(const Transform& other) {
		this->matrix = other.get_matrix();
	}

	Transform::~Transform() {}

	void Transform::set_position(Vector3 position) {
		this->matrix(3, 0, position.v.g.x);
		this->matrix(3, 1, position.v.g.y);
		this->matrix(3, 2, position.v.g.z);
	}

	void Transform::set_scale_uniform(float scaler) {
		this->matrix(0, 0, scaler);
		this->matrix(1, 1, scaler);
		this->matrix(2, 2, scaler);
	}

	void Transform::set_scale(Vector3 scaler) {
		this->matrix(0, 0, scaler.v.g.x);
		this->matrix(1, 1, scaler.v.g.y);
		this->matrix(2, 2, scaler.v.g.z);
	}

	void Transform::set_orientation(Vector3 orientation) {
		set_orientation_x(orientation.v.g.x);
		set_orientation_y(orientation.v.g.y);
		set_orientation_z(orientation.v.g.z);
	}

	void Transform::set_orientation_x(float angle) {
		this->matrix(1, 1, cos(angle));
		this->matrix(1, 2, -sin(angle));
		this->matrix(2, 1, sin(angle));
		this->matrix(2, 2, cos(angle));
	}

	void Transform::set_orientation_y(float angle) {
		this->matrix(0, 0, cos(angle));
		this->matrix(0, 2, sin(angle));
		this->matrix(2, 0, -sin(angle));
		this->matrix(2, 2, cos(angle));
	}

	void Transform::set_orientation_z(float angle) {
		this->matrix(0, 0, cos(angle));
		this->matrix(0, 1, -sin(angle));
		this->matrix(1, 0, sin(angle));
		this->matrix(1, 1, cos(angle));
	}

	void Transform::translate(Vector3 translation) {
		this->matrix += Matrix4(
			0, 0, 0, translation.v.g.x,
			0, 0, 0, translation.v.g.y,
			0, 0, 0, translation.v.g.z,
			0, 0, 0, 0
		);
	}

	void Transform::rotate(Vector3 angle) {
		rotate_z(angle.v.g.z);
		rotate_y(angle.v.g.y);
		rotate_x(angle.v.g.x);
	}

	void Transform::rotate_x(float angle) {
		this->matrix *= Matrix4(
			1,	0,			0,				0,
			0,	cos(angle),	-(sin(angle)),	0,
			0,	sin(angle),	cos(angle),		0,
			0,	0,			0,				1
		);
	}

	void Transform::rotate_y(float angle) {
		this->matrix *= Matrix4(
			cos(angle),		0,		sin(angle),	0,
			0,				1,		0,			0,
			-(sin(angle)),	0,		cos(angle),	0,
			0,				0,		0,			1
		);
	}

	void Transform::rotate_z(float angle) {
		this->matrix *= Matrix4(
			cos(angle),	-(sin(angle)),	0,	0,
			sin(angle),	cos(angle),		0,	0,
			0,			0,				1,	0,
			0,			0,				0,	1
		);
	}

	void Transform::to_float_array(float* float_array) const {
		this->matrix.to_float_array(float_array);
	}

	Transform Transform::inverse(void) const {
		return Transform(this->matrix.inverse());
	}

	Matrix4 Transform::get_matrix(void) const {
		return this->matrix;
	}
	
	Vector3 Transform::get_position() const {
		Matrix4 matrix = get_matrix();
		return Vector3(matrix(3, 0), matrix(3, 1), matrix(3, 2));
	}

	const float Transform::operator()(unsigned short i, unsigned short j) const {
		return this->matrix(i, j);
	}

	void Transform::operator()(unsigned short i, unsigned short j, float value) {
		this->matrix(i, j, value);
	}

	const Transform& Transform::operator=(const Transform& other) {
		this->matrix = other.get_matrix();

		return *this;
	}

	const Transform& Transform::operator*=(const Transform& other) {
		this->matrix *= other.get_matrix();

		return *this;
	}

	const Transform Transform::operator*(const Transform& other) const {
		return Transform(this->matrix * other.get_matrix());
	}

	bool operator==(const Transform& lhs, const Transform& rhs) {
		return lhs.matrix == rhs.matrix;
	}

	bool operator!=(const Transform& lhs, const Transform& rhs) {
		return !(lhs == rhs);
	}
}