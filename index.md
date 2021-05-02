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




```markdown
Syntax highlighted code block

# Header 1
## Header 2
### Header 3

- Bulleted
- List

1. Numbered
2. List

**Bold** and _Italic_ and `Code` text

[Link](url) and ![Image](src)
```

For more details see [GitHub Flavored Markdown](https://guides.github.com/features/mastering-markdown/).

### Jekyll Themes

Your Pages site will use the layout and styles from the Jekyll theme you have selected in your [repository settings](https://github.com/TitoLuce/Video-Player-Research/settings/pages). The name of this theme is saved in the Jekyll `_config.yml` configuration file.

### Support or Contact

Having trouble with Pages? Check out our [documentation](https://docs.github.com/categories/github-pages-basics/) or [contact support](https://support.github.com/contact) and we’ll help you sort it out.
