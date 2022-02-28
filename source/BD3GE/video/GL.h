#ifndef BD3GE_GL_H
#define BD3GE_GL_H

#include <iostream>

#include <glew/GL/glew.h>

#include "../system/constants.h"
#include "../system/globals.h"
#include "../utility/color.h"
#include "../utility/log.h"

namespace BD3GE {
	class GL {
		public:

							GL();

			void			create_texture_handle(unsigned int* texture_handle);
			void			clear_buffers();
			void			reshape_viewport(unsigned int x, unsigned int y);
			const void		print_info();
			const GLubyte*	get_vendor();
			const GLubyte*	get_renderer();
			const GLubyte*	get_version();
			const GLubyte*	get_shading_language_version();
			unsigned int	get_viewport_width();
			unsigned int	get_viewport_height();
			void			set_wireframe_mode(bool should_enable_wireframe_mode);
			void			toggle_wireframe_mode();

		private:

			unsigned int	viewport_width;
			unsigned int	viewport_height;
			bool			is_wireframe_mode_enabled;
	};
}

#endif // BD3GE_GL_H
