#include "player.h"

Player::Player(Shader &shader)
{
	this->shader = shader;
	// this->begin = mp(0.025, 0.02);
	this->begin = mp(0.00f, 0.00f);
	this->cur = mp(0.00f, 0.00f);
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

void Player::move(int direction, float dt)
{
	if (direction == UP)
	{
		this->cur.ss += dt;
	}

	else if (direction == DOWN)
	{
		this->cur.ss -= dt;
	}

	else if (direction == LEFT)
	{
		this->cur.ff -= dt;
	}

	else if (direction == RIGHT)
	{
		this->cur.ff += dt;
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
