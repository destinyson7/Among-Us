#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <glad/glad.h>
#include <glm/glm.hpp>

using namespace std;

class GameObject
{
public:
	bool IS_LEFT_OPEN = 0;
	bool IS_RIGHT_OPEN = 0;
	bool IS_TOP_OPEN = 0;
	bool IS_BOTTOM_OPEN = 0;

	bool visited = false;

	pair<float, float> bottom_left;
	pair<float, float> top_left;
	pair<float, float> bottom_right;
	pair<float, float> top_right;

	GameObject()
	{
	}
};

#endif
