/*
 * 		Ogg class
 */

#include "ogg.h"

Ogg::Ogg()
{
	alGenBuffers(1, &mIdBuffer);
	alGenSources(1, &mIdSources);
	alSource3f(mIdSources, AL_POSITION, 0.0f, 0.0f, 0.0f);
	mInfo = NULL;
	mFormat = 0;
	mFrequency = 0;
	mLoaded = false;
}

Ogg::Ogg(std::string fileName)
{
	alGenBuffers(1, &mIdBuffer);
	alGenSources(1, &mIdSources);
	alSource3f(mIdSources, AL_POSITION, 0.0f, 0.0f, 0.0f);
	mLoaded = false;
	loadOggFile(fileName);
	mLoaded = true;
}

Ogg::~Ogg()
{
	alDeleteBuffers(1, &mIdBuffer);
	alDeleteSources(1, &mIdSources);
}

void Ogg::loadOggFile(std::string fileName)
{
	FILE* infile = NULL;
	int bitStream = 0;
	long bytes = 0;
	char tempBuffer[32768];
	bool success;

	if (true == mLoaded)
	{
		std::cout << "File object already loaded." << std::endl;
		return;
	}

	infile = fopen(fileName.c_str(), "rb");
	success = ov_open(infile, &mFile, NULL, 0);

	switch (success)
	{
		case OV_EREAD:
			std::cout << BD3GE_PRINT_ERROR << "OV_EREAD" << std::endl;
			break;
		case OV_ENOTVORBIS:
			std::cout << BD3GE_PRINT_ERROR << "OV_ENOTVORBIS" << std::endl;
			break;
		case OV_EVERSION:
			std::cout << BD3GE_PRINT_ERROR << "OV_EVERSION" << std::endl;
			break;
		case OV_EBADHEADER:
			std::cout << BD3GE_PRINT_ERROR << "OV_EBADHEADER" << std::endl;
			break;
		case OV_EFAULT:
			std::cout << BD3GE_PRINT_ERROR << "OV_EFAULT" << std::endl;
			break;
		case 0:
			std::cout << BD3GE_PRINT_INFORMATION << "File opened successfully." << std::endl;
			break;
		default:
			std::cout << BD3GE_PRINT_ERROR << "Unknown Ogg error." << std::endl;
	}

	mInfo = ov_info(&mFile, -1);
	switch (mInfo->channels)
	{
		case 1:
			mFormat = AL_FORMAT_MONO16;
			std::cout << BD3GE_PRINT_INFORMATION << "Format is mono-16." << std::endl;
			break;
		case 2:
			std::cout << BD3GE_PRINT_INFORMATION << "Format is stereo-16." << std::endl;
			mFormat = AL_FORMAT_STEREO16;
			break;
	}

	mFrequency = mInfo->rate;
	do
	{
		bytes = ov_read(&mFile, tempBuffer, 32768, 0, 2, 1, &bitStream);
		mBuffer.insert(mBuffer.end(), tempBuffer, tempBuffer + bytes);
	} while (bytes > 0);

	ov_clear(&mFile);
}

void Ogg::play(void)
{
//	ALint state = 0;

	alBufferData(mIdBuffer, mFormat, &mBuffer[0], mBuffer.size(), mFrequency);
	alSourcei(mIdSources, AL_BUFFER, mIdBuffer);
	alSourcePlay(mIdSources);
/*	do
	{
		alGetSourcei(mIdSources, AL_SOURCE_STATE, &state);
	} while (state != AL_STOPPED);*/
}
