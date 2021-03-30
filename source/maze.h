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
	int MAZE_WIDTH = 40;
	int MAZE_HEIGHT = 30;
	int EDGE_LENGTH = 20;
	// Constructor (inits shaders/shapes)
	Maze(Shader &shader);
	// Destructor
	~Maze();
	// Renders a defined quad textured with given sprite
	void DrawMaze(glm::vec2 position, glm::vec2 size = glm::vec2(10.0f, 10.0f), float rotate = 0.0f, glm::vec3 color = glm::vec3(1.0f));
	void GenerateMaze(int edge_length, pair<int, int> start_position);

private:
	// Render state
	Shader shader;
	unsigned int quadVAO;
	// Initializes and configures the quad's buffer and vertex attributes
	void initRenderData();
};

#endif
