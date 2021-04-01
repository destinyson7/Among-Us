#ifndef MAZE_H
#define MAZE_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// #include "texture.h"
#include "shader.h"
#include "game_object.h"
#include <vector>

#define pb push_back
#define mp make_pair

#define ss second
#define ff first

typedef pair<int, int> pii;
typedef pair<float, float> pff;

using namespace std;

enum Player_Movement
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
};

class Maze
{
public:
	const static int MAZE_WIDTH = 10;
	const static int MAZE_HEIGHT = 8;

	glm::vec3 translate;

	string lighting = "On";

	float EDGE_LENGTH = 0.15f;
	int n_edges = 0;

	vector<pair<pff, pff>> edges;

	GameObject maze[MAZE_HEIGHT][MAZE_WIDTH];
	int dist[MAZE_HEIGHT * MAZE_WIDTH][MAZE_HEIGHT * MAZE_WIDTH];
	// Constructor (inits shaders/shapes)
	Maze(Shader &shader);
	// Destructor
	~Maze();
	// Renders a defined quad textured with given sprite
	void DrawMaze();
	vector<float> GenerateMaze(float edge_length, pair<int, int> start_position);
	void FloydWarshall();

private:
	// Render state
	Shader shader;
	unsigned int quadVAO;
	// Initializes and configures the quad's buffer and vertex attributes
	void initRenderData();
};

#endif
