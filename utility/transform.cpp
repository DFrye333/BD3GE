#include "transform.h"

namespace BD3GE {
	/*
	 *	Transform class
	 */

	Transform::Transform() {
		this->matrix = Matrix4::identity();
	}

	Transform::Transform(Matrix4 matrix) {
		this->matrix = matrix;
	}

	Transform::~Transform() {}

	void Transform::translate(Vector3 translation) {
		this->matrix(3, 0, translation.v.g.x);
		this->matrix(3, 1, translation.v.g.y);
		this->matrix(3, 2, translation.v.g.z);
	}

	void Transform::scale(float scaler) {
		this->matrix(0, 0, scaler);
		this->matrix(1, 1, scaler);
		this->matrix(2, 2, scaler);
	}

	void Transform::scale(Vector3 scaler) {
		this->matrix(0, 0, scaler.v.g.x);
		this->matrix(0, 0, scaler.v.g.y);
		this->matrix(0, 0, scaler.v.g.z);
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
}