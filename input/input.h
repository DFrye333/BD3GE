#ifndef BD3GE_INPUT_H
#define BD3GE_INPUT_H

#include <iostream>
#include <cstring>
#include <map>
#include <utility>

#include "../system/constants.h"
#include "../system/globals.h"
#include "../system/window.h"
#include "../utility/message.h"

namespace BD3GE {
	class Input {
		public:

			void					handle(const BD3GE::Window::InputEvent input_event);
			bool					get_key_state(BD3GE::KEY_CODE key);
			bool					consume_key_input(BD3GE::KEY_CODE key);
			std::pair<short, short>	get_current_mouse_position();
			std::pair<short, short>	get_previous_mouse_position();

			bool is_mouse_position_fresh;

		protected:

			void					record_key_state(BD3GE::KEY_CODE key, bool state);
			void					record_mouse_position(std::pair<short, short> mouse_position);

			std::map<KEY_CODE, bool> keys;
			std::pair<short, short> current_mouse_position;
			std::pair<short, short> previous_mouse_position;
	};
}

#endif // BD3GE_INPUT_H
