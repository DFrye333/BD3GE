#include "transform.h"

namespace BD3GE {
	Transform::Transform() : scale(Vector3(1, 1, 1)), matrix(Matrix4::identity()), is_matrix_dirty(true), are_components_dirty(false) {}

	Transform::Transform(const Matrix4& matrix) : matrix(matrix) {
		decompose_matrix();
	}

	Transform::Transform(const Vector3& position) : Transform() {
		set_position(position);
	}

	Transform::Transform(const Vector3& position, const Vector3& orientation) : Transform(position) {
		set_orientation(orientation);
	}

	Transform::Transform(const Vector3& position, const Quaternion& orientation) : Transform(position) {
		set_orientation(orientation);
	}

	Transform::Transform(const Vector3& position, const Vector3& orientation, const Vector3& scale) : Transform(position, orientation) {
		set_scale(scale);
	}

	Transform::Transform(const Vector3& position, const Quaternion& orientation, const Vector3& scale) : Transform(position, orientation) {
		set_scale(scale);
	}

	Vector3 Transform::get_position() {
		if (this->are_components_dirty) {
			decompose_matrix();
		}

		return this->position;
	}

	Quaternion Transform::get_orientation() {
		if (this->are_components_dirty) {
			decompose_matrix();
		}

		return this->orientation;
	}

	Vector3 Transform::get_scale() {
		if (this->are_components_dirty) {
			decompose_matrix();
		}

		return this->scale;
	}

	Matrix4& Transform::get_matrix() {
		if (this->is_matrix_dirty) {
			recalculate_matrix();
		}

		return this->matrix;
	}

	void Transform::set_position(const Vector3 position) {
		this->position = position;

		this->is_matrix_dirty = true;
	}

	void Transform::set_orientation(float angle, Vector3 axis) {
		set_orientation(Quaternion(angle, axis));
	}

	void Transform::set_orientation(const Vector3 orientation) {
		set_orientation(Quaternion(orientation));
	}

	void Transform::set_orientation(const Quaternion& orientation) {
		this->orientation = orientation;

		this->is_matrix_dirty = true;
	}

	void Transform::set_orientation_x(float angle) {
		set_orientation(Vector3(angle, 0, 0));
	}

	void Transform::set_orientation_y(float angle) {
		set_orientation(Vector3(0, angle, 0));
	}

	void Transform::set_orientation_z(float angle) {
		set_orientation(Vector3(0, 0, angle));
	}

	void Transform::set_scale(Vector3 scale) {
		this->scale = scale;

		this->is_matrix_dirty = true;
	}

	void Transform::set_scale_uniform(float scale) {
		set_scale(Vector3(scale, scale, scale));
	}

	void Transform::translate(Vector3 translation) {
		set_position(get_position() + translation);
	}

	void Transform::rotate(Quaternion rotation) {
		this->orientation = rotation * get_orientation();

		this->is_matrix_dirty = true;
	}

	void Transform::rotate(float angle, Vector3 axis) {
		rotate(Quaternion(cos(angle / 2), axis.get_normalized() * sin(angle / 2)));
	}

	void Transform::rotate(Vector3 euler) {
		rotate(Quaternion(euler));
	}

	void Transform::rotate_x(float angle) {
		rotate(angle, Vector3(1, 0, 0));
	}

	void Transform::rotate_y(float angle) {
		rotate(angle, Vector3(0, 1, 0));
	}

	void Transform::rotate_z(float angle) {
		rotate(angle, Vector3(0, 0, 1));
	}

	void Transform::to_float_array(float* float_array) {
		get_matrix().to_float_array(float_array);
	}

	Transform Transform::inverse() {
		return Transform(get_matrix().inverse());
	}

	Vector3 Transform::get_forward() {
		Matrix4& matrix = get_matrix();
		return -Vector3(
			matrix(2, 0),
			matrix(2, 1),
			matrix(2, 2)
		).normalize();
	}

	Vector3 Transform::get_right() {
		Matrix4& matrix = get_matrix();
		return -Vector3(
			matrix(0, 0),
			matrix(0, 1),
			matrix(0, 2)
		).normalize();
	}

	Vector3 Transform::get_up() {
		Matrix4& matrix = get_matrix();
		return -Vector3(
			matrix(1, 0),
			matrix(1, 1),
			matrix(1, 2)
		).normalize();
	}

	void Transform::set_forward(Vector3 forward) {
		Matrix4& matrix = get_matrix();
		matrix(2, 0, forward.v.g.x);
		matrix(2, 1, forward.v.g.y);
		matrix(2, 2, forward.v.g.z);
		
		this->are_components_dirty = true;
	}

	void Transform::set_right(Vector3 left) {
		Matrix4& matrix = get_matrix();
		matrix(0, 0, left.v.g.x);
		matrix(0, 1, left.v.g.y);
		matrix(0, 2, left.v.g.z);
		
		this->are_components_dirty = true;
	}

	void Transform::set_up(Vector3 up) {
		Matrix4& matrix = get_matrix();
		matrix(1, 0, up.v.g.x);
		matrix(1, 1, up.v.g.y);
		matrix(1, 2, up.v.g.z);
		
		this->are_components_dirty = true;
	}

	void Transform::print() {
		get_matrix().print();
	}

	const Transform& Transform::operator=(const Transform& other) {
		Transform other_copy = Transform(other);

		set_position(other_copy.get_position());
		set_orientation(other_copy.get_orientation());
		set_scale(other_copy.get_scale());

		return *this;
	}

	Transform Transform::operator*(const Transform& other) {
		return Transform(get_matrix() * Transform(other).get_matrix());
	}

	bool operator==(const Transform& lhs, const Transform& rhs) {
		return Transform(lhs).get_matrix() == Transform(rhs).get_matrix();
	}

	bool operator!=(const Transform& lhs, const Transform& rhs) {
		return !(lhs == rhs);
	}

	void Transform::recalculate_matrix() {
		Vector3 scale = get_scale();
		this->matrix = Matrix4(
			scale.v.g.x, 0, 0, 0,
			0, scale.v.g.y, 0, 0,
			0, 0, scale.v.g.z, 0,
			0, 0, 0, 1
		);

		Matrix4 rotation = get_orientation().get_rotation_matrix();
		this->matrix = rotation * this->matrix;

		Vector3 position = get_position();
		this->matrix(3, 0, position.v.g.x);
		this->matrix(3, 1, position.v.g.y);
		this->matrix(3, 2, position.v.g.z);

		this->is_matrix_dirty = false;
	}

	void Transform::decompose_matrix() {
		this->position = Vector3(this->matrix(3, 0), this->matrix(3, 1), this->matrix(3, 2));
		this->scale = Vector3(
			Vector3(this->matrix(0, 0), this->matrix(0, 1), this->matrix(0, 2)).get_magnitude(),
			Vector3(this->matrix(1, 0), this->matrix(1, 1), this->matrix(1, 2)).get_magnitude(),
			Vector3(this->matrix(2, 0), this->matrix(2, 1), this->matrix(2, 2)).get_magnitude()
		);
		this->orientation = Quaternion(Matrix4(
			this->matrix(0, 0) / this->scale.v.g.x, this->matrix(1, 0) / this->scale.v.g.y, this->matrix(2, 0) / this->scale.v.g.z, 0,
			this->matrix(0, 1) / this->scale.v.g.x, this->matrix(1, 1) / this->scale.v.g.y, this->matrix(2, 1) / this->scale.v.g.z, 0,
			this->matrix(0, 2) / this->scale.v.g.x, this->matrix(1, 2) / this->scale.v.g.y, this->matrix(2, 2) / this->scale.v.g.z, 0,
			0, 0, 0, 1
		));

		this->are_components_dirty = false;
	}
}