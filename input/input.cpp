#include "input.h"

namespace BD3GE {
	void Input::handler(BD3GE::Window::InputEvent input_event) {
		for (const auto& [key, state] : input_event.key_state_map) {
			set_key_state(key, state);

			if (state == true) {
				// TODO: Write conversion utility between key code enum and string.
				//g_log.write("'" + std::string(input_event.get_data()->first) + "' key pressed.", BD3GE::LOG_TYPE::INFO);
			} else {
				// TODO: Write conversion utility between key code enum and string.
				//g_log.write("'" + std::string(input_event.get_data()->first) + "' key released.", BD3GE::LOG_TYPE::INFO);
			}
		}
	}

	void Input::set_key_state(BD3GE::KEY_CODE key, bool state) {
		keys[key] = state;
	}

	bool Input::get_key_state(BD3GE::KEY_CODE key) {
		return keys[key];
	}

	bool Input::consume_input(BD3GE::KEY_CODE key) {
		bool key_state = keys[key];
		keys[key] = false;
		return key_state;
	}
}