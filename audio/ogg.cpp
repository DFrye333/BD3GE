#include "ogg.h"

namespace BD3GE {
	/*
	 * 		Ogg class
	 */

	Ogg::Ogg() {
		alGenBuffers(1, &m_ID_buffer);
		alGenSources(1, &m_ID_sources);
		alSource3f(m_ID_sources, AL_POSITION, 0.0f, 0.0f, 0.0f);
		info = NULL;
		format = 0;
		frequency = 0;
		loaded = false;
	}

	Ogg::Ogg(std::string file_name) {
		alGenBuffers(1, &m_ID_buffer);
		alGenSources(1, &m_ID_sources);
		alSource3f(m_ID_sources, AL_POSITION, 0.0f, 0.0f, 0.0f);
		loaded = false;
		load_OGG_file(file_name);
		loaded = true;
	}

	Ogg::~Ogg() {
		alDeleteBuffers(1, &m_ID_buffer);
		alDeleteSources(1, &m_ID_sources);
	}

	void Ogg::load_OGG_file(std::string file_name) {
		FILE* infile = NULL;
		int bitStream = 0;
		long bytes = 0;
		char tempBuffer[32768];
		int success;

		if (true == loaded) {
			g_log->write(Log::TYPE::ERR, "File object already loaded.");
			return;
		}

		infile = fopen(file_name.c_str(), "rb");
		success = ov_open(infile, &file, NULL, 0);

		switch (success) {
			case OV_EREAD:
				g_log->write(Log::TYPE::ERR, "Cannot open Ogg - OV_EREAD");
				break;
			case OV_ENOTVORBIS:
				g_log->write(Log::TYPE::ERR, "Cannot open Ogg - OV_ENOTVORBIS");
				break;
			case OV_EVERSION:
				g_log->write(Log::TYPE::ERR, "Cannot open Ogg - OV_EVERSION");
				break;
			case OV_EBADHEADER:
				g_log->write(Log::TYPE::ERR, "Cannot open Ogg - OV_EBADHEADER");
				break;
			case OV_EFAULT:
				g_log->write(Log::TYPE::ERR, "Cannot open Ogg - OV_EFAULT");
				break;
			case 0:
				g_log->write(Log::TYPE::INFO, "Ogg file opened successfully.");
				break;
			default:
				g_log->write(Log::TYPE::ERR, "Cannot open Ogg - Unknown Ogg error.");
		}

		info = ov_info(&file, -1);
		switch (info->channels) {
			case 1:
				format = AL_FORMAT_MONO16;
				g_log->write(Log::TYPE::INFO, "Format is mono-16.");
				break;
			case 2:
				g_log->write(Log::TYPE::INFO, "Format is stereo-16.");
				format = AL_FORMAT_STEREO16;
				break;
		}

		frequency = info->rate;
		do {
			bytes = ov_read(&file, tempBuffer, 32768, 0, 2, 1, &bitStream);
			buffer.insert(buffer.end(), tempBuffer, tempBuffer + bytes);
		} while (bytes > 0);

		ov_clear(&file);
	}

	void Ogg::play(void) {
	//	ALint state = 0;

		alBufferData(m_ID_buffer, format, &buffer[0], buffer.size(), frequency);
		alSourcei(m_ID_sources, AL_BUFFER, m_ID_buffer);
		alSourcePlay(m_ID_sources);
	/*	do {
			alGetSourcei(m_ID_sources, AL_SOURCE_STATE, &state);
		} while (state != AL_STOPPED);*/
	}
}