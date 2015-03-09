#ifndef GL_H
#define GL_H

#include <iostream>

#include <GL/glew.h>

#include "../system/constants.h"
#include "../utility/vector.h"

class GL
{
	public:

						GL();
		void			reshape(int x, int y);
		const GLubyte*	getOpenGLVersion(void);
		unsigned int	getViewportWidth(void);
		unsigned int	getViewportHeight(void);

	private:

		unsigned int	mViewportWidth;
		unsigned int	mViewportHeight;
};

#endif // GL_H
