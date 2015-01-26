#include "camera.h"

/*
 *	Camera Class
 */
Camera::Camera(Vector3 position, Vector3 look, double lookXZAngle, double lookYZAngle)
{
	mPos.u.g.x = position.u.g.x;
	mPos.u.g.y = position.u.g.y;
	mPos.u.g.z = position.u.g.z;
	mLook.u.g.x = look.u.g.x;
	mLook.u.g.y = look.u.g.y;
	mLook.u.g.z = look.u.g.z;
	mLookXZAngle = lookXZAngle;
	mLookYZAngle = lookYZAngle;
	mAltitudeLock = true;
}

Camera::~Camera()
{
}

void Camera::setLookXZAngle(double lookXZAngle)
{
	if(0 > lookXZAngle)
	{
		lookXZAngle += 360;
	}
	else if(360 < lookXZAngle)
	{
		lookXZAngle -= 360;
	}
	mLookXZAngle = lookXZAngle;
}

void Camera::setLookYZAngle(double lookYZAngle)
{
	if(0 > lookYZAngle)
	{
		lookYZAngle += 360;
	}
	else if(360 < lookYZAngle)
	{
		lookYZAngle -= 360;
	}
	mLookYZAngle = lookYZAngle;
}

double Camera::calcDistance(Vector3 point)
{
	return sqrt(pow(mPos.u.g.x - point.u.g.x, 2) + pow(mPos.u.g.y - point.u.g.y, 2) + pow(mPos.u.g.z - point.u.g.z, 2));
}

short	Camera::calcQuadrant(void)
{
	if(mPos.u.g.x >= 0 && mPos.u.g.z >= 0)		// Quadrant I
	{
		return 1;
	}
	else if(mPos.u.g.x < 0 && mPos.u.g.z >= 0)	// Quadrant II
	{
		return 2;
	}
	else if(mPos.u.g.x <= 0 && mPos.u.g.z < 0)	// Quadrant III
	{
		return 3;
	}
	else if(mPos.u.g.x > 0 && mPos.u.g.z <= 0)	// Quadrant IV
	{
		return 4;
	}
	else
	{
		return 0;
	}
}
