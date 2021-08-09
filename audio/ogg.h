#ifndef BD3GE_OGG_H
#define BD3GE_OGG_H

#include <iostream>
#include <string>
#include <vector>

#include <al.h>
#include <alc.h>
#include <vorbis/vorbisfile.h>

#include "../system/constants.h"
#include "../system/globals.h"

namespace BD3GE {
	class Ogg {
		public:
								Ogg();
								Ogg(std::string file_name);
								~Ogg();
			void				load_OGG_file(std::string file_name);
			void				play(void);
			ALuint				get_ID_buffer(void)		{ return m_ID_buffer; }
			ALuint				get_ID_sources(void)	{ return m_ID_sources; }
			ALuint				get_format(void)		{ return format; }
			ALsizei				get_frequency(void)		{ return frequency; }
			std::vector <char>	get_buffer(void)		{ return buffer; }
		protected:
			ALuint				m_ID_buffer;
			ALuint				m_ID_sources;
			bool				loaded;
			OggVorbis_File		file;
			vorbis_info*		info;
			ALuint				format;
			ALsizei				frequency;
			std::vector <char>	buffer;
	};
}

#endif // BD3GE_OGG_H
