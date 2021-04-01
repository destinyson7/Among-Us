#ifndef IMPOSTER_H
#define IMPOSTER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

#include "texture.h"
#include "shader.h"
#include "maze.h"
#include "player.h"
#include <iostream>

#define mp make_pair
#define ff first
#define ss second
#define pff pair<float, float>

using namespace std;

template <class Ch, class Tr, class Container>
basic_ostream<Ch, Tr> &operator<<(basic_ostream<Ch, Tr> &os, Container const &x)
{
	os << "{ ";
	for (auto &y : x)
	{
		os << y << " ";
	}
	return os << "}";
}

template <class X, class Y>
ostream &operator<<(ostream &os, pair<X, Y> const &p)
{
	return os << "[" << p.ff << ", " << p.ss << "]";
}

class Imposter
{
public:
	// Constructor (inits shaders/shapes)
	Imposter(Shader &shader, Maze *MazeRenderer);

	const float IMPOSTER_SIZE = 0.1;
	bool exists = true;
	bool going_left = false;

	int mov_cnt = 0;

	pff begin;
	pff cur;
	pff travelled = mp(0.0f, 0.0f);

	// Destructor
	~Imposter();
	// Renders a defined quad textured with given sprite
	void DrawImposter(Texture2D &texture);
	void move(Player *PlayerRenderer, float dt, Maze *MazeRenderer);
	bool CheckCollision(Maze *MazeRenderer);
	bool CheckCollisionWithPlayer(Player *PlayerRenderer);

private:
	// Render state
	Shader shader;
	unsigned int quadVAO;
	// Initializes and configures the quad's buffer and vertex attributes
	void initRenderData();
};

#endif
