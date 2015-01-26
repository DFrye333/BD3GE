#include "vector.h"

/*
 * 	Vector3 class
 */

Vector3::Vector3(void)
{
	u.a[0] = 0.0;
	u.a[1] = 0.0;
	u.a[2] = 0.0;
}

Vector3::Vector3(const double x, const double y, const double z)
{
	u.g.x = x;
	u.g.y = y;
	u.g.z = z;
}

Vector3::Vector3(const double a[3])
{
	u.a[0] = a[0];
	u.a[1] = a[1];
	u.a[2] = a[2];
}

Vector3::Vector3(const Vector3& v)
{
	u.a[0] = v.u.a[0];
	u.a[1] = v.u.a[1];
	u.a[2] = v.u.a[2];
}

Vector3& Vector3::operator+=(const Vector3& v)
{
	u.a[0] += v.u.a[0];
	u.a[1] += v.u.a[1];
	u.a[2] += v.u.a[2];

	return *this;
}

Vector3& Vector3::operator+(const Vector3& v)
{
	return Vector3(*this) += v;
}

Vector3& Vector3::operator*=(const Vector3& v)
{
	u.a[0] *= v.u.a[0];
	u.a[1] *= v.u.a[1];
	u.a[2] *= v.u.a[2];

	return *this;
}

Vector3& Vector3::operator*(const Vector3& v)
{
	return Vector3(*this) *= v;
}

Vector3& Vector3::operator*=(const double s)
{
	u.a[0] *= s;
	u.a[1] *= s;
	u.a[2] *= s;

	return *this;
}

Vector3& Vector3::operator*(const double s)
{
	return Vector3(*this) *= s;
}
