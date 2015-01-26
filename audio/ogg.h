#ifndef OGG_H
#define OGG_H

#include <iostream>
#include <string>
#include <vector>

#include <AL/al.h>
#include <AL/alc.h>
#include <vorbis/vorbisfile.h>

#include "../system/constants.h"

class Ogg
{
	public:
							Ogg();
							Ogg(std::string fileName);
							~Ogg();
		ALuint				getIdBuffer(void) 	{ return mIdBuffer; }
		ALuint				getIdSources(void) 	{ return mIdSources; }
		ALuint				getFormat(void)		{ return mFormat; }
		ALsizei				getFrequency(void)	{ return mFrequency; }
		std::vector <char>	getBuffer(void)		{ return mBuffer; }
		void				loadOggFile(std::string fileName);
		void				play(void);
	protected:
		ALuint				mIdBuffer;
		ALuint				mIdSources;
		bool				mLoaded;
		OggVorbis_File		mFile;
		vorbis_info*		mInfo;
		ALuint				mFormat;
		ALsizei				mFrequency;
		std::vector <char>	mBuffer;
};

#endif // OGG_H
