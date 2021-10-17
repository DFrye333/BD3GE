#include "input.h"

namespace BD3GE {
	void Input::handle(const BD3GE::Window::InputEvent input_event) {
		for (const auto& [key, state] : input_event.key_state_map) {
			record_key_state(key, state);
		}
		record_mouse_position(input_event.mouse_position);
	}

	void Input::handle(const BD3GE::Gamepad::InputEvent input_event) {
		switch (input_event.connection_state) {
			case Gamepad::CONNECTION_STATE::CONNECTED:
				for (const auto& [input_code, state] : input_event.digitals) {
					gamepads[input_event.index][input_code] = state;
				}
				for (const auto& [input_code, value] : input_event.analogs) {
					gamepads[input_event.index][input_code] = value;
				}
				break;
			case Gamepad::CONNECTION_STATE::DISCONNECTED:
				gamepads.erase(input_event.index);
				break;
		}
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

	short Input::get_quantity_gamepads_active() {
		return gamepads.size();
	}

	bool Input::check_is_gamepad_connected(short gamepad_index) {
		return gamepads.contains(gamepad_index);
	}

	float Input::get_gamepad_value(short gamepad_index, Gamepad::INPUT_CODE input_code) {
		return gamepads.contains(gamepad_index) ? gamepads[gamepad_index][input_code] : 0.0f;
	}

	float Input::consume_gamepad_value(short gamepad_index, Gamepad::INPUT_CODE input_code) {
		float value = 0.0f;
		
		if (gamepads.contains(gamepad_index)) {
			value = gamepads[gamepad_index][input_code];
			gamepads[gamepad_index][input_code] = 0.0f;
		}

		return value;
	}
}