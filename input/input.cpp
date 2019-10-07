#include "input.h"

namespace BD3GE
{
	/*
	 *	Input class
	 */

	void Input::handler(Message<std::pair<BD3GE::KEY_CODE, bool>> message)
	{
		if (message.get_data())
		{
			set_key_state(message.get_data()->first, message.get_data()->second);

			if (message.get_data()->second == true)
			{
				// TODO: Write conversion utility between key code enum and string.
				//g_log.write("'" + std::string(message.get_data()->first) + "' key pressed.", BD3GE::LOG_TYPE::INFO);
			}

			else if (message.get_data()->second == false)
			{
				// TODO: Write conversion utility between key code enum and string.
				//g_log.write("'" + std::string(message.get_data()->first) + "' key released.", BD3GE::LOG_TYPE::INFO);
			}
		}
	}

	void Input::set_key_state(BD3GE::KEY_CODE key, bool state)
	{
		m_keys[key] = state;
	}

	bool Input::get_key_state(BD3GE::KEY_CODE key)
	{
		return m_keys[key];
	}
}