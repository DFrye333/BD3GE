#include "matrix.h"

namespace BD3GE {
	/*
	 *	Matrix class
	 */

	Matrix4 Matrix4::identity(void) {
		return Matrix4(
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);
	}

	Matrix4::Matrix4() {
		for (int i = 0; i < NUMBER_ELEMENTS; ++i) {
			elements[i] = 0.0f;
		}
	}

	// Constructs a matrix given an array of values.
	Matrix4::Matrix4(float* elements) {
		for (int i = 0; i < NUMBER_ELEMENTS; ++i) {
			elements[i] = elements[i];
		}
	}

	// Constructs a matrix given individual values.
	Matrix4::Matrix4(float a11, float a12, float a13, float a14,
					float a21, float a22, float a23, float a24,
					float a31, float a32, float a33, float a34,
					float a41, float a42, float a43, float a44) {
		elements[0] = a11;	elements[1] = a12;	elements[2] = a13;	elements[3] = a14;
		elements[4] = a21;	elements[5] = a22;	elements[6] = a23;	elements[7] = a24;
		elements[8] = a31;	elements[9] = a32;	elements[10] = a33;	elements[11] = a34;
		elements[12] = a41;	elements[13] = a42;	elements[14] = a43;	elements[15] = a44;
	}

	Matrix4::Matrix4(const Matrix4& source) {
		*this = source;
	}

	void Matrix4::to_float_array(float* float_array) const {
		for (int i = 0; i < NUMBER_ELEMENTS; ++i) {
			float_array[i] = (float)elements[i];
		}
	}

	void Matrix4::print(void) const {
		float matrix_array[16];
		to_float_array(matrix_array);
		std::cout << "Printing matrix: ";
		for (unsigned int i = 0; i < 16; ++i) {
			if (i % 4 == 0) {
				std::cout << std::endl;
			}

			std::cout << matrix_array[i] << "\t";
		}
		std::cout << std::endl;
	}

	const Matrix4 Matrix4::inverse(void) const {
		// If determinant is zero, the matrix is not invertible. In that case, the original matrix is returned.
		if (compute_determinant() == 0) {
			return *this;
		}

		Matrix4 input_matrix(*this);
		Matrix4 inverse_matrix = Matrix4::identity();

		// For each column i, zero the entire i-th column beneath row i.
		for (unsigned short i = 0; i < NUMBER_COLUMNS; ++i) {
			// If (i, i) is zero, try to swap rows.
			float i_i = input_matrix(i, i);
			if (i_i == 0.0f) {
				for (unsigned short l = i; l < NUMBER_ROWS; ++l) {
					// If a suitable row has been found to swap with row i, swap rows.
					if (input_matrix(i, l) != 0.0f) {
						input_matrix.row_swap(i, l);
						inverse_matrix.row_swap(i, l);

						// Use the new (i, i) in the remaining calculations.
						i_i = input_matrix(i, i);

						break;
					}
				}
			}

			// Zero the i-th element in the j-th row.
			for (unsigned short j = 0; j < NUMBER_ROWS; ++j) {
				if (j == i) {
					continue;
				}

				// If the current target (i, j) is already zero, move on to the next row rather than dividing by zero.
				float i_j = input_matrix(i, j);
				if (i_j == 0.0f) {
					continue;
				}

				// The cancellation factor is the number -(i, i) / (i, j) that, when multiplied by the current target (i, j), yields -(i, i), allowing for easy zeroing.
				float cancellation_factor =  -1.0f * (i_i / i_j);

				// Update the current element by multiplying it with the cancellation factor.
				input_matrix.row_multiply(j, cancellation_factor);
				inverse_matrix.row_multiply(j, cancellation_factor);

				// Add the corresponding row elements together.
				input_matrix.row_add(j, i, 1);
				inverse_matrix.row_add(j, i, 1);
			}
		}

		// Divide all rows of matrix by their diagonal elements so that the input matrix is the identity, and the inverse matrix contains the final inverse.
		for (unsigned short i = 0; i < NUMBER_COLUMNS; ++i) {
			float diagonal_element = input_matrix(i, i);
			input_matrix.row_multiply(i, 1.0f / diagonal_element);
			inverse_matrix.row_multiply(i, 1.0f / diagonal_element);
		}

		return inverse_matrix;
	}

	// Computes the determinant by row-reducing the matrix to lower-triangular form and using the resulting determinant to compute the actual determinant (keeping track of row operations and their effects).
	const float Matrix4::compute_determinant(void) const {
		Matrix4 determinant_matrix(*this);
		float determinant_modifier = 1.0f;

		// For each column i, zero the entire i-th column beneath row i.
		for (unsigned short i = 0; i < NUMBER_COLUMNS; ++i) {
			// If (i, i) is zero, try to swap rows.
			float i_i = determinant_matrix(i, i);
			if (i_i == 0.0f) {
				for (unsigned short l = i; l < NUMBER_ROWS; ++l) {
					// If a suitable row has been found to swap with row i, swap rows.
					if (determinant_matrix(i, l) != 0.0f) {
						determinant_matrix.row_swap(i, l);

						// Keep track of each row-swap made, as it affects the final determinant.
						determinant_modifier *= -1.0f;

						// Use the new (i, i) in the remaining calculations.
						i_i = determinant_matrix(i, i);

						break;
					}
				}
			}

			// Zero the i-th element in the j-th row.
			for (unsigned short j = i + 1; j < NUMBER_ROWS; ++j) {
				// If the current target (i, j) is already zero, move on to the next row rather than dividing by zero.
				float i_j = determinant_matrix(i, j);
				if (i_j == 0.0f) {
					continue;
				}

				// The cancellation factor is the number -(i, i) / (i, j) that, when multiplied by the current target (i, j), yields -(i, i), allowing for easy zeroing.
				float cancellation_factor =  -1.0f * (i_i / i_j);

				// Update the current element by multiplying it with the cancellation factor.
				determinant_matrix.row_multiply(j, cancellation_factor);

				// Add the corresponding row elements together.
				determinant_matrix.row_add(j, i, 1);

				// Keep track of each row-multiply made, as it affects the final determinant.
				determinant_modifier *= cancellation_factor;
			}
		}

		// Compute the determinant of the modified matrix.
		float determinant_temporary = 1.0f;
		for (unsigned short i = 0; i < NUMBER_ROWS; ++i) {
			determinant_temporary *= determinant_matrix(i, i);
		}

		// Return the determinant of the original matrix by dividing accounting for effects of all row operations.
		return determinant_temporary / determinant_modifier;
	}

	void Matrix4::row_add(unsigned short row_destination, unsigned short row_source, float multiplier) {
		for (unsigned short column = 0; column < NUMBER_COLUMNS; ++column) {
			(*this)(column, row_destination, (((*this)(column, row_destination)) + (multiplier * ((*this)(column, row_source)))));
		}
	}

	void Matrix4::row_multiply(unsigned short row, float multiplier) {
		for (unsigned short column = 0; column < NUMBER_COLUMNS; ++column) {
			(*this)(column, row, (multiplier * ((*this)(column, row))));
		}
	}

	void Matrix4::row_swap(unsigned short row_1, unsigned short row_2) {
		for (unsigned short column = 0; column < NUMBER_COLUMNS; ++column) {
			float temporary = (*this)(column, row_1);
			(*this)(column, row_1, ((*this)(column, row_2)));
			(*this)(column, row_2, temporary);
		}
	}

	// Returns the matrix element mapped to by the 0-based subscripts "i" and "j". Row-major order.
	const float Matrix4::operator()(unsigned short i, unsigned short j) const {
		return elements[i + (4 * j)];
	}

	// Set the matrix element mapped to by the 0-based subscripts "i" and "j" to the input "value". Row-major order.
	void Matrix4::operator()(unsigned short i, unsigned short j, float value) {
		elements[i + (4 * j)] = value;
	}

	const Matrix4& Matrix4::operator=(const Matrix4& other) {
		for (int i = 0; i < NUMBER_ELEMENTS; ++i) {
			elements[i] = other.elements[i];
		}

		return *this;
	}

	const Matrix4& Matrix4::operator+=(const Matrix4& other) {
		for (unsigned short i = 0; i < NUMBER_ELEMENTS; ++i) {
			this->elements[i] += other.elements[i];
		}

		return *this;
	}

	const Matrix4 Matrix4::operator+(const Matrix4& other) const {
		return Matrix4(*this) += other;
	}

	const Matrix4& Matrix4::operator*=(const Matrix4& other) {
		Matrix4 temporary;

		for (unsigned short this_row = 0; this_row < NUMBER_ROWS; ++this_row) {
			for (unsigned short other_column = 0; other_column < NUMBER_COLUMNS; ++other_column) {
				float new_value = 0.0f;

				for (unsigned short element = 0; element < NUMBER_ROWS; ++element) {
					new_value += (*this)(element, this_row) * other(other_column, element);
				}

				temporary(other_column, this_row, new_value);
			}
		}

		(*this) = temporary;

		return *this;
	}

	const Matrix4 Matrix4::operator*(const Matrix4& other) const {
		return Matrix4(*this) *= other;
	}

	bool operator==(const Matrix4& lhs, const Matrix4& rhs) {
		for (unsigned short i = 0; i < Matrix4::NUMBER_ELEMENTS; ++i) {
			if ((lhs.elements[i] - rhs.elements[i]) > Matrix4::EPSILON) {
				return false;
			}
		}

		return true;
	}

	bool operator!=(const Matrix4& lhs, const Matrix4& rhs) {
		return !(lhs == rhs);
	}
}