#ifndef PLAYER_H
#define PLAYER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "texture.h"
#include "shader.h"

#define mp make_pair
#define ff first
#define ss second
#define pff pair<float, float>

using namespace std;

enum Player_Movement
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
};

class Player
{
public:
	// Constructor (inits shaders/shapes)
	Player(Shader &shader);

	const float PLAYER_SIZE = 0.2;

	pff begin;
	pff cur;
	// Destructor
	~Player();
	// Renders a defined quad textured with given sprite
	void DrawPlayer(Texture2D &texture);
	void move(int direction, float dt);

private:
	// Render state
	Shader shader;
	unsigned int quadVAO;
	// Initializes and configures the quad's buffer and vertex attributes
	void initRenderData();
};

#endif