#include "input.h"

namespace BD3GE {
	std::map<int, Input::KEY_CODE> Input::key_code_map = {
		{ VK_BACK, Input::KEY_CODE::BACKSPACE },
		{ VK_TAB, Input::KEY_CODE::TAB },
		{ VK_ESCAPE, Input::KEY_CODE::ESCAPE },
		{ VK_SPACE, Input::KEY_CODE::SPACE },
		{ VK_OEM_7, Input::KEY_CODE::QUOTE },
		{ VK_OEM_COMMA, Input::KEY_CODE::COMMA },
		{ VK_OEM_MINUS, Input::KEY_CODE::MINUS },
		{ VK_OEM_PERIOD, Input::KEY_CODE::PERIOD },
		{ VK_OEM_2, Input::KEY_CODE::SLASH },
		{ 0x30, Input::KEY_CODE::NUM_0 },
		{ 0x31, Input::KEY_CODE::NUM_1 },
		{ 0x32, Input::KEY_CODE::NUM_2 },
		{ 0x33, Input::KEY_CODE::NUM_3 },
		{ 0x34, Input::KEY_CODE::NUM_4 },
		{ 0x35, Input::KEY_CODE::NUM_5 },
		{ 0x36, Input::KEY_CODE::NUM_6 },
		{ 0x37, Input::KEY_CODE::NUM_7 },
		{ 0x38, Input::KEY_CODE::NUM_8 },
		{ 0x39, Input::KEY_CODE::NUM_9 },
		{ VK_OEM_1, Input::KEY_CODE::SEMICOLON },
		{ VK_OEM_PLUS, Input::KEY_CODE::EQUAL },
		{ VK_OEM_4, Input::KEY_CODE::BRACKETLEFT },
		{ VK_OEM_5, Input::KEY_CODE::BACKSLASH },
		{ VK_OEM_6, Input::KEY_CODE::BRACKETRIGHT },
		{ VK_OEM_3, Input::KEY_CODE::GRAVE },
		{ 0x41, Input::KEY_CODE::A },
		{ 0x42, Input::KEY_CODE::B },
		{ 0x43, Input::KEY_CODE::C },
		{ 0x44, Input::KEY_CODE::D },
		{ 0x45, Input::KEY_CODE::E },
		{ 0x46, Input::KEY_CODE::F },
		{ 0x47, Input::KEY_CODE::G },
		{ 0x48, Input::KEY_CODE::H },
		{ 0x49, Input::KEY_CODE::I },
		{ 0x4A, Input::KEY_CODE::J },
		{ 0x4B, Input::KEY_CODE::K },
		{ 0x4C, Input::KEY_CODE::L },
		{ 0x4D, Input::KEY_CODE::M },
		{ 0x4E, Input::KEY_CODE::N },
		{ 0x4F, Input::KEY_CODE::O },
		{ 0x50, Input::KEY_CODE::P },
		{ 0x51, Input::KEY_CODE::Q },
		{ 0x52, Input::KEY_CODE::R },
		{ 0x53, Input::KEY_CODE::S },
		{ 0x54, Input::KEY_CODE::T },
		{ 0x55, Input::KEY_CODE::U },
		{ 0x56, Input::KEY_CODE::V },
		{ 0x57, Input::KEY_CODE::W },
		{ 0x58, Input::KEY_CODE::X },
		{ 0x59, Input::KEY_CODE::Y },
		{ 0x5A, Input::KEY_CODE::Z },
		{ VK_RETURN, Input::KEY_CODE::RETURN },
		{ VK_SNAPSHOT, Input::KEY_CODE::PRINTSCREEN },
		{ VK_SCROLL, Input::KEY_CODE::SCROLLLOCK },
		{ VK_PAUSE, Input::KEY_CODE::PAUSE },
		{ VK_INSERT, Input::KEY_CODE::INSERT },
		{ VK_HOME, Input::KEY_CODE::HOME },
		{ VK_PRIOR, Input::KEY_CODE::PAGEUP },
		{ VK_DELETE, Input::KEY_CODE::DEL },
		{ VK_END, Input::KEY_CODE::END },
		{ VK_NEXT, Input::KEY_CODE::PAGEDOWN },
		{ VK_UP, Input::KEY_CODE::UP },
		{ VK_LEFT, Input::KEY_CODE::LEFT },
		{ VK_DOWN, Input::KEY_CODE::DOWN },
		{ VK_RIGHT, Input::KEY_CODE::RIGHT },
		{ VK_SHIFT, Input::KEY_CODE::SHIFT },
		{ VK_LMENU, Input::KEY_CODE::ALTL },
		{ VK_RMENU, Input::KEY_CODE::ALTR },
		{ VK_LWIN, Input::KEY_CODE::SUPERL },
		{ VK_CAPITAL, Input::KEY_CODE::CAPSLOCK },
		{ VK_NUMLOCK, Input::KEY_CODE::NUMLOCK },
		{ VK_F1, Input::KEY_CODE::F1 },
		{ VK_F2, Input::KEY_CODE::F2 },
		{ VK_F3, Input::KEY_CODE::F3 },
		{ VK_F4, Input::KEY_CODE::F4 },
		{ VK_F5, Input::KEY_CODE::F5 },
		{ VK_F6, Input::KEY_CODE::F6 },
		{ VK_F7, Input::KEY_CODE::F7 },
		{ VK_F8, Input::KEY_CODE::F8 },
		{ VK_F9, Input::KEY_CODE::F9 },
		{ VK_F10, Input::KEY_CODE::F10 },
		{ VK_F11, Input::KEY_CODE::F11 },
		{ VK_F12, Input::KEY_CODE::F12 },
		{ VK_F13, Input::KEY_CODE::F13 },
		{ VK_F14, Input::KEY_CODE::F14 },
		{ VK_F15, Input::KEY_CODE::F15 },
		{ VK_F16, Input::KEY_CODE::F16 },
		{ VK_F17, Input::KEY_CODE::F17 },
		{ VK_F18, Input::KEY_CODE::F18 },
		{ VK_F19, Input::KEY_CODE::F19 },
		{ VK_F20, Input::KEY_CODE::F20 },
		{ VK_F21, Input::KEY_CODE::F21 },
		{ VK_F22, Input::KEY_CODE::F22 },
		{ VK_F23, Input::KEY_CODE::F23 },
		{ VK_F24, Input::KEY_CODE::F24 },
		{ VK_DIVIDE, Input::KEY_CODE::KP_DIVIDE },
		{ VK_MULTIPLY, Input::KEY_CODE::KP_MULTIPLY },
		{ VK_SUBTRACT, Input::KEY_CODE::KP_SUBTRACT },
		{ VK_ADD, Input::KEY_CODE::KP_ADD },
		{ VK_RETURN, Input::KEY_CODE::KP_ENTER },
		{ VK_DECIMAL, Input::KEY_CODE::KP_DECIMAL },
		{ VK_NUMPAD0, Input::KEY_CODE::KP_0 },
		{ VK_NUMPAD1, Input::KEY_CODE::KP_1 },
		{ VK_NUMPAD2, Input::KEY_CODE::KP_2 },
		{ VK_NUMPAD3, Input::KEY_CODE::KP_3 },
		{ VK_NUMPAD4, Input::KEY_CODE::KP_4 },
		{ VK_NUMPAD5, Input::KEY_CODE::KP_5 },
		{ VK_NUMPAD6, Input::KEY_CODE::KP_6 },
		{ VK_NUMPAD7, Input::KEY_CODE::KP_7 },
		{ VK_NUMPAD8, Input::KEY_CODE::KP_8 },
		{ VK_NUMPAD9, Input::KEY_CODE::KP_9 },
		{ VK_LBUTTON, Input::KEY_CODE::MOUSE_LEFTBUTTON },
		{ VK_RBUTTON, Input::KEY_CODE::MOUSE_RIGHTBUTTON },
		{ VK_MBUTTON, Input::KEY_CODE::MOUSE_MIDDLEBUTTON },
		{ VK_XBUTTON1, Input::KEY_CODE::MOUSE_X1BUTTON },
		{ VK_XBUTTON2, Input::KEY_CODE::MOUSE_X2BUTTON },
	};

	Input::Input() : is_mouse_position_fresh(false) {
		timer = Factory::createTimer("Input");
		timer->start();
	}

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

	void Input::handle(const Window::InputEvent input_event) {
		for (const auto& [key, state] : input_event.key_state_map) {
			record_key_state(key, state);
		}
		record_mouse_position(input_event.mouse_position);
		if (input_event.mouse_wheel_delta != 0) {
			record_mouse_wheel(input_event.mouse_wheel_delta);
		}
	}

	void Input::handle(const Gamepad::InputEvent input_event) {
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

	bool Input::get_key_state(KEY_CODE key) {
		return keys.contains(key);
	}

	bool Input::consume_key_input(KEY_CODE key_code) {
		return consume_key_input(key_code, true);
	}

	bool Input::consume_key_input(KEY_CODE key_code, bool should_debounce) {
		if (!get_key_state(key_code) || (should_debounce && keys[key_code] != 0 && (timer->elapsed() - keys[key_code] <= 1000))) { return false; }

		if (keys[key_code] == 0) {
			keys[key_code] = timer->elapsed();
		}

		if (key_code == KEY_CODE::MOUSE_WHEELUP || key_code == KEY_CODE::MOUSE_WHEELDOWN) {
			record_key_state(key_code, false);
		}

		return true;
	}

	std::pair<short, short> Input::get_current_mouse_position() {
		is_mouse_position_fresh = false;
		return this->current_mouse_position;
	}

	std::pair<short, short> Input::get_previous_mouse_position() {
		return this->previous_mouse_position;
	}

	void Input::record_key_state(unsigned int key_code, bool state) {
		record_key_state(key_code_map[key_code], state);
	}

	void Input::record_key_state(KEY_CODE key_code, bool state) {
		if (state && !get_key_state(key_code)) {
			keys[key_code] = 0;
		} else if (!state) {
			keys.erase(key_code);
		}
	}

	void Input::record_mouse_position(std::pair<short, short> mouse_position) {
		is_mouse_position_fresh = true;
		this->previous_mouse_position = this->current_mouse_position;
		this->current_mouse_position = mouse_position;
	}

	void Input::record_mouse_wheel(short mouse_wheel_delta) {
		record_key_state(KEY_CODE::MOUSE_WHEELUP, mouse_wheel_delta > 0);
		record_key_state(KEY_CODE::MOUSE_WHEELDOWN, mouse_wheel_delta < 0);
	}

	Gamepad* Input::get_gamepad(short gamepad_index) {
		return gamepads.contains(gamepad_index) ? gamepads[gamepad_index] : nullptr;
	}

	short Input::get_quantity_gamepads_connected() {
		short quantity_gamepads_connected = 0;

		for (const auto& [gamepad_index, gamepad] : gamepads) {
			quantity_gamepads_connected += (gamepad->connection_state == Gamepad::CONNECTION_STATE::CONNECTED);
		}

		return quantity_gamepads_connected;
	}

	bool Input::check_is_gamepad_connected(short gamepad_index) {
		Gamepad* gamepad = get_gamepad(gamepad_index);
		return gamepad != nullptr && gamepad->connection_state == Gamepad::CONNECTION_STATE::CONNECTED;
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
			float gamepad_input = gamepad_inputs[gamepad_index][input_code];
			uint64_t gamepad_input_consumption_stamp = gamepad_input_consumption_stamps[gamepad_index][input_code];
			if (gamepad_input != 0.0f && ((gamepad_input_consumption_stamp == 0) || (timer->elapsed() - gamepad_input_consumption_stamp > 1000))) {
				value = gamepad_input;
				if (gamepad_input_consumption_stamp == 0) {
					gamepad_input_consumption_stamps[gamepad_index][input_code] = timer->elapsed();
				}
			} else if (gamepad_input == 0.0f && gamepad_input_consumption_stamp != 0) {
				gamepad_input_consumption_stamps[gamepad_index][input_code] = 0;
			}
		}

		return value;
	}

	float Input::get_gamepad_output_value(short gamepad_index, Gamepad::OUTPUT_CODE output_code) {
		return gamepad_outputs.contains(gamepad_index) ? gamepad_outputs[gamepad_index][output_code] : 0.0f;
	}

	void Input::set_gamepad_output_value(short gamepad_index, Gamepad::OUTPUT_CODE output_code, float output_value) {
		Gamepad* gamepad = get_gamepad(gamepad_index);
		if (gamepad != nullptr) {
			Gamepad::OutputEvent output_event;
			output_event.index = gamepad_index;
			output_event.analogs[output_code] = gamepad_outputs[gamepad_index][output_code] = output_value;
			gamepad->push_output_message(Message<Gamepad::OutputEvent>(output_event));
		}
	}
}