#ifndef BD3GE_MATRIX_H
#define BD3GE_MATRIX_H

#include <iostream>

namespace BD3GE {
	class Matrix4 {
		public:

			static Matrix4 identity(void);

							Matrix4();
							Matrix4(float* elements);
							Matrix4(float a11, float a12, float a13, float a14,
									float a21, float a22, float a23, float a24,
									float a31, float a32, float a33, float a34,
									float a41, float a42, float a43, float a44);
							Matrix4(const Matrix4& source);
			void 			to_float_array(float* float_array) const;
			void 			print(void) const;
			const 			Matrix4 inverse(void) const;
			void 			row_add(unsigned short row_destination, unsigned short row_source, float multiplier);
			void 			row_multiply(unsigned short row, float multipler);
			void 			row_swap(unsigned short row_1, unsigned short row_2);
			const 			float operator()(unsigned short i, unsigned short j) const;
			void 			operator()(unsigned short i, unsigned short j, float value);
			const Matrix4& 	operator=(const Matrix4& other);
			const Matrix4& 	operator*=(const Matrix4& other);
			const Matrix4 	operator*(const Matrix4& other) const;

		private:

			const float compute_determinant(void) const;

			static const short NUMBER_ROWS = 4;
			static const short NUMBER_COLUMNS = 4;
			static const short NUMBER_ELEMENTS = NUMBER_ROWS * NUMBER_COLUMNS;

			float elements[NUMBER_ELEMENTS];
	};
}

#endif // BD3GE_MATRIX_H