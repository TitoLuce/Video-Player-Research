#include "App.h"
#include "Render.h"
#include "Input.h"
#include "Window.h"
#include "Log.h"
#include "Video.h"
#include "VideoScene.h"

Video::Video()
{
}

Video::~Video()
{
}

bool Video::Awake(pugi::xml_node&)
{
	return true;
}

bool Video::CleanUp()
{
	return true;
}


int Video::Load(const char* file, SDL_Renderer* renderer)
{
	//TODO 1: Use THEORAPLAY_Decoder & THEORAPLAY_startDecodeFile to decode the format



	//TODO 2: Create a video & audio buffer (THEORAPLAY_VideoFrame & THEORAPLAY_AudioPacket) and fill them with THEORAPLAY_getAudioand THEORAPLAY_getVideo.



	SDL_Texture* overlay = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_YV12, SDL_TEXTUREACCESS_STREAMING, video->width, video->height);
	if (overlay == 0)
	{
		//TODO 3.1: In case of error, free the audio & video buffers & stop the debuffer



		return 0;
	}

	// Create video item
	Video* player = (Video*)malloc(sizeof(Video));
	player->audio = audio;
	player->video = video;
	player->decoder = decoder;
	player->texture = overlay;
	player->baseticks = SDL_GetTicks();
	player->framems = (video->fps == 0.0) ? 0 : ((Uint32)(1000.0 / video->fps));

	//Load audio specs
	memset(&player->audioSpec, '\0', sizeof(SDL_AudioSpec));
	player->audioSpec.freq = audio->freq;
	player->audioSpec.format = AUDIO_S16SYS;
	player->audioSpec.channels = audio->channels;
	player->audioSpec.samples = 2048;
	player->audioSpec.callback = AudioCallback;

	if (SDL_OpenAudio(&player->audioSpec, NULL) != 0 )
	{
		//TODO 3.2: In case of error, free the audio & video buffers & stop the decoding



		return 0;
	}

	//After the audio packet is processed we process the next audio packet
	while (audio)
	{
		QueueAudio(audio);
		audio = THEORAPLAY_getAudio(decoder);
	}

	SDL_PauseAudio(0);

	return (int)player;
}

SDL_Texture* Video::UpdateVideo(int videoId)
{
	Video* vid = (Video*)videoId;
	
	if (THEORAPLAY_isDecoding(vid->decoder))
	{
		//TODO 4: Get & process the video data from the decoder




		const Uint32 now = SDL_GetTicks() - vid->baseticks;


		if (vid->video && (vid->video->playms <= now))
		{
			// Play the video frames when it's time. Each frame needs to be rendered during a certain amount of time, the time is specified in video->playms. 
			if (vid->framems && ((now - vid->video->playms) >= vid->framems))
			{
				const THEORAPLAY_VideoFrame* last = vid->video;

				while ((vid->video = THEORAPLAY_getVideo(vid->decoder)) != NULL)
				{
					THEORAPLAY_freeVideo(last);
					last = vid->video;
					if ((now - vid->video->playms) < vid->framems)
						break;
				}

				if (!vid->video)
					vid->video = last;
			}

			if (!vid->video)
			{
				LOG("WARNING: Playback can't keep up!");
				return NULL;
			}
			else
			{
				int halfWidth = vid->video->width / 2;

				const Uint8* y = (const Uint8*)vid->video->pixels;
				const Uint8* u = y + (vid->video->width * vid->video->height);
				const Uint8* v = u + (halfWidth * (vid->video->height / 2));

				SDL_UpdateYUVTexture(vid->texture, NULL, y, vid->video->width, u, halfWidth, v, halfWidth);
			}
			THEORAPLAY_freeVideo(vid->video);
			vid->video = NULL;
		}
	}

	//For each frame the audio needs to be processed again
	while ((vid->audio = THEORAPLAY_getAudio(vid->decoder)) != NULL)
		QueueAudio(vid->audio);

	return vid->texture;
}

void Video::DestroyVideo(int video)
{
	Video* vid = (Video*)video;

	while (audioQueue != NULL)
	{
		SDL_LockAudio();
		SDL_UnlockAudio();
		SDL_Delay(10);
	}

	//TODO 5: Just like the TODO 3, free the video & audio buffers & stop the decoding, but also destroy the texture.



}

int Video::IsPlaying(int video)
{
	return THEORAPLAY_isDecoding(((Video*)video)->decoder);
}

void Video::QueueAudio(const THEORAPLAY_AudioPacket* audio)
{
	AudioQueue* item = (AudioQueue*)malloc(sizeof(AudioQueue));
	if (!item)
	{
		THEORAPLAY_freeAudio(audio);
		return;
	}

	item->audio = audio;
	item->offset = 0;
	item->next = NULL;

	SDL_LockAudio();
	if (audioQueueTail)
		audioQueueTail->next = item;
	else
		audioQueue = item;
	audioQueueTail = item;
	SDL_UnlockAudio();
}

void SDLCALL Video::AudioCallback(void* userdata, Uint8* stream, int len)
{

	Sint16* dst = (Sint16*)stream;

	while (audioQueue && (len > 0))
	{
		volatile AudioQueue* item = audioQueue;
		AudioQueue* next = item->next;
		const int channels = item->audio->channels;

		const float* src = item->audio->samples + (item->offset * channels);
		int cpy = (item->audio->frames - item->offset) * channels;
		int i;

		if (cpy > (len / sizeof(Sint16)))
			cpy = len / sizeof(Sint16);

		for (i = 0; i < cpy; i++)
		{
			const float val = *(src++);
			if (val < -1.0f)
				*(dst++) = -32768;
			else if (val > 1.0f)
				*(dst++) = 32767;
			else
				*(dst++) = (Sint16)(val * 32767.0f);
		}

		item->offset += (cpy / channels);
		len -= cpy * sizeof(Sint16);

		if (item->offset >= item->audio->frames)
		{
			THEORAPLAY_freeAudio(item->audio);
			free((void*)item);
			audioQueue = next;
		}
	}

	if (!audioQueue)
		audioQueueTail = NULL;

	if (len > 0)
		memset(dst, '\0', len);
}