#ifndef BD3GE_GAMEPAD_H
#define BD3GE_GAMEPAD_H

#include <algorithm>
#include <map>
#include <queue>

#ifdef __linux__
#elif _WIN32

#include <Windows.h>
#include <Xinput.h>

#endif

#include "../system/constants.h"
#include "../system/globals.h"
#include "../utility/message.h"

namespace BD3GE {
	class Gamepad {
		public:

			static short MAX_QUANTITY_GAMEPADS;

			enum class CONNECTION_STATE {
				CONNECTED,
				DISCONNECTED
			};

			enum class INPUT_CODE {
				LEFT_STICK_X,
				LEFT_STICK_Y,
				RIGHT_STICK_X,
				RIGHT_STICK_Y,
				LEFT_STICK_BUTTON,
				RIGHT_STICK_BUTTON,
				DPAD_UP,
				DPAD_DOWN,
				DPAD_LEFT,
				DPAD_RIGHT,
				FACE_0,
				FACE_1,
				FACE_2,
				FACE_3,
				LEFT_SHOULDER,
				RIGHT_SHOULDER,
				LEFT_TRIGGER,
				RIGHT_TRIGGER,
				UTIL_0,
				UTIL_1
			};

			enum class OUTPUT_CODE {
				VIBRATION_MOTOR_0,
				VIBRATION_MOTOR_1,
			};

			typedef struct InputEvent {
				CONNECTION_STATE connection_state;
				short index = 0;
				std::map<INPUT_CODE, bool> digitals;
				std::map<INPUT_CODE, float> analogs;
			} InputEvent;

			typedef struct OutputEvent {
				short index = 0;
				std::map<OUTPUT_CODE, float> analogs;
			} OutputEvent;

			Gamepad();
			virtual Message<Gamepad::InputEvent> pull_input_message() = 0;
			virtual void push_output_message(Message<Gamepad::OutputEvent> output_message) = 0;
			virtual void check_input() = 0;

			short user_index;
			CONNECTION_STATE connection_state;
			std::queue<Message<InputEvent>>* input_queue;
	};

#ifdef __linux__
#elif _WIN32

	class XInputGamepad : public Gamepad {
		public:

			XInputGamepad();
			XInputGamepad(DWORD user_index);
			Message<Gamepad::InputEvent> pull_input_message() override;
			void push_output_message(Message<Gamepad::OutputEvent> output_message) override;
			void check_input() override;

			DWORD last_checked_packet_number;
	};
}

#endif

#endif // BD3GE_GAMEPAD_H