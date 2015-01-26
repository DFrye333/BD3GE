#ifndef CAMERA_H
#define CAMERA_H

#include <cmath>

#include "../utility/object.h"
#include "../utility/vector.h"

class Camera : public Object
{
	public:
				Camera(Vector3 position, Vector3 look, double lookXZAngle = 90.0, double lookYZAngle = 180.0);	// Default: position(0.0, 1.0, 50.0), look(0.0, 0.0, -5.0)
				~Camera();
		void	setLookX(double x)	{ mLook.u.g.x = x; }
		void	setLookY(double y)	{ mLook.u.g.y = y; }
		void	setLookZ(double z)	{ mLook.u.g.z = z; }
		void	setLookXZAngle(double lookXZAngle);
		void	setLookYZAngle(double lookYZAngle);
		void	setAltitudeLock(bool state)	{ mAltitudeLock = state; }
		double	getLookX(void)		{ return mLook.u.g.x; }
		double	getLookY(void)		{ return mLook.u.g.y; }
		double	getLookZ(void)		{ return mLook.u.g.z; }
		double	getLookXZAngle(void)	{ return mLookXZAngle; }
		double	getLookYZAngle(void)	{ return mLookYZAngle; }
		bool	getAltitudeLock(void)	{ return mAltitudeLock; }
		void	toggleAltitudeLock(void)	{ mAltitudeLock = !mAltitudeLock; }
		double	calcDistance(Vector3 point);	// Default: point(0.0, 0.0, 0.0)
		short	calcQuadrant(void);
	protected:
		Vector3	mLook;
		float	mLookXZAngle;
		float	mLookYZAngle;
		bool	mAltitudeLock;
};

#endif // CAMERA_H
