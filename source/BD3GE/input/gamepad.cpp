#include "gamepad.h"

namespace BD3GE {
	short Gamepad::MAX_QUANTITY_GAMEPADS = 4;

	Gamepad::Gamepad() : user_index(-1), connection_state(Gamepad::CONNECTION_STATE::DISCONNECTED) {
		this->input_queue = new std::queue<Message<InputEvent>>;
	}

	XInputGamepad::XInputGamepad() : XInputGamepad(0) {}

	XInputGamepad::XInputGamepad(DWORD user_index) : last_checked_packet_number(0) {
		this->user_index = user_index;
	}

	Message<Gamepad::InputEvent> XInputGamepad::pull_input_message() {
		check_input();

		Message<Gamepad::InputEvent> input_message = Message<Gamepad::InputEvent>();

		if (!input_queue->empty()) {
			input_message = input_queue->front();
			input_queue->pop();
		}

		return input_message;
	}

	void XInputGamepad::push_output_message(Message<Gamepad::OutputEvent> output_message) {
		XINPUT_VIBRATION output_vibration;
		float VIBRATION_MAX = 65535;
		output_vibration.wLeftMotorSpeed = std::clamp(output_message.get_data()->analogs[Gamepad::OUTPUT_CODE::VIBRATION_MOTOR_0] * VIBRATION_MAX, 0.0f, VIBRATION_MAX);
		output_vibration.wRightMotorSpeed = std::clamp(output_message.get_data()->analogs[Gamepad::OUTPUT_CODE::VIBRATION_MOTOR_1] * VIBRATION_MAX, 0.0f, VIBRATION_MAX);
		XInputSetState(output_message.get_data()->index, &output_vibration);
	}

	void XInputGamepad::check_input() {
		XINPUT_STATE input_state;
		ZeroMemory(&input_state, sizeof(XINPUT_STATE));

		DWORD check_result = XInputGetState(user_index, &input_state);
		if (check_result == ERROR_SUCCESS && input_state.dwPacketNumber > last_checked_packet_number) {
			last_checked_packet_number = input_state.dwPacketNumber;

			Gamepad::InputEvent input_event{};
			input_event.connection_state = connection_state = Gamepad::CONNECTION_STATE::CONNECTED;
			input_event.index = user_index;
			float STICK_RADIUS = 32767.0f;
			float LEFT_STICK_DEADZONE = XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;
			float RIGHT_STICK_DEADZONE = XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE;
			float lx = input_state.Gamepad.sThumbLX;
			float ly = input_state.Gamepad.sThumbLY;
			float rx = input_state.Gamepad.sThumbRX;
			float ry = input_state.Gamepad.sThumbRY;
			input_event.analogs.insert({ Gamepad::INPUT_CODE::LEFT_STICK_X, abs(lx) > LEFT_STICK_DEADZONE ? (lx >= 0 ? lx - LEFT_STICK_DEADZONE : lx + LEFT_STICK_DEADZONE) / (STICK_RADIUS - LEFT_STICK_DEADZONE) : 0.0f });
			input_event.analogs.insert({ Gamepad::INPUT_CODE::LEFT_STICK_Y, abs(ly) > LEFT_STICK_DEADZONE ? (ly >= 0 ? ly - LEFT_STICK_DEADZONE : ly + LEFT_STICK_DEADZONE) / (STICK_RADIUS - LEFT_STICK_DEADZONE) : 0.0f });
			input_event.analogs.insert({ Gamepad::INPUT_CODE::RIGHT_STICK_X, abs(rx) > RIGHT_STICK_DEADZONE ? (rx >= 0 ? rx - RIGHT_STICK_DEADZONE : rx + RIGHT_STICK_DEADZONE) / (STICK_RADIUS - RIGHT_STICK_DEADZONE) : 0.0f });
			input_event.analogs.insert({ Gamepad::INPUT_CODE::RIGHT_STICK_Y, abs(ry) > RIGHT_STICK_DEADZONE ? (ry >= 0 ? ry - RIGHT_STICK_DEADZONE : ry + RIGHT_STICK_DEADZONE) / (STICK_RADIUS - RIGHT_STICK_DEADZONE) : 0.0f });
			input_event.analogs.insert({ Gamepad::INPUT_CODE::LEFT_TRIGGER, input_state.Gamepad.bLeftTrigger });
			input_event.analogs.insert({ Gamepad::INPUT_CODE::RIGHT_TRIGGER, input_state.Gamepad.bRightTrigger });
			input_event.digitals.insert({ Gamepad::INPUT_CODE::LEFT_STICK_BUTTON, (input_state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB) == XINPUT_GAMEPAD_LEFT_THUMB });
			input_event.digitals.insert({ Gamepad::INPUT_CODE::RIGHT_STICK_BUTTON, (input_state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB) == XINPUT_GAMEPAD_RIGHT_THUMB });
			input_event.digitals.insert({ Gamepad::INPUT_CODE::DPAD_UP, (input_state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP) == XINPUT_GAMEPAD_DPAD_UP });
			input_event.digitals.insert({ Gamepad::INPUT_CODE::DPAD_DOWN, (input_state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) == XINPUT_GAMEPAD_DPAD_DOWN });
			input_event.digitals.insert({ Gamepad::INPUT_CODE::DPAD_LEFT, (input_state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) == XINPUT_GAMEPAD_DPAD_LEFT });
			input_event.digitals.insert({ Gamepad::INPUT_CODE::DPAD_RIGHT, (input_state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) == XINPUT_GAMEPAD_DPAD_RIGHT });
			input_event.digitals.insert({ Gamepad::INPUT_CODE::FACE_0, (input_state.Gamepad.wButtons & XINPUT_GAMEPAD_A) == XINPUT_GAMEPAD_A });
			input_event.digitals.insert({ Gamepad::INPUT_CODE::FACE_1, (input_state.Gamepad.wButtons & XINPUT_GAMEPAD_B) == XINPUT_GAMEPAD_B });
			input_event.digitals.insert({ Gamepad::INPUT_CODE::FACE_2, (input_state.Gamepad.wButtons & XINPUT_GAMEPAD_X) == XINPUT_GAMEPAD_X });
			input_event.digitals.insert({ Gamepad::INPUT_CODE::FACE_3, (input_state.Gamepad.wButtons & XINPUT_GAMEPAD_Y) == XINPUT_GAMEPAD_Y });
			input_event.digitals.insert({ Gamepad::INPUT_CODE::LEFT_SHOULDER, (input_state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) == XINPUT_GAMEPAD_LEFT_SHOULDER });
			input_event.digitals.insert({ Gamepad::INPUT_CODE::RIGHT_SHOULDER, (input_state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) == XINPUT_GAMEPAD_RIGHT_SHOULDER });
			input_event.digitals.insert({ Gamepad::INPUT_CODE::UTIL_0, (input_state.Gamepad.wButtons & XINPUT_GAMEPAD_START) == XINPUT_GAMEPAD_START });
			input_event.digitals.insert({ Gamepad::INPUT_CODE::UTIL_1, (input_state.Gamepad.wButtons & XINPUT_GAMEPAD_BACK) == XINPUT_GAMEPAD_BACK });

			input_queue->push(input_event);
		} else if (check_result == ERROR_DEVICE_NOT_CONNECTED && connection_state == Gamepad::CONNECTION_STATE::CONNECTED) {
			last_checked_packet_number = 0;

			Gamepad::InputEvent input_event = Gamepad::InputEvent{};
			input_event.connection_state = connection_state = Gamepad::CONNECTION_STATE::DISCONNECTED;
			input_event.index = user_index;
			input_queue->push(input_event);
		}
	}
}