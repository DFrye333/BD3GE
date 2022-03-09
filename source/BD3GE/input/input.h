#ifndef BD3GE_INPUT_H
#define BD3GE_INPUT_H

#include <iostream>
#include <cstring>
#include <map>
#include <utility>

#include "../input/gamepad.h"
#include "../system/api.h"
#include "../system/constants.h"
#include "../system/globals.h"
#include "../system/window.h"
#include "../utility/message.h"

namespace BD3GE {
	extern "C" class BD3GE_API Input {
		public:

									Input();
									Input(std::vector<Gamepad*> gamepads);
									~Input();
			void					handle(const BD3GE::Window::InputEvent input_event);
			void					handle(const BD3GE::Gamepad::InputEvent input_event);
			void					update();
			bool					get_key_state(BD3GE::KEY_CODE key);
			bool					consume_key_input(BD3GE::KEY_CODE key);
			std::pair<short, short>	get_current_mouse_position();
			std::pair<short, short>	get_previous_mouse_position();
			Gamepad*				get_gamepad(short gamepad_index);
			short					get_quantity_gamepads_connected();
			bool					check_is_gamepad_connected(short gamepad_index);
			short					get_primary_connected_gamepad_index();
			float					get_gamepad_input_value(short gamepad_index, Gamepad::INPUT_CODE input_code);
			float					consume_gamepad_input_value(short gamepad_index, Gamepad::INPUT_CODE input_code);
			float					get_gamepad_output_value(short gamepad_index, Gamepad::OUTPUT_CODE output_code);
			void					set_gamepad_output_value(short gamepad_index, Gamepad::OUTPUT_CODE output_code, float output_value);

			bool is_mouse_position_fresh;

		protected:

			void					record_key_state(BD3GE::KEY_CODE key, bool state);
			void					record_mouse_position(std::pair<short, short> mouse_position);

			std::map<KEY_CODE, bool> keys;
			std::pair<short, short> current_mouse_position;
			std::pair<short, short> previous_mouse_position;
			std::map<short, Gamepad*> gamepads;
			std::map<short, std::map<Gamepad::INPUT_CODE, float>> gamepad_inputs;
			std::map<short, std::map<Gamepad::OUTPUT_CODE, float>> gamepad_outputs;
	};
}

#endif // BD3GE_INPUT_H
