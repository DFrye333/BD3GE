#include "input.h"

namespace BD3GE {
	Input::Input() : is_mouse_position_fresh(false) {}

	Input::Input(std::vector<Gamepad*> gamepads) : Input() {
		for (unsigned short i = 0; i < gamepads.size() && i < Gamepad::MAX_QUANTITY_GAMEPADS; ++i) {
			this->gamepads[i] = gamepads[i];
		}
	}

	Input::~Input() {
		for (auto& [gamepad_index, gamepad] : gamepads) {
			delete gamepad;
			gamepad = nullptr;
		}
	}

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
					gamepad_inputs[input_event.index][input_code] = state;
				}
				for (const auto& [input_code, value] : input_event.analogs) {
					gamepad_inputs[input_event.index][input_code] = value;
				}
				break;
			case Gamepad::CONNECTION_STATE::DISCONNECTED:
				gamepad_inputs.erase(input_event.index);
				break;
		}
	}

	void Input::update() {
		for (const auto& [gamepad_index, gamepad] : gamepads) {
			Message<Gamepad::InputEvent> gamepad_input_message = gamepad->pull_input_message();
			if (gamepad_input_message.get_data() != nullptr) {
				handle(Gamepad::InputEvent(*(gamepad_input_message.get_data())));
			}
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

	short Input::get_quantity_gamepads_connected() {
		short quantity_gamepads_connected = 0;

		for (const auto& [gamepad_index, gamepad] : gamepads) {
			quantity_gamepads_connected += (gamepad->connection_state == Gamepad::CONNECTION_STATE::CONNECTED);
		}

		return quantity_gamepads_connected;
	}

	bool Input::check_is_gamepad_connected(short gamepad_index) {
		return gamepads[gamepad_index]->connection_state == Gamepad::CONNECTION_STATE::CONNECTED;
	}

	short Input::get_primary_connected_gamepad_index() {
		for (short i = 0; i < Gamepad::MAX_QUANTITY_GAMEPADS; ++i) {
			if (check_is_gamepad_connected(i)) {
				return i;
			}
		}

		return -1;
	}

	float Input::get_gamepad_input_value(short gamepad_index, Gamepad::INPUT_CODE input_code) {
		return gamepad_inputs.contains(gamepad_index) ? gamepad_inputs[gamepad_index][input_code] : 0.0f;
	}

	float Input::consume_gamepad_input_value(short gamepad_index, Gamepad::INPUT_CODE input_code) {
		float value = 0.0f;
		
		if (gamepad_inputs.contains(gamepad_index)) {
			value = gamepad_inputs[gamepad_index][input_code];
			gamepad_inputs[gamepad_index][input_code] = 0.0f;
		}

		return value;
	}

	float Input::get_gamepad_output_value(short gamepad_index, Gamepad::OUTPUT_CODE output_code) {
		return gamepad_outputs.contains(gamepad_index) ? gamepad_outputs[gamepad_index][output_code] : 0.0f;
	}

	void Input::set_gamepad_output_value(short gamepad_index, Gamepad::OUTPUT_CODE output_code, float output_value) {
		Gamepad::OutputEvent output_event;
		output_event.index = gamepad_index;
		output_event.analogs[output_code] = gamepad_outputs[gamepad_index][output_code] = output_value;
		gamepads[gamepad_index]->push_output_message(Message<Gamepad::OutputEvent>(output_event));
	}
}