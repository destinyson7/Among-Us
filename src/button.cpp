#include "button.h"

Button::Button(Shader &shader, Maze *MazeRenderer)
{
	this->shader = shader;

	this->BUTTON_SIZE = (MazeRenderer->EDGE_LENGTH);

	int c = rand() % MazeRenderer->MAZE_HEIGHT;
	int r = rand() % MazeRenderer->MAZE_WIDTH;

	this->pos = mp((float)r * this->BUTTON_SIZE + MazeRenderer->translate.x, (float)c * this->BUTTON_SIZE + MazeRenderer->translate.y);

	this->initRenderData();
}

Button::~Button()
{
	glDeleteVertexArrays(1, &this->quadVAO);
}

void Button::DrawButton(Texture2D &texture)
{
	// prepare transformations
	this->shader.Use();
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(this->pos.ff, this->pos.ss, 0.0f)); // first translate (transformations are: scale happens first, then rotation, and then final translation happens; reversed order)

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

bool Button::CheckCollision(Player *PlayerRenderer)
{

	bool collisionX = (this->pos.ff + this->BUTTON_SIZE > PlayerRenderer->cur.ff) && (this->pos.ff < PlayerRenderer->cur.ff + PlayerRenderer->PLAYER_SIZE);
	bool collisionY = (this->pos.ss + this->BUTTON_SIZE > PlayerRenderer->cur.ss) && (this->pos.ss < PlayerRenderer->cur.ss + PlayerRenderer->PLAYER_SIZE);

	if (collisionX && collisionY)
	{
		// cout << "true" << endl;
		return true;
	}

	// cout << "false" << endl;
	return false;
}

void Button::initRenderData()
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
		0.0f + this->BUTTON_SIZE, 0.0f, 1.0f, 1.0f,
		0.0f + this->BUTTON_SIZE, 0.0f + this->BUTTON_SIZE, 1.0f, 0.0f,
		0.0f, 0.0f + this->BUTTON_SIZE, 0.0f, 0.0f};

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
