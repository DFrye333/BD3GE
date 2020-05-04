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
			ALuint				get_format(void)		{ return m_format; }
			ALsizei				get_frequency(void)		{ return m_frequency; }
			std::vector <char>	get_buffer(void)		{ return m_buffer; }
		protected:
			ALuint				m_ID_buffer;
			ALuint				m_ID_sources;
			bool				m_loaded;
			OggVorbis_File		m_file;
			vorbis_info*		m_info;
			ALuint				m_format;
			ALsizei				m_frequency;
			std::vector <char>	m_buffer;
	};
}

#endif // BD3GE_OGG_H
