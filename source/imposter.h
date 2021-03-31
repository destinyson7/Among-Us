#ifndef IMPOSTER_H
#define IMPOSTER_H

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

class Imposter
{
public:
	// Constructor (inits shaders/shapes)
	Imposter(Shader &shader);

	const float IMPOSTER_SIZE = 0.1;
	bool exists = true;

	pff begin;
	pff cur;
	// Destructor
	~Imposter();
	// Renders a defined quad textured with given sprite
	void DrawImposter(Texture2D &texture);
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
