#ifndef BD3GE_INPUT_H
#define BD3GE_INPUT_H

#include <iostream>
#include <cstring>
#include <map>

#include "../system/constants.h"
#include "../system/globals.h"
#include "../system/window.h"
#include "../utility/message.h"

namespace BD3GE {
	class Input {
		public:

			void	handler(BD3GE::Window::InputEvent input_event);
			void	set_key_state(BD3GE::KEY_CODE key, bool state);
			bool	get_key_state(BD3GE::KEY_CODE key);

		protected:

			std::map<BD3GE::KEY_CODE, bool>	m_keys;
	};
}

#endif // BD3GE_INPUT_H
