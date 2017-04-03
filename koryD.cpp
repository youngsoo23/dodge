// Author: Kory Despot 
// sound functions for dodge program
//
//

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include </usr/include/AL/alut.h>
#include <stdlib.h>

/*void kory() 
{
	cout << "This is a test of kory's function\n";
	return;
}
*/
/*
static void list_audio_devices(const ALCchar *devices)
{
	const ALCchar *device = devices, *next = devices + 1;
	size_t len = 0;
	
	while (device && *device != '\0' && next && *next != '\0') 
	{
		fprintf(stdout, "%s\n", device);
		len = strlen(device);
		device += (len + 1);
		next += (len + 2);
	}
}
*/

extern void initialize_sounds() 
{
	alutInit(0, NULL);
	if ( alGetError() != AL_NO_ERROR ) {
		printf("error initializing sound\n");
		return;
	}
	alGetError();

	float vec[6] = { 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f };
	alListener3f(AL_POSITION, 0.0f, 0.0f, 0.0f);
	alListenerfv(AL_ORIENTATION, vec);
	alListenerf(AL_GAIN, 1.0f);

}
extern void play_helmet_hit()
{
	ALuint alBuffer;
	alBuffer = alutCreateBufferFromFile("./sounds/metal-clang1.wav");

	ALuint alSource;
	alGenSources(1, &alSource);
	alSourcei(alSource, AL_BUFFER, alBuffer);
	
	alSourcef(alSource, AL_GAIN, 1.0f);
	alSourcef(alSource, AL_PITCH, 1.0f);
	alSourcei(alSource, AL_LOOPING, AL_FALSE);
	if (alGetError() != AL_NO_ERROR) {
		printf("ERROR setting sound source\n");
		return;
	}
	
	alSourcePlay(alSource);
	usleep(50000);

	//alDeleteSources(1, &alSource);

	//alDeleteBuffers(1, &alBuffer);
	
	//ALCcontext *Context = alcGetCurrentContext();
	//ALCdevice *Device = alcGetContextsDevice(Context);

	//alcMakeContextCurrent(NULL);

	//alcDestroyContext(Context);

	//alcCloseDevice(Device);
}



extern void play_powerup() 
{

	ALuint alBuffer;
	alBuffer = alutCreateBufferFromFile("./sounds/powerup01.wav");

	ALuint alSource;
	alGenSources(1, &alSource);
	alSourcei(alSource, AL_BUFFER, alBuffer);
	
	alSourcef(alSource, AL_GAIN, 1.0f);
	alSourcef(alSource, AL_PITCH, 1.0f);
	alSourcei(alSource, AL_LOOPING, AL_FALSE);
	if (alGetError() != AL_NO_ERROR) {
		printf("ERROR setting sound source\n");
		return;
	}
	
	alSourcePlay(alSource);
	usleep(50000);

	//alDeleteSources(1, &alSource);

	//alDeleteBuffers(1, &alBuffer);
	
	//ALCcontext *Context = alcGetCurrentContext();
	//ALCdevice *Device = alcGetContextsDevice(Context);

	//alcMakeContextCurrent(NULL);

	//alcDestroyContext(Context);

	//alcCloseDevice(Device);
}

extern void play_GetShield() 
{
	if ( alGetError() != AL_NO_ERROR ) {
		printf("error initializing sound\n");
		return;
	}
	alGetError();


	float vec[6] = { 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f };
	alListener3f(AL_POSITION, 0.0f, 0.0f, 0.0f);
	alListenerfv(AL_ORIENTATION, vec);
	alListenerf(AL_GAIN, 1.0f);

	ALuint alBuffer;
	alBuffer = alutCreateBufferFromFile("./sounds/pickup_shield.wav");

	ALuint alSource;
	alGenSources(1, &alSource);
	alSourcei(alSource, AL_BUFFER, alBuffer);
	
	alSourcef(alSource, AL_GAIN, 1.0f);
	alSourcef(alSource, AL_PITCH, 1.0f);
	alSourcei(alSource, AL_LOOPING, AL_FALSE);
	if (alGetError() != AL_NO_ERROR) {
		printf("ERROR setting sound source\n");
		return;
	}
	
	alSourcePlay(alSource);

	//alDeleteSources(1, &alSource);

	//alDeleteBuffers(1, &alBuffer);
	
	//ALCcontext *Context = alcGetCurrentContext();
	//ALCdevice *Device = alcGetContextsDevice(Context);

	//alcMakeContextCurrent(NULL);

	//alcDestroyContext(Context);

	//alcCloseDevice(Device);
}
