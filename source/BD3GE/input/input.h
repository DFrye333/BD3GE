#ifndef BD3GE_INPUT_H
#define BD3GE_INPUT_H

#include <iostream>
#include <cstring>
#include <map>
#include <utility>

#ifdef __linux__
#elif _WIN32

#include <Windows.h>

#endif

#include "../input/gamepad.h"
#include "../system/api.h"
#include "../system/constants.h"
#include "../system/globals.h"
#include "../utility/factory.h"
#include "../utility/message.h"
#include "../utility/timer.h"

namespace BD3GE {
	extern "C" class BD3GE_API Input {
		public:

			// Keystring mappings.
			enum class KEY_CODE {
				BACKSPACE,
				TAB,
				ESCAPE,
				SPACE,
				QUOTE,
				COMMA,
				MINUS,
				PERIOD,
				SLASH,
				NUM_0,
				NUM_1,
				NUM_2,
				NUM_3,
				NUM_4,
				NUM_5,
				NUM_6,
				NUM_7,
				NUM_8,
				NUM_9,
				SEMICOLON,
				EQUAL,
				BRACKETLEFT,
				BACKSLASH,
				BRACKETRIGHT,
				GRAVE,
				A,
				B,
				C,
				D,
				E,
				F,
				G,
				H,
				I,
				J,
				K,
				L,
				M,
				N,
				O,
				P,
				Q,
				R,
				S,
				T,
				U,
				V,
				W,
				X,
				Y,
				Z,
				RETURN,
				PRINTSCREEN,
				SCROLLLOCK,
				PAUSE,
				INSERT,
				HOME,
				PAGEUP,
				DEL,
				END,
				PAGEDOWN,
				UP,
				LEFT,
				DOWN,
				RIGHT,
				SHIFT,
				SHIFTL,
				SHIFTR,
				CONTROLL,
				CONTROLR,
				ALTL,
				ALTR,
				SUPERL,
				CAPSLOCK,
				NUMLOCK,
				F1,
				F2,
				F3,
				F4,
				F5,
				F6,
				F7,
				F8,
				F9,
				F10,
				F11,
				F12,
				F13,
				F14,
				F15,
				F16,
				F17,
				F18,
				F19,
				F20,
				F21,
				F22,
				F23,
				F24,
				KP_DIVIDE,
				KP_MULTIPLY,
				KP_SUBTRACT,
				KP_ADD,
				KP_ENTER,
				KP_DECIMAL,
				KP_0,
				KP_1,
				KP_2,
				KP_3,
				KP_4,
				KP_5,
				KP_6,
				KP_7,
				KP_8,
				KP_9,
				MOUSE_LEFTBUTTON,
				MOUSE_RIGHTBUTTON,
				MOUSE_MIDDLEBUTTON,
				MOUSE_X1BUTTON,
				MOUSE_X2BUTTON,
				MOUSE_WHEELUP,
				MOUSE_WHEELDOWN
			};

#ifdef __linux__
#elif _WIN32
			static std::map<int, Input::KEY_CODE> key_code_map;
#endif

									Input();
									Input(unsigned short debounce_duration);
									Input(std::vector<Gamepad*> gamepads);
									~Input();
			void					handle(const Window::InputEvent input_event);
			void					handle(const Gamepad::InputEvent input_event);
			void					update();
			bool					get_key_state(KEY_CODE key);
			bool					consume_key_input(KEY_CODE key);
			bool					consume_key_input(KEY_CODE key, bool should_debounce);
			std::pair<short, short>	get_current_mouse_position();
			std::pair<short, short>	get_previous_mouse_position();
			bool					get_is_mouse_position_fresh();
			Gamepad*				get_gamepad(short gamepad_index);
			short					get_quantity_gamepads_connected();
			bool					check_is_gamepad_connected(short gamepad_index);
			short					get_primary_connected_gamepad_index();
			float					get_gamepad_input_value(short gamepad_index, Gamepad::INPUT_CODE input_code);
			float					consume_gamepad_input_value(short gamepad_index, Gamepad::INPUT_CODE input_code);
			float					get_gamepad_output_value(short gamepad_index, Gamepad::OUTPUT_CODE output_code);
			void					set_gamepad_output_value(short gamepad_index, Gamepad::OUTPUT_CODE output_code, float output_value);

		protected:

			void					record_key_state(unsigned int key_code, bool state);
			void					record_key_state(KEY_CODE key_code, bool state);
			void					record_mouse_position(std::pair<short, short> mouse_position);
			void					record_mouse_wheel(short mouse_wheel_delta);

			Timer* timer;
			unsigned short debounce_duration;
			std::map<KEY_CODE, uint64_t> keys;
			std::pair<short, short> current_mouse_position;
			std::pair<short, short> previous_mouse_position;
			bool is_mouse_position_fresh;
			std::map<short, Gamepad*> gamepads;
			std::map<short, std::map<Gamepad::INPUT_CODE, float>> gamepad_inputs;
			std::map<short, std::map<Gamepad::INPUT_CODE, uint64_t>> gamepad_input_consumption_stamps;
			std::map<short, std::map<Gamepad::OUTPUT_CODE, float>> gamepad_outputs;
	};
}

#endif // BD3GE_INPUT_H
