#pragma once
#include "libs.h"

class Game
{
	enum State {
		GAME_ACTIVE,
		GAME_PAUSED,
		GAME_MAIN_MENU,
		GAME_END
	};

public:
	State gameState;
	GLboolean Keys[1024];
	GLuint Width, Height;
	Game(GLuint width, GLuint height);
	~Game();

	void Init();
	void ProcessInput(GLfloat dt);
	void Update(GLfloat dt);
	void Render();
};

