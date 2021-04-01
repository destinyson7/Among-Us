#include "imposter.h"

Imposter::Imposter(Shader &shader, Maze *MazeRenderer)
{
	this->shader = shader;

	int c = rand() % MazeRenderer->MAZE_HEIGHT;
	int r = rand() % MazeRenderer->MAZE_WIDTH;

	this->begin = mp((float)r * MazeRenderer->EDGE_LENGTH + MazeRenderer->translate.x, (float)c * MazeRenderer->EDGE_LENGTH + MazeRenderer->translate.y);
	this->cur = mp((float)r * MazeRenderer->EDGE_LENGTH + MazeRenderer->translate.x, (float)c * MazeRenderer->EDGE_LENGTH + MazeRenderer->translate.y);

	this->initRenderData();
}

Imposter::~Imposter()
{
	glDeleteVertexArrays(1, &this->quadVAO);
}

void Imposter::DrawImposter(Texture2D &texture)
{
	// prepare transformations
	this->shader.Use();
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(this->cur.ff, this->cur.ss, 0.0f)); // first translate (transformations are: scale happens first, then rotation, and then final translation happens; reversed order)

	// model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));	// move origin of rotation to center of quad
	// model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f));	// then rotate
	// model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f)); // move origin back

	// model = glm::scale(model, glm::vec3(size, 1.0f)); // last scale

	this->shader.SetMatrix4("model", model);

	// render textured quad
	// this->shader.SetVector3f("spriteColor", color);

	glActiveTexture(GL_TEXTURE0);
	texture.Bind();

	glBindVertexArray(this->quadVAO);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
	glBindVertexArray(0);
}

bool Imposter::CheckCollision(Maze *MazeRenderer)
{
	for (auto edge : MazeRenderer->edges)
	{
		bool collisionX = (this->cur.ff - MazeRenderer->translate.x + this->IMPOSTER_SIZE >= edge.ff.ff) && (this->cur.ff - MazeRenderer->translate.x <= edge.ss.ff);
		bool collisionY = (this->cur.ss - MazeRenderer->translate.y + this->IMPOSTER_SIZE >= edge.ff.ss) && (this->cur.ss - MazeRenderer->translate.y <= edge.ss.ss);

		if (collisionX && collisionY)
		{
			// cout << "true" << endl;
			return true;
		}
	}

	// cout << "false" << endl;
	return false;
}

bool Imposter::CheckCollisionWithPlayer(Player *PlayerRenderer)
{

	bool collisionX = (this->cur.ff + this->IMPOSTER_SIZE >= PlayerRenderer->cur.ff) && (this->cur.ff <= PlayerRenderer->cur.ff + PlayerRenderer->PLAYER_SIZE);
	bool collisionY = (this->cur.ss + this->IMPOSTER_SIZE >= PlayerRenderer->cur.ss) && (this->cur.ss <= PlayerRenderer->cur.ss + PlayerRenderer->PLAYER_SIZE);

	if (collisionX && collisionY)
	{
		// cout << "true" << endl;
		return true;
	}

	// cout << "false" << endl;
	return false;
}

void Imposter::move(int direction, float dt, Maze *MazeRenderer)
{
	if (direction == UP)
	{
		this->cur.ss += dt;

		if (CheckCollision(MazeRenderer))
		{
			this->cur.ss -= dt;
		}
	}

	else if (direction == DOWN)
	{
		this->cur.ss -= dt;

		if (CheckCollision(MazeRenderer))
		{
			this->cur.ss += dt;
		}
	}

	else if (direction == LEFT)
	{
		this->cur.ff -= dt;

		if (CheckCollision(MazeRenderer))
		{
			this->cur.ff += dt;
		}
	}

	else if (direction == RIGHT)
	{
		this->cur.ff += dt;

		if (CheckCollision(MazeRenderer))
		{
			this->cur.ff -= dt;
		}
	}
}

void Imposter::initRenderData()
{
	// configure VAO/VBO
	unsigned int VBO;
	// float vertices[] = {
	// 	// pos      // tex
	// 	this->begin.ff, this->begin.ss, 0.0f, 1.0f,
	// 	this->begin.ff + this->PLAYER_SIZE, this->begin.ss, 1.0f, 1.0f,
	// 	this->begin.ff + this->PLAYER_SIZE, this->begin.ss + this->PLAYER_SIZE, 1.0f, 0.0f,
	// 	this->begin.ff, this->begin.ss + this->PLAYER_SIZE, 0.0f, 0.0f};

	float vertices[] = {
		// pos      // tex
		0.0f, 0.0f, 0.0f, 1.0f,
		0.0f + this->IMPOSTER_SIZE, 0.0f, 1.0f, 1.0f,
		0.0f + this->IMPOSTER_SIZE, 0.0f + this->IMPOSTER_SIZE, 1.0f, 0.0f,
		0.0f, 0.0f + this->IMPOSTER_SIZE, 0.0f, 0.0f};

	glGenVertexArrays(1, &this->quadVAO);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(this->quadVAO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
