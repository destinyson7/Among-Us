#ifndef KILL_H
#define KILL_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

#include "texture.h"
#include "shader.h"
#include "maze.h"
#include "player.h"

#define mp make_pair
#define ff first
#define ss second
#define pff pair<float, float>

using namespace std;

class KillButton
{
public:
	// Constructor (inits shaders/shapes)
	KillButton(Shader &shader, Maze *MazeRenderer);

	float BUTTON_SIZE;
	bool exists = true;
	pff pos;

	// Destructor
	~KillButton();
	// Renders a defined quad textured with given sprite
	void DrawKillButton(Texture2D &texture);
	// bool CheckCollision(Player *PlayerRenderer);

private:
	// Render state
	Shader shader;
	unsigned int quadVAO;
	// Initializes and configures the quad's buffer and vertex attributes
	void initRenderData();
};

#endif
