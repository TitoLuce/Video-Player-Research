#ifndef __SCENE_H__
#define __SCENE_H__

#include "Module.h"

class Scene : public Module
{
public:

	Scene();

	// Destructor
	virtual ~Scene();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

public:
	SDL_Texture* videoTexture = nullptr;
	SDL_Texture* pauseFrame = nullptr;
	bool skip = false;
	int video;
};

#endif // __SCENE_H__