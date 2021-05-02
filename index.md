## Introduction

Hello, I am Arnau Lucena Cobo, and I welcome you to my personal research on how to make a Video Player for video games in Visual Studio, assigned by [Raysan](https://github.com/raysan5) in the Project 2 subject at the Video Game Design & Development Degree in CITM, UPC.

### What is a Video Player

A video player is a kind of media player for playing back digital video data from media such as optical discs, as well as from files of appropriate formats such as MPEG, AVI, RealVideo & QuickTime. Many of the video players also support simple playback of digital audio and 3D playback of 2D video.

![Media players](https://user-images.githubusercontent.com/59049803/116826770-f2634180-ab95-11eb-9daf-203f6ced86fa.png)

When it comes to video games, these are used to cinematically showcase situations that would not be efficiently shown through gameplay, or would otherwise bee too complex to process in real time, and are especially useful to impress the players by showcasing animation prowess, and help expand the creative options one has to convey emotions or ideas.

### Types of cutscenes in videogames

There are a total of five types of cutscenes used in video games:

- Live-action Cutscenes

Live-action cutscenes have many similarities to films, using constructed sets & actors to portray the characters. And some games, such as Electronic Arts' Lord of the Rings & Star Wars games have extensively used film footage & other assets from the film production in their cutscenes.

- Pre-rendered cutscenes

Pre-rendered cutscenes are animated and rendered by the game's developers, and take advantage of the full array of techniques of CGI, cel animation or graphic novel-style panel art.

![TBOI Prerendered Cutscene](https://thumbs.gfycat.com/ExcitableMediumChihuahua-size_restricted.gif)

-Real time cutscenes 
Real time cutscenes are rendered on-the-fly using the same game engine as the graphics during gameplay. This technique is also known as Machinima/Machinema.

These are usually of much lower quality than pre-rendered cutscenes, but can adapt to the game's state. For example, some games allow the player character to wear several different outfits, and appear in cutscenes wearing the outfit the player has chosen, and sometimes even give players control over camera movement during them.

<iframe width="560" height="315" src="https://www.youtube.com/embed/g9Q5g_orycA" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>

- Mixed media cutscenes

These are basically the combination of both pre-rendered and real time cutscenes on a game, Which many games use as the developers may feel it appropriate for scenes to be of one type or other.

- Interactive cutscenes

Interactive cutscenes, also known as Quick time events involve the computer taking control of the player character while prompts (such as a sequence of button presses) appear onscreen, requiring the player to follow them in order to continue or succeed at the action.

![QTE](https://i1.wp.com/stinger-magazine.com/wp-content/uploads/2020/10/God_of_War%C2%AE_III_Remastered_Kratos_beats_Zeus_to_Death.gif?w=850&ssl=1)

### Video files & Codecs

Before starting withe the code implementation, first we need to talk about video files & codecs.

Video files are formats used to store digital video data on a computer system, usually consisting of a container (MP4, AVI, Webm...) that stores video data in a video coding format such as VP9, H.264 or H.265 alongside audio data in an audio coding format such as MP3, AAc or Vorbis and, optionally, synchronization information, subtitles & other metadata such as the title.

Due to the extensive amount of containers, which in turn are usually capable of containing multiple video & audio coding formats, media players with high compatibility usually end up being a coding hell due to the fact that they have to keep in mind the many formats within the many containers, which usually are not easy to identify, and therefore require a lot of knowledge, time & patience to make.

![File Formats](https://jingzhi.space/wp-content/uploads/2020/05/file-formats.png)

Furthermore, to do all of this we need the use of codecs, which are programs or pieces of hardware that pack and compress data (Encode) and/or takes packed data and unpackages it (Decode). This is necessary due to the fact that video & music files are really big, and in consequence, are hard to transfer & store.

And just as there are many containers & formats, there are also many types of different codecs, which may bre preferable in different situations.
For more information about it, I recommend checking this video:

<iframe width="560" height="315" src="https://www.youtube.com/embed/7YQ1mikDhIo" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>

At last, it must be said that each codec has it's own license type, so developers need to be careful of them if they do not want to get into legal trouble. Here are some available options I have found and their advantages & disadvantages:

- Bink

Bink from RAD game tools is as close as you can get to a de facto standard in the games industry, being used in more than 5800 games on 14 different platforms.
It's main drawback is it's pricing of $8500 per platform per game, which, in big companies is not a big number, but for indie developers, and even more students, this sum is pretty exorbitant.

- Platform specific

One approach to video playing is to not develop a platform-independent library but instead use the video playing capabilities inherent in each platform. For example, Windows has Windows Media Foundation, MacOS has QuickTime, etc.

Using the platform's own library has several advantages. It is free to use, even for proprietary formats, because the platform manufacturers have already paid the license fees for the codecs & the implementation is already there, even if the APIs are not the easiest to use.

The biggest advantage is that on low-end platforms, using the built-in platform libraries can give you access to special video decoding hardware. For example, many phones have built-in H.264 decoding hardware. This means you can play video nearly for free, something that otherwise would be very costly on a low-end CPU.

But going platform specific also has a lot of drawbacks. If you target many platforms you have your work cut out for you in integrating all their different video playing backends. It adds an additional chunk of work that you need to do whenever you want to add a new platform.

- H.264

Over the last few years H.264 has emerged as the most popular commercial codec. It is used in Blu-ray players, video cameras, on iTunes, YouTube, etc. If you want a codec with good tool support and high quality, H.264 is the best choice.

However, H.264 is covered by patents. Patents that need to be licensed if you want to use H.264 without risking a lawsuit.

The H.264 patents are managed by an entity known as MPEG LA. They have gathered all the patents that they believe pertain to H.264 in "patent pool" that you can license all at once, with a single agreement. That patent pool contains a total of **1700 patents**. And you still could get sued if you were to infringe on a patent that isn't there. So it is probably not worth the risks and the headache.

- VP8/VP9

VP8 & VP9 are free video codecs owned by Google, covered by patents that Google has granted free use of & also provides a BSD licensed library libvpx for encoding and decoding video files. The formats are also endorsed by the Free Software Foundation, but there been a constant discussion on whether it infringes or not on patents, but this usually happens with free codecs such as Dirac or Theora, as they all try not to infringe on patents.

### Implementation in code

Now that I have explained the basics of video files & codecs, I will proceed to talk about the implementation of the video player in Visual Studio. And I will be using the aforementioned free codec Theora. Furthermore, I will be using a library called TheoraPlay to play encoded videos as SDL_Textures which is free to use & unencumbered

The implementation is a bit extensive & has many new functions but  the summarised version would be:

1. Call the Load function to load the desired video (The format container used will be .ogv)
2. Upon loading, Update video will take care of playing videos at the right time, updating the textures in the right format & freeing the video frame once they have been updated, and will then reprocess the audio, as it is necessary. At the same time, AudioCallback & QueueAudio will take care of filling the audioQueue & audioQueueTail with the correct audio properties so that sound may be played well.
3. Through the use of IsPlaying, once the videois finished, it will be destroyed.

As an extra, I have added a function to skip the video by pressing spacebar.

### Possible improvements

- Due to how complicated game video players are to make in Visual Studio, there are many options I have not been able to add due to lack of expertise and time. Such as:
1. A pause function
2. A method of replaying the video or playing multiple videos (Even at the same time), as as of right now only one video can be played at a time and only once.
3. A method to scale videos regardless of quality, as the video player currently doesn't scale the video to the window.
4. A method to easily modify the volume, as it is currently set to a specific amount.

### Exercises

### TODO 1
Use THEORAPLAY_Decoder & THEORAPLAY_startDecodeFile to decode the format.
Hint: THEORAPLAY_startDecodeFile(File path, number of frames(Set to 30), Format too decode (THEORAPLAY_VIDFMT_IYUV)).

```cpp
	THEORAPLAY_Decoder* decoder = THEORAPLAY_startDecodeFile(file, 30, THEORAPLAY_VIDFMT_IYUV);
	if (!decoder)
	{
		LOG("Failed to start decoding file");
		return 0;
	}
```

### TODO 2
Create a video & audio buffer (THEORAPLAY_VideoFrame & THEORAPLAY_AudioPacket) and fill them with THEORAPLAY_getAudioand THEORAPLAY_getVideo.

```cpp
	const THEORAPLAY_AudioPacket* audio = NULL;
	const THEORAPLAY_VideoFrame* video = NULL;

	while (!audio)
	{
		audio = THEORAPLAY_getAudio(decoder);
	}
	while (!video)
	{
		if (!video) video = THEORAPLAY_getVideo(decoder);
	}
```

### TODO 3
In case of error, free the audio & video buffers & stop the decoding.

```cpp
	if (overlay == 0)
	{
		THEORAPLAY_freeAudio(audio);
		THEORAPLAY_freeVideo(video);
		THEORAPLAY_stopDecode(decoder);
		return 0;
	}
  .
  .
  .
	if (SDL_OpenAudio(&player->audioSpec, NULL) != 0 )
	{
		THEORAPLAY_freeAudio(audio);
		THEORAPLAY_freeVideo(video);
		THEORAPLAY_stopDecode(decoder);
		return 0;
	}
```

### TODO 4
Get & process the video data from the decoder.

```cpp
		if (!vid->video)
		{
			vid->video = THEORAPLAY_getVideo(vid->decoder);
		}		
```

### TODO 5
Just like the TODO 3, free the video & audio buffers & stop the decoding, but also destroy the texture.

```cpp
void Video::DestroyVideo(int video)
{
	Video* vid = (Video*)video;

	while (audioQueue != NULL)
	{
		SDL_LockAudio();
		SDL_UnlockAudio();
		SDL_Delay(10);
	}

	SDL_DestroyTexture(vid->texture);
	THEORAPLAY_freeVideo(vid->video);
	THEORAPLAY_freeAudio(vid->audio);
	THEORAPLAY_stopDecode(vid->decoder);
}
```

### TODO 6
Use the video's load function and save it to the video variable (You will need the file pathing & the renderer)

```cpp
	if (app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN && video == 0)
	{
		video = app->video->Load("Assets/Videos/Vibin.ogv", app->render->renderer);
	}
```

### SOURCES

https://maciadalmau.github.io/Video-Player-Research/

https://axelalavedra.github.io/Video-Player-Research/

https://en.wikipedia.org/wiki/Cutscene

https://en.wikipedia.org/wiki/Codec

https://www.gamasutra.com/view/news/170671/Indepth_Playing_with_video.php

https://en.wikipedia.org/wiki/Video_file_format

https://www.theora.org/downloads/

https://icculus.org/theoraplay/

These were used as references for the code:

https://glusoft.com/tutorials/sdl2/playing-theora-video

https://github.com/maciadalmau/Video-Player-Research
