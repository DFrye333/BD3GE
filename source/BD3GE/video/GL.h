#ifndef BD3GE_GL_H
#define BD3GE_GL_H

#include <iostream>
#include <map>

#include <glew/GL/glew.h>

#include "../management/texture_manager.h"
#include "../system/constants.h"
#include "../system/globals.h"
#include "../utility/color.h"
#include "../utility/log.h"
#include "../video/renderable.h"

namespace BD3GE {
	class GL {
		public:

							GL();
							~GL();
			void			create_buffers(unsigned int buffers_quantity);
			void			delete_buffers();
			void			setup_vaos(std::vector<RenderableUnit*> renderable_units);
			void			setup_vao(RenderableUnit* renderable_unit);
			void			create_texture_handle(unsigned int* texture_handle);
			void			initialize_texture(size_t texture_id);
			void			enable_texture(size_t texture_id, unsigned int index);
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
			std::map<const size_t, unsigned int> texture_id_to_handle;
			GLuint* vao_handles;
			GLuint* vbo_handles;
			GLuint* ibo_handles;
			unsigned int buffers_quantity;
			unsigned int renderables_quantity;
	};
}

#endif // BD3GE_GL_H
