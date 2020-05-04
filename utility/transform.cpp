#include "transform.h"

namespace BD3GE {
	/*
	 *	Transform class
	 */

	Transform::Transform() {
		this->m_matrix = Matrix4::identity();
	}

	Transform::Transform(Matrix4 matrix) {
		this->m_matrix = matrix;
	}

	Transform::~Transform() {}

	void Transform::translate(Vector3 translation) {
		this->m_matrix(3, 0, translation.v.g.x);
		this->m_matrix(3, 1, translation.v.g.y);
		this->m_matrix(3, 2, translation.v.g.z);
	}

	void Transform::scale(float scaler) {
		this->m_matrix(0, 0, scaler);
		this->m_matrix(1, 1, scaler);
		this->m_matrix(2, 2, scaler);
	}

	void Transform::scale(Vector3 scaler) {
		this->m_matrix(0, 0, scaler.v.g.x);
		this->m_matrix(0, 0, scaler.v.g.y);
		this->m_matrix(0, 0, scaler.v.g.z);
	}

	void Transform::rotate(Vector3 angle) {
		rotate_z(angle.v.g.z);
		rotate_y(angle.v.g.y);
		rotate_x(angle.v.g.x);
	}

	void Transform::rotate_x(float angle) {
		this->m_matrix *= Matrix4(
			1,	0,			0,				0,
			0,	cos(angle),	-(sin(angle)),	0,
			0,	sin(angle),	cos(angle),		0,
			0,	0,			0,				1
		);
	}

	void Transform::rotate_y(float angle) {
		this->m_matrix *= Matrix4(
			cos(angle),		0,		sin(angle),	0,
			0,				1,		0,			0,
			-(sin(angle)),	0,		cos(angle),	0,
			0,				0,		0,			1
		);
	}

	void Transform::rotate_z(float angle) {
		this->m_matrix *= Matrix4(
			cos(angle),	-(sin(angle)),	0,	0,
			sin(angle),	cos(angle),		0,	0,
			0,			0,				1,	0,
			0,			0,				0,	1
		);
	}

	void Transform::to_float_array(float* float_array) const {
		this->m_matrix.to_float_array(float_array);
	}

	Transform Transform::inverse(void) const {
		return Transform(this->m_matrix.inverse());
	}

	Matrix4 Transform::get_matrix(void) const {
		return this->m_matrix;
	}

	const float Transform::operator()(unsigned short i, unsigned short j) const {
		return this->m_matrix(i, j);
	}

	void Transform::operator()(unsigned short i, unsigned short j, float value) {
		this->m_matrix(i, j, value);
	}

	const Transform& Transform::operator=(const Transform& other) {
		this->m_matrix = other.get_matrix();

		return *this;
	}

	const Transform& Transform::operator*=(const Transform& other) {
		this->m_matrix *= other.get_matrix();

		return *this;
	}

	const Transform Transform::operator*(const Transform& other) const {
		return Transform(this->m_matrix * other.get_matrix());
	}
}