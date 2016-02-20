#ifndef GL_H
#define GL_H

#include <iostream>

#include <GL/glew.h>

#include "../system/constants.h"
#include "../utility/vector.h"

namespace BD3GE
{
	class GL
	{
		public:

							GL();
			void			reshape(int x, int y);
			const GLubyte*	get_openGL_version(void);
			unsigned int	get_viewport_width(void);
			unsigned int	get_viewport_height(void);

		private:

			unsigned int	m_viewport_width;
			unsigned int	m_viewport_height;
	};
}

#endif // GL_H
