#include "input.h"

namespace BD3GE
{
	/*
	 *	Input class
	 */

	void Input::handler(Message< std::pair <char*, bool> > message)
	{
		if (message.get_data())
		{
			set_key_state(message.get_data()->first, message.get_data()->second);

			if (message.get_data()->second == true)
			{
				g_log.write("'" + std::string(message.get_data()->first) + "' key pressed.", LOG_INFORMATION);
			}

			else if (message.get_data()->second == false)
			{
				g_log.write("'" + std::string(message.get_data()->first) + "' key released.", LOG_INFORMATION);
			}
		}
	}

	void Input::set_key_state(std::string key, bool state)
	{
		m_keys[key] = state;
	}

	bool Input::get_key_state(const std::string key)
	{
		return m_keys[key];
	}
}