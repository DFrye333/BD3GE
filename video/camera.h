#ifndef CAMERA_H
#define CAMERA_H

#include <cmath>

#include "../utility/matrix.h"
#include "../utility/object.h"
#include "../utility/vector.h"

class Camera : public Object
{
	public:

				Camera();
				~Camera();

	private:

				Vector3 mOrientation;
				Matrix4 mProjection;
};

#endif // CAMERA_H
