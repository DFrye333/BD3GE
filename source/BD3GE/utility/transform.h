#ifndef BD3GE_TRANSFORM_H
#define BD3GE_TRANSFORM_H

#include <cmath>

#include "../utility/matrix.h"
#include "../utility/quaternion.h"
#include "../utility/vector.h"

namespace BD3GE {
	class BD3GE_API Transform {
		public:

								Transform();
								explicit Transform(const Matrix4& matrix);
								Transform(const Vector3& position);
								Transform(const Vector3& position, const Vector3& orientation);
								Transform(const Vector3& position, const Quaternion& orientation);
								Transform(const Vector3& position, const Vector3& orientation, const Vector3& scale);
								Transform(const Vector3& position, const Quaternion& orientation, const Vector3& scale);
								~Transform();
			Vector3				get_position() const;
			Quaternion			get_orientation() const;
			Vector3				get_scale() const;
			Matrix4&			get_matrix();
			void 				set_position(const Vector3 position);
			void				set_orientation(float angle, Vector3 axis);
			void				set_orientation(const Vector3 orientation);
			void				set_orientation(const Quaternion& orientation);
			void				set_orientation_x(float orientation);
			void				set_orientation_y(float orientation);
			void				set_orientation_z(float orientation);
			void				set_scale(Vector3 scale);
			void				set_scale_uniform(float scale);
			void				translate(Vector3 translation);
			void				rotate(Quaternion rotation);
			void				rotate(float angle, Vector3 axis);
			void				rotate(Vector3 euler);
			void				rotate_x(float angle);
			void				rotate_y(float angle);
			void				rotate_z(float angle);
			void 				to_float_array(float* float_array);
			Transform 			inverse();
			Vector3				get_forward();
			void 				print();
			const Transform& 	operator=(const Transform& other);
			const Transform& 	operator*=(const Transform& other);
			const Transform 	operator*(const Transform& other) const;
			friend bool			operator==(const Transform& lhs, const Transform& rhs);
			friend bool			operator!=(const Transform& lhs, const Transform& rhs);

		//private:

			void				recalculate_matrix();
			void				decompose_matrix();

			Matrix4 matrix;
			Quaternion orientation;
			Vector3 position;
			Vector3 scale;
			bool is_matrix_dirty = true;
	};

	struct TransformNode {
		TransformNode* parent;
		Transform transform;
	};
}

#endif // BD3GE_TRANSFORM_H