#ifndef MAZE_H
#define MAZE_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// #include "texture.h"
#include "shader.h"
#include "game_object.h"

using namespace std;

class Maze
{
public:
	const static int MAZE_WIDTH = 800;
	const static int MAZE_HEIGHT = 600;
	float EDGE_LENGTH = 2500.0f;
	int n_edges = 0;

	GameObject maze[MAZE_WIDTH][MAZE_HEIGHT];
	// Constructor (inits shaders/shapes)
	Maze(Shader &shader);
	// Destructor
	~Maze();
	// Renders a defined quad textured with given sprite
	void DrawMaze();
	float *GenerateMaze(int edge_length, pair<int, int> start_position);

private:
	// Render state
	Shader shader;
	unsigned int quadVAO;
	// Initializes and configures the quad's buffer and vertex attributes
	void initRenderData();
};

#endif
