#include "maze.h"
#include <iostream>
#include <stack>
#include <vector>

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

Maze::Maze(Shader &shader)
{
	this->shader = shader;
	this->translate = glm::vec3(-0.75f, -0.55f, 0.0f);
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

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, this->translate);
	this->shader.SetMatrix4("model", model);

	glBindVertexArray(this->quadVAO);
	glDrawArrays(GL_LINES, 0, this->n_edges);
	glBindVertexArray(0);
}

vector<float> Maze::GenerateMaze(float edge_length, pair<int, int> start_position)
{
	// GameObject maze[this->MAZE_WIDTH][this->MAZE_HEIGHT];

	for (int i = 0; i < this->MAZE_HEIGHT; i++)
	{
		for (int j = 0; j < this->MAZE_WIDTH; j++)
		{
			this->maze[i][j].bottom_left = {(float)(j * edge_length), (float)(i * edge_length)};
			this->maze[i][j].top_left = {(float)(j * edge_length), (float)((i + 1) * edge_length)};
			this->maze[i][j].bottom_right = {(float)((j + 1) * edge_length), (float)(i * edge_length)};
			this->maze[i][j].top_right = {(float)((j + 1) * edge_length), (float)((i + 1) * edge_length)};

			// cout << edge_length << endl;
			// cout << mp((float)((j + 1) * edge_length), (float)((i + 1) * edge_length)) << endl;
		}
	}

	// cout << this->maze << endl;

	stack<pii> s;
	s.push(mp(0, 0));

	while (!s.empty())
	{
		pii top = s.top();
		s.pop();

		bool check = false;

		if (top.ff + 1 < this->MAZE_HEIGHT && !((this->maze[top.ff + 1][top.ss]).visited))
		{
			check = true;
		}

		if (top.ff - 1 >= 0 && !((this->maze[top.ff - 1][top.ss]).visited))
		{
			check = true;
		}

		if (top.ss + 1 < this->MAZE_WIDTH && !((this->maze[top.ff][top.ss + 1]).visited))
		{
			check = true;
		}

		if (top.ss - 1 >= 0 && !((this->maze[top.ff][top.ss - 1]).visited))
		{
			check = true;
		}

		if (!check)
		{
			continue;
		}

		s.push(top);

		while (true)
		{
			int where = rand() % 4;
			int r = top.ff, c = top.ss;

			if (where == 0 && c + 1 < this->MAZE_WIDTH && !((this->maze[r][c + 1]).visited))
			{
				s.push(mp(r, c + 1));
				this->maze[r][c + 1].visited = true;

				this->maze[r][c].IS_RIGHT_OPEN = 1;
				this->maze[r][c + 1].IS_LEFT_OPEN = 1;

				break;
			}

			if (where == 1 && c - 1 >= 0 && !((this->maze[r][c - 1]).visited))
			{
				s.push(mp(r, c - 1));
				this->maze[r][c - 1].visited = true;

				this->maze[r][c].IS_LEFT_OPEN = 1;
				this->maze[r][c - 1].IS_RIGHT_OPEN = 1;

				break;
			}

			if (where == 2 && r + 1 < this->MAZE_HEIGHT && !((this->maze[r + 1][c]).visited))
			{
				s.push(mp(r + 1, c));
				this->maze[r + 1][c].visited = true;

				this->maze[r][c].IS_TOP_OPEN = 1;
				this->maze[r + 1][c].IS_BOTTOM_OPEN = 1;

				break;
			}

			if (where == 3 && r - 1 >= 0 && !((this->maze[r - 1][c]).visited))
			{
				s.push(mp(r - 1, c));
				this->maze[r - 1][c].visited = true;

				this->maze[r][c].IS_BOTTOM_OPEN = 1;
				this->maze[r - 1][c].IS_TOP_OPEN = 1;

				break;
			}
		}
	}

	// cout << "** " << this->n_edges << endl;

	vector<float> vertices_vec;

	// int ind = 0;

	for (int i = 0; i < this->MAZE_HEIGHT; i++)
	{
		for (int j = 0; j < this->MAZE_WIDTH; j++)
		{
			// cout << "****" << endl;

			if (!((this->maze[i][j]).IS_BOTTOM_OPEN))
			{
				vertices_vec.push_back((this->maze[i][j]).bottom_left.first);
				vertices_vec.push_back((this->maze[i][j]).bottom_left.second);

				vertices_vec.push_back((this->maze[i][j]).bottom_right.first);
				vertices_vec.push_back((this->maze[i][j]).bottom_right.second);

				(this->edges).pb(mp(this->maze[i][j].bottom_left, this->maze[i][j].bottom_right));
			}

			if (!((this->maze[i][j]).IS_TOP_OPEN))
			{
				vertices_vec.push_back((this->maze[i][j]).top_left.first);
				vertices_vec.push_back((this->maze[i][j]).top_left.second);

				vertices_vec.push_back((this->maze[i][j]).top_right.first);
				vertices_vec.push_back((this->maze[i][j]).top_right.second);

				(this->edges).pb(mp(this->maze[i][j].top_left, this->maze[i][j].top_right));
			}

			if (!((this->maze[i][j]).IS_LEFT_OPEN))
			{
				vertices_vec.push_back((this->maze[i][j]).bottom_left.first);
				vertices_vec.push_back((this->maze[i][j]).bottom_left.second);

				vertices_vec.push_back((this->maze[i][j]).top_left.first);
				vertices_vec.push_back((this->maze[i][j]).top_left.second);

				(this->edges).pb(mp(this->maze[i][j].bottom_left, this->maze[i][j].top_left));
			}

			if (!((this->maze[i][j]).IS_RIGHT_OPEN))
			{
				vertices_vec.push_back((this->maze[i][j]).bottom_right.first);
				vertices_vec.push_back((this->maze[i][j]).bottom_right.second);

				vertices_vec.push_back((this->maze[i][j]).top_right.first);
				vertices_vec.push_back((this->maze[i][j]).top_right.second);

				(this->edges).pb(mp(this->maze[i][j].bottom_right, this->maze[i][j].top_right));
			}
		}
	}

	this->FloydWarshall();

	// cout << this->n_edges << " " << ind << endl;

	// assert(ind == n_vertices * 4);

	return vertices_vec;
}

void Maze::FloydWarshall()
{
	for (int i = 0; i < this->MAZE_HEIGHT * this->MAZE_WIDTH; i++)
	{
		for (int j = 0; j < this->MAZE_HEIGHT * this->MAZE_WIDTH; j++)
		{
			this->dist[i][j] = 1e8;
		}
	}

	for (int i = 0; i < this->MAZE_HEIGHT * this->MAZE_WIDTH; i++)
	{
		this->dist[i][i] = 0;
	}

	for (int i = 0; i < this->MAZE_HEIGHT; i++)
	{
		for (int j = 0; j < this->MAZE_WIDTH; j++)
		{
			if ((this->maze[i][j]).IS_BOTTOM_OPEN)
			{
				int ff = i * MAZE_WIDTH + j;
				int ss = (i - 1) * MAZE_WIDTH + j;

				this->dist[ff][ss] = 1;
				this->dist[ss][ff] = 1;
			}

			if ((this->maze[i][j]).IS_TOP_OPEN)
			{
				int ff = i * MAZE_WIDTH + j;
				int ss = (i + 1) * MAZE_WIDTH + j;

				this->dist[ff][ss] = 1;
				this->dist[ss][ff] = 1;
			}

			if ((this->maze[i][j]).IS_LEFT_OPEN)
			{
				int ff = i * MAZE_WIDTH + j;
				int ss = i * MAZE_WIDTH + j - 1;

				this->dist[ff][ss] = 1;
				this->dist[ss][ff] = 1;
			}

			if ((this->maze[i][j]).IS_RIGHT_OPEN)
			{
				int ff = i * MAZE_WIDTH + j;
				int ss = i * MAZE_WIDTH + j + 1;

				this->dist[ff][ss] = 1;
				this->dist[ss][ff] = 1;
			}
		}
	}

	int n = MAZE_HEIGHT * MAZE_WIDTH;

	for (int k = 0; k < n; k++)
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				this->dist[i][j] = min(this->dist[i][j], this->dist[i][k] + this->dist[k][j]);
			}
		}
	}
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

	vector<float> vertices_vec = GenerateMaze(this->EDGE_LENGTH, {0, 0});

	int len_vertices = vertices_vec.size();

	this->n_edges = len_vertices;
	// cout << vertices_vec << endl;
	float vertices[len_vertices];

	cout << "len " << len_vertices << endl;

	for (int i = 0; i < len_vertices; i++)
	{
		vertices[i] = vertices_vec[i];
	}

	glGenVertexArrays(1, &this->quadVAO);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(this->quadVAO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void *)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
