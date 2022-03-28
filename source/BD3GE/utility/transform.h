#ifndef BD3GE_TRANSFORM_H
#define BD3GE_TRANSFORM_H

#include <cmath>

#include "../utility/matrix.h"
#include "../utility/vector.h"

namespace BD3GE {
	class BD3GE_API Transform {
		public:

								Transform();
								Transform(const Matrix4& matrix);
								Transform(const Transform& other);
								Transform(const Vector3& position);
								Transform(const Vector3& position, const Vector3& orientation);
								Transform(const Vector3& position, const Vector3& orientation, const Vector3& scale);
								~Transform();
			void 				set_position(Vector3 position);
			void				set_orientation(Vector3 orientation);
			void				set_orientation_x(float orientation);
			void				set_orientation_y(float orientation);
			void				set_orientation_z(float orientation);
			void				set_scale_uniform(float scaler);
			void				set_scale(Vector3 scaler);
			void				translate(Vector3 translation);
			void				rotate(Vector3 angle);
			void				rotate_x(float angle);
			void				rotate_y(float angle);
			void				rotate_z(float angle);
			void 				to_float_array(float* float_array) const;
			Transform 			inverse(void) const;
			Matrix4				get_matrix(void) const;
			Vector3				get_position() const;
			const float 		operator()(unsigned short i, unsigned short j) const;
			void 				operator()(unsigned short i, unsigned short j, float value);
			const Transform& 	operator=(const Transform& other);
			const Transform& 	operator*=(const Transform& other);
			const Transform 	operator*(const Transform& other) const;
			friend bool			operator==(const Transform& lhs, const Transform& rhs);
			friend bool			operator!=(const Transform& lhs, const Transform& rhs);

		private:

			Matrix4 matrix;
	};

	struct TransformNode {
		TransformNode* parent;
		Transform transform;
	};
}

#endif // BD3GE_TRANSFORM_H