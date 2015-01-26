#ifndef MATRIX_H
#define MATRIX_H

class Matrix4
{
	public:

		Matrix4();
		Matrix4(double* elements);
		Matrix4(double a11, double a12, double a13, double a14,
				double a21, double a22, double a23, double a24,
				double a31, double a32, double a33, double a34,
				double a41, double a42, double a43, double a44);
		const double operator()(unsigned short i, unsigned short j);
		void operator()(unsigned short i, unsigned short j, double value);
		void toFloatArray(float* floatArray);
		const Matrix4 inverse(void);

	private:

		const float determinant(void);

		double mElements[16];
		static const short m_NUMBER_ELEMENTS = 16;
};

#endif // MATRIX_H
