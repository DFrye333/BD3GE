#ifndef BD3GE_MATRIX_H
#define BD3GE_MATRIX_H

#include <iostream>

#include "../system/api.h"
#include "../utility/vector.h"

namespace BD3GE {
	class Matrix4 {
		public:

			static const short NUMBER_ROWS = 4;
			static const short NUMBER_COLUMNS = 4;
			static const short NUMBER_ELEMENTS = NUMBER_ROWS * NUMBER_COLUMNS;
			// This value is as large as it is to prevent near-zero values, which cause poorly-conditioned matrices. Recall The Great Rotation Jitter of '22.
			static constexpr float EPSILON = 1.0e-3f;

			static Matrix4 identity();

							Matrix4();
							Matrix4(float* elements);
							Matrix4(float a00, float a10, float a20, float a30,
									float a01, float a11, float a21, float a31,
									float a02, float a12, float a22, float a32,
									float a03, float a13, float a23, float a33);
							Matrix4(const Matrix4& source);
			void 			to_float_array(float* float_array) const;
			void 			print() const;
			const 			Matrix4 inverse() const;
			const 			Matrix4 transpose() const;
			void 			row_add(unsigned short row_destination, unsigned short row_source, float multiplier);
			void 			row_multiply(unsigned short row, float multipler);
			void 			row_swap(unsigned short row_1, unsigned short row_2);
			const 			float operator()(unsigned short i, unsigned short j) const;
			void 			operator()(unsigned short i, unsigned short j, float value);
			const Matrix4& 	operator=(const Matrix4& other);
			const Matrix4&	operator+=(const Matrix4& other);
			const Matrix4	operator+(const Matrix4& other) const;
			const Matrix4& 	operator*=(const Matrix4& other);
			const Matrix4 	operator*(const Matrix4& other) const;
			const Vector4	operator*=(const Vector4& other) const;
			const Vector4	operator*(const Vector4& other) const;
			friend bool		operator==(const Matrix4& lhs, const Matrix4& rhs);
			friend bool		operator!=(const Matrix4& lhs, const Matrix4& rhs);

		private:

			const float compute_determinant() const;

			float elements[NUMBER_ELEMENTS];
	};
}

#endif // BD3GE_MATRIX_H