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

void Maze::DrawMaze()
{
	// prepare transformations
	this->shader.Use();

	glBindVertexArray(this->quadVAO);
	glDrawArrays(GL_LINES, 0, this->n_edges * 2);
	glBindVertexArray(0);
}

float *Maze::GenerateMaze(int edge_length, pair<int, int> start_position)
{
	// GameObject maze[this->MAZE_WIDTH][this->MAZE_HEIGHT];

	for (int i = 0; i < this->MAZE_WIDTH; i++)
	{
		for (int j = 0; j < this->MAZE_HEIGHT; j++)
		{
			this->maze[i][j].bottom_left = {(float)(i * edge_length), (float)(j * edge_length)};
			this->maze[i][j].top_left = {(float)(i * edge_length), (float)((j + 1) * edge_length)};
			this->maze[i][j].bottom_right = {(float)((i + 1) * edge_length), (float)(j * edge_length)};
			this->maze[i][j].top_right = {(float)((i + 1) * edge_length), (float)((j + 1) * edge_length)};
		}
	}

	// maze[0][0].IS_BOTTOM_OPEN = true;

	this->n_edges = this->MAZE_WIDTH * this->MAZE_HEIGHT * 4;

	int r = start_position.first, c = start_position.second;
	while (true)
	{
		this->maze[r][c].visited = true;

		int where = rand() % 4;

		if (where == 0 && c + 1 < this->MAZE_WIDTH && !((this->maze[r][c + 1]).visited))
		{
			this->maze[r][c].IS_RIGHT_OPEN = 1;
			this->maze[r][c + 1].IS_LEFT_OPEN = 1;
			this->n_edges -= 2;
			c++;
		}

		else if (where == 1 && c - 1 >= 0 && !((this->maze[r][c - 1]).visited))
		{
			this->maze[r][c].IS_LEFT_OPEN = 1;
			this->maze[r][c - 1].IS_RIGHT_OPEN = 1;
			this->n_edges -= 2;
			c--;
		}

		else if (where == 2 && r + 1 < this->MAZE_HEIGHT && !((this->maze[r + 1][c]).visited))
		{
			this->maze[r][c].IS_TOP_OPEN = 1;
			this->maze[r + 1][c].IS_BOTTOM_OPEN = 1;
			this->n_edges -= 2;
			r++;
		}

		else if (where == 3 && r - 1 < this->MAZE_HEIGHT && !((this->maze[r - 1][c]).visited))
		{
			this->maze[r][c].IS_BOTTOM_OPEN = 1;
			this->maze[r][c - 1].IS_TOP_OPEN = 1;
			this->n_edges -= 2;
			r--;
		}

		else
		{
			break;
		}
	}

	float *vertices = new float[this->n_edges * 4];
	int ind = 0;

	for (int i = 0; i < this->MAZE_WIDTH; i++)
	{
		for (int j = 0; j < this->MAZE_HEIGHT; i++)
		{
			if ((this->maze[i][j]).IS_BOTTOM_OPEN)
			{
				vertices[ind++] = (this->maze[i][j]).bottom_left.first;
				vertices[ind++] = (this->maze[i][j]).bottom_left.second;

				vertices[ind++] = (this->maze[i][j]).bottom_right.first;
				vertices[ind++] = (this->maze[i][j]).bottom_right.second;
			}

			if ((this->maze[i][j]).IS_TOP_OPEN)
			{
				vertices[ind++] = (this->maze[i][j]).top_left.first;
				vertices[ind++] = (this->maze[i][j]).top_left.second;

				vertices[ind++] = (this->maze[i][j]).top_right.first;
				vertices[ind++] = (this->maze[i][j]).top_right.second;
			}

			if ((this->maze[i][j]).IS_LEFT_OPEN)
			{
				vertices[ind++] = (this->maze[i][j]).bottom_left.first;
				vertices[ind++] = (this->maze[i][j]).bottom_left.second;

				vertices[ind++] = (this->maze[i][j]).top_left.first;
				vertices[ind++] = (this->maze[i][j]).top_left.second;
			}

			if ((this->maze[i][j]).IS_RIGHT_OPEN)
			{
				vertices[ind++] = (this->maze[i][j]).top_right.first;
				vertices[ind++] = (this->maze[i][j]).top_right.second;

				vertices[ind++] = (this->maze[i][j]).bottom_right.first;
				vertices[ind++] = (this->maze[i][j]).bottom_right.second;
			}
		}
	}

	// assert(ind == n_vertices * 4);

	return vertices;
}

void Maze::initRenderData()
{
	// configure VAO/VBO
	unsigned int VBO;
	// float vertices[] = {
	// 	// pos      // tex
	// 	0.0f, 1.0f, 0.0f, 1.0f,
	// 	1.0f, 0.0f, 1.0f, 0.0f,
	// 	0.0f, 0.0f, 0.0f, 0.0f,

	// 	0.0f, 1.0f, 0.0f, 1.0f,
	// 	1.0f, 1.0f, 1.0f, 1.0f,
	// 	1.0f, 0.0f, 1.0f, 0.0f};

	float *vertices = GenerateMaze(this->EDGE_LENGTH, {0, 0});

	glGenVertexArrays(1, &this->quadVAO);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, n_edges * 4 * sizeof(float), vertices, GL_STATIC_DRAW);

	glBindVertexArray(this->quadVAO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void *)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
