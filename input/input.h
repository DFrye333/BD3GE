#ifndef INPUT_H
#define INPUT_H

#include <iostream>
#include <cstring>
#include <map>

#include <X11/Xlib.h>

#include "../system/constants.h"
#include "../utility/message.h"

class Input
{
	public:

				Input();
		void	handler(Message< std::pair <char*, bool> > message);
		void	setKeyState(std::string key, bool state);
		bool	getKeyState(const std::string key);

	protected:

		std::map<const std::string, unsigned int>	mKeys;
};

#endif // INPUT_H
