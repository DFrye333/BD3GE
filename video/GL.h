#ifndef GL_H
#define GL_H

#include "../utility/object.h"

// Forward declaration.
class Cube;

class GL
{
	public:

		void			init(void);
		void			reshape(int x, int y);
		void			render(Cube** cubettes);
		const GLubyte*	getOpenGLVersion(void);
		unsigned int	getViewportWidth(void);
		unsigned int	getViewportHeight(void);

	private:

		unsigned int	mViewportWidth;
		unsigned int	mViewportHeight;
};

#endif // GL_H
