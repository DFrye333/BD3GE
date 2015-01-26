#ifndef VECTOR_H
#define VECTOR_H

class Vector3
{
	public:
		Vector3(void);
		Vector3(const double x, const double y, const double z);
		Vector3(const double a[3]);
		Vector3(const Vector3& v);
		Vector3& operator+=(const Vector3& v);
		Vector3& operator+(const Vector3& v);
		Vector3& operator*=(const Vector3& v);
		Vector3& operator*(const Vector3& v);
		Vector3& operator*=(const double s);
		Vector3& operator*(const double s);

		union // Union allows different Vector3 notation in different contexts.
		{
			struct			// Vector3 as geometry.
			{
				double x;
				double y;
				double z;
			} g;

			struct			// Vector3 as color.
			{
				double r;
				double g;
				double b;
			} c;

			double a[3];	// Vector3 as generic array.
		} u;

};

#endif // VECTOR_H
