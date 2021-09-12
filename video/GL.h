#ifndef BD3GE_GL_H
#define BD3GE_GL_H

#include <iostream>

#include <GL/glew.h>

#include "../system/constants.h"
#include "../utility/vector.h"

namespace BD3GE {
	class GL {
		public:

							GL();
			void			reshape(int x, int y);
			const void		print_info();
			const GLubyte*	get_vendor();
			const GLubyte*	get_renderer();
			const GLubyte*	get_version();
			const GLubyte*	get_shading_language_version();
			unsigned int	get_viewport_width();
			unsigned int	get_viewport_height();

		private:

			unsigned int	viewport_width;
			unsigned int	viewport_height;
	};
}

#endif // BD3GE_GL_H
