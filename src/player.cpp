#include "player.h"

Player::Player(Shader &shader, Maze *MazeRenderer)
{
	this->shader = shader;
	// this->begin = mp(0.025, 0.02);

	int r = rand() % MazeRenderer->MAZE_HEIGHT;
	int c = rand() % MazeRenderer->MAZE_WIDTH;

	// this->begin = mp(0.00f, 0.1f);
	// this->cur = mp(0.00f, 0.1f);

	this->begin = mp((float)c * MazeRenderer->EDGE_LENGTH + MazeRenderer->translate.x, (float)r * MazeRenderer->EDGE_LENGTH + MazeRenderer->translate.y);
	this->cur = mp((float)c * MazeRenderer->EDGE_LENGTH + MazeRenderer->translate.x, (float)r * MazeRenderer->EDGE_LENGTH + MazeRenderer->translate.y);
	this->travelled = mp((float)c * MazeRenderer->EDGE_LENGTH, (float)r * MazeRenderer->EDGE_LENGTH);
	this->initRenderData();
}

Player::~Player()
{
	glDeleteVertexArrays(1, &this->quadVAO);
}

void Player::DrawPlayer(Texture2D &texture)
{
	// prepare transformations
	this->shader.Use();
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(this->cur.ff, this->cur.ss, 0.0f)); // first translate (transformations are: scale happens first, then rotation, and then final translation happens; reversed order)

	if (this->going_left)
	{
		model = glm::scale(glm::translate(model, glm::vec3(this->PLAYER_SIZE, 0.0f, 0.0f)), glm::vec3(-1.0f, 1.0f, 1.0f));
	}

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

bool Player::CheckCollision(Maze *MazeRenderer)
{
	for (auto edge : MazeRenderer->edges)
	{
		bool collisionX = (this->cur.ff - MazeRenderer->translate.x + this->PLAYER_SIZE > edge.ff.ff) && (this->cur.ff - MazeRenderer->translate.x < edge.ss.ff);
		bool collisionY = (this->cur.ss - MazeRenderer->translate.y + this->PLAYER_SIZE > edge.ff.ss) && (this->cur.ss - MazeRenderer->translate.y < edge.ss.ss);

		if (collisionX && collisionY)
		{
			// cout << "true" << endl;
			return true;
		}
	}

	// cout << "false" << endl;
	return false;
}

void Player::move(int direction, float dt, Maze *MazeRenderer)
{
	if (direction == UP)
	{
		this->cur.ss += dt;
		this->travelled.ss += dt;
		// this->move_cnt++;

		if (CheckCollision(MazeRenderer))
		{
			this->cur.ss -= dt;
			this->travelled.ss -= dt;
			// this->move_cnt--;
		}
	}

	else if (direction == DOWN)
	{
		this->cur.ss -= dt;
		// this->move_cnt++;
		this->travelled.ss -= dt;

		if (CheckCollision(MazeRenderer))
		{
			this->cur.ss += dt;
			this->travelled.ss += dt;
			// this->move_cnt--;
		}
	}

	else if (direction == LEFT)
	{
		this->going_left = true;
		this->cur.ff -= dt;
		this->travelled.ff -= dt;
		this->move_cnt++;

		if (CheckCollision(MazeRenderer))
		{
			this->cur.ff += dt;
			this->travelled.ff += dt;
			this->move_cnt--;
		}
	}

	else if (direction == RIGHT)
	{
		this->going_left = false;
		this->cur.ff += dt;
		this->travelled.ff += dt;
		this->move_cnt++;

		if (CheckCollision(MazeRenderer))
		{
			this->cur.ff -= dt;
			this->travelled.ff -= dt;
			this->move_cnt--;
		}
	}
}

void Player::initRenderData()
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
		0.0f + this->PLAYER_SIZE, 0.0f, 1.0f, 1.0f,
		0.0f + this->PLAYER_SIZE, 0.0f + this->PLAYER_SIZE, 1.0f, 0.0f,
		0.0f, 0.0f + this->PLAYER_SIZE, 0.0f, 0.0f};

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
