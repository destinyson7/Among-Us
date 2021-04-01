#ifndef PLAYER_H
#define PLAYER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

#include "texture.h"
#include "shader.h"
#include "maze.h"

#define mp make_pair
#define ff first
#define ss second
#define pff pair<float, float>

using namespace std;

class Player
{
public:
	// Constructor (inits shaders/shapes)
	Player(Shader &shader, Maze *MazeRenderer);

	const float PLAYER_SIZE = 0.1;
	int health = 100;
	int tasks_completed = 0;
	int move_cnt = 0;
	bool going_left = false;

	pff begin;
	pff cur;
	pff travelled = mp(0.0f, 0.0f);
	// Destructor
	~Player();
	// Renders a defined quad textured with given sprite
	void DrawPlayer(Texture2D &texture);
	void move(int direction, float dt, Maze *MazeRenderer);
	bool CheckCollision(Maze *MazeRenderer);

private:
	// Render state
	Shader shader;
	unsigned int quadVAO;
	// Initializes and configures the quad's buffer and vertex attributes
	void initRenderData();
};

#endif
