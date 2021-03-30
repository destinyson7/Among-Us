#include "maze.h"

Maze::Maze(Shader &shader)
{
	this->shader = shader;
	this->initRenderData();
}

Maze::~Maze()
{
	glDeleteVertexArrays(1, &this->quadVAO);
}

void Maze::DrawMaze(glm::vec2 position, glm::vec2 size, float rotate, glm::vec3 color)
{
	// prepare transformations
	this->shader.Use();
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(position, 0.0f)); // first translate (transformations are: scale happens first, then rotation, and then final translation happens; reversed order)

	// model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));	// move origin of rotation to center of quad
	// model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f));	// then rotate
	// model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f)); // move origin back

	model = glm::scale(model, glm::vec3(size, 1.0f)); // last scale

	this->shader.SetMatrix4("model", model);

	// render textured quad
	this->shader.SetVector3f("spriteColor", color);

	// glActiveTexture(GL_TEXTURE0);
	// texture.Bind();

	glBindVertexArray(this->quadVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}

void Maze::GenerateMaze(int edge_length, pair<int, int> start_position)
{
	GameObject maze[this->MAZE_WIDTH][this->MAZE_HEIGHT];

	for (int i = 0; i < this->MAZE_WIDTH; i++)
	{
		for (int j = 0; j < this->MAZE_HEIGHT; j++)
		{
			maze[i][j].bottom_left = {(float)(i * edge_length), (float)(j * edge_length)};
			maze[i][j].top_left = {(float)(i * edge_length), (float)((j + 1) * edge_length)};
			maze[i][j].bottom_right = {(float)((i + 1) * edge_length), (float)(j * edge_length)};
			maze[i][j].top_right = {(float)((i + 1) * edge_length), (float)((j + 1) * edge_length)};
		}
	}

	// maze[0][0].IS_BOTTOM_OPEN = true;

	int r = 0, c = 0;
	while (true)
	{
		maze[r][c].visited = true;

		int where = rand() % 4;

		if (where == 0 && c + 1 < this->MAZE_WIDTH && !(maze[r][c + 1].visited))
		{
			maze[r][c].IS_RIGHT_OPEN = 1;
			maze[r][c + 1].IS_LEFT_OPEN = 1;
			c++;
		}

		else if (where == 1 && c - 1 >= 0 && !(maze[r][c - 1].visited))
		{
			maze[r][c].IS_LEFT_OPEN = 1;
			maze[r][c - 1].IS_RIGHT_OPEN = 1;
			c--;
		}

		else if (where == 2 && r + 1 < this->MAZE_HEIGHT && !(maze[r + 1][c].visited))
		{
			maze[r][c].IS_TOP_OPEN = 1;
			maze[r + 1][c].IS_BOTTOM_OPEN = 1;
			r++;
		}

		else if (where == 3 && r - 1 < this->MAZE_HEIGHT && !(maze[r - 1][c].visited))
		{
			maze[r][c].IS_BOTTOM_OPEN = 1;
			maze[r][c - 1].IS_TOP_OPEN = 1;
			r--;
		}

		else
		{
			break;
		}
	}
}

void Maze::initRenderData()
{
	// configure VAO/VBO
	unsigned int VBO;
	float vertices[] = {
		// pos      // tex
		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,

		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f};

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
