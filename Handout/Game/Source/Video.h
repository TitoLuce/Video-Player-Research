#ifndef _VIDEO_H_
#define _VIDEO_H_

#pragma comment( lib, "SDL/libx86/SDL2.lib" )
#pragma comment( lib, "SDL/libx86/SDL2main.lib" )

#include "Module.h"
#include "theoraplay.h"
#include "External/SDL/include/SDL.h"
#include "External/SDL/include/SDL_version.h"
#include "External/SDL/include/begin_code.h"

typedef struct AudioQueue
{
	const THEORAPLAY_AudioPacket* audio;
	int offset;
	struct AudioQueue* next;
} AudioQueue;

static volatile AudioQueue* audioQueue = NULL;
static volatile AudioQueue* audioQueueTail = NULL;

class Video : public Module
{
public:
	Video();
	~Video();
	bool Awake(pugi::xml_node&);
	bool CleanUp();

	THEORAPLAY_Decoder* decoder;
	const THEORAPLAY_AudioPacket* audio;
	const THEORAPLAY_VideoFrame* video;
	SDL_Texture* texture;
	SDL_AudioSpec audioSpec;
	Uint32 baseticks;
	Uint32 framems;

	int SDLCALL Load(const char* file, SDL_Renderer* renderer);
	SDL_Texture* SDLCALL UpdateVideo(int video);
	int SDLCALL IsPlaying(int videoId);
	void SDLCALL DestroyVideo(int video);
	static void SDLCALL AudioCallback(void* userdata, Uint8* stream, int len);
	static void QueueAudio(const THEORAPLAY_AudioPacket* audio);
};

#endif