#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Render.h"
#include "Window.h"
#include "Video.h"
#include "VideoScene.h"

#include "Defs.h"
#include "Log.h"


Scene::Scene() : Module()
{
	name.Create("scene");
}

// Destructor
Scene::~Scene()
{}

// Called before render is available
bool Scene::Awake()
{
	LOG("Loading Scene Manager");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool Scene::Start()
{
	return true;
}

// Called each loop iteration
bool Scene::PreUpdate()
{
	if (app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN && video == 0)
	{
		//TODO 6: Use the video's load function and save it to the video variable (You will need the file pathing & the renderer)
		video = app->video->Load("Assets/Videos/Vibin.ogv", app->render->renderer);
	}

	//Skip video by pressing space
	if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		if (skip) { skip = false; }
		else { skip = true; }
	}

	return true;
}

// Called each loop iteration
bool Scene::Update(float dt)
{
	if (video != 0 )
	{
		videoTexture = app->video->UpdateVideo(video);

		app->render->DrawTexture(videoTexture, 0, 0);

		if (app->video->IsPlaying(video) == 0 || skip)
		{
			app->video->DestroyVideo(video);
			 video = 0;
		}
	}

	bool ret = true;

	return ret;
}

// Called each loop iteration
bool Scene::PostUpdate()
{
	return true;
}

// Called before quitting
bool Scene::CleanUp()
{
	LOG("Freeing scene");

	return true;
}