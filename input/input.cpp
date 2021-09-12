#include "input.h"

namespace BD3GE {
	void Input::handle(const BD3GE::Window::InputEvent* const input_event) {
		for (const auto& [key, state] : input_event->key_state_map) {
			record_key_state(key, state);
		}
		record_mouse_position(input_event->mouse_position);
	}

	bool Input::get_key_state(BD3GE::KEY_CODE key) {
		return keys[key];
	}

	bool Input::consume_key_input(BD3GE::KEY_CODE key) {
		bool key_state = keys[key];
		keys[key] = false;
		return key_state;
	}

	std::pair<short, short> Input::get_current_mouse_position() {
		is_mouse_position_fresh = false;
		return this->current_mouse_position;
	}

	std::pair<short, short> Input::get_previous_mouse_position() {
		return this->previous_mouse_position;
	}

	void Input::record_key_state(BD3GE::KEY_CODE key, bool state) {
		keys[key] = state;
	}

	void Input::record_mouse_position(std::pair<short, short> mouse_position) {
		is_mouse_position_fresh = true;
		this->previous_mouse_position = this->current_mouse_position;
		this->current_mouse_position = mouse_position;
	}
}