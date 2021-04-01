#include "imposter.h"

Imposter::Imposter(Shader &shader, Maze *MazeRenderer)
{
	this->shader = shader;

	int r = rand() % MazeRenderer->MAZE_HEIGHT;
	int c = rand() % MazeRenderer->MAZE_WIDTH;

	this->begin = mp((float)c * MazeRenderer->EDGE_LENGTH + MazeRenderer->translate.x, (float)r * MazeRenderer->EDGE_LENGTH + MazeRenderer->translate.y);
	this->cur = mp((float)c * MazeRenderer->EDGE_LENGTH + MazeRenderer->translate.x, (float)r * MazeRenderer->EDGE_LENGTH + MazeRenderer->translate.y);
	this->travelled = mp((float)c * MazeRenderer->EDGE_LENGTH, (float)r * MazeRenderer->EDGE_LENGTH);

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

	if (this->going_left)
	{
		model = glm::scale(glm::translate(model, glm::vec3(this->IMPOSTER_SIZE, 0.0f, 0.0f)), glm::vec3(-1.0f, 1.0f, 1.0f));
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

bool Imposter::CheckCollision(Maze *MazeRenderer)
{
	for (auto edge : MazeRenderer->edges)
	{
		bool collisionX = (this->cur.ff - MazeRenderer->translate.x + this->IMPOSTER_SIZE > edge.ff.ff) && (this->cur.ff - MazeRenderer->translate.x < edge.ss.ff);
		bool collisionY = (this->cur.ss - MazeRenderer->translate.y + this->IMPOSTER_SIZE > edge.ff.ss) && (this->cur.ss - MazeRenderer->translate.y < edge.ss.ss);

		if (collisionX && collisionY)
		{
			// cout << this->travelled << " " << edge << " " << MazeRenderer->translate.x << " " << MazeRenderer->translate.y << endl;
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

void Imposter::move(Player *PlayerRenderer, float dt, Maze *MazeRenderer)
{
	int player_r = PlayerRenderer->travelled.ss / MazeRenderer->EDGE_LENGTH;
	int player_c = PlayerRenderer->travelled.ff / MazeRenderer->EDGE_LENGTH;

	int imposter_r = this->travelled.ss / MazeRenderer->EDGE_LENGTH;
	int imposter_c = this->travelled.ff / MazeRenderer->EDGE_LENGTH;

	int i = imposter_r * MazeRenderer->MAZE_WIDTH + imposter_c;
	int j = player_r * MazeRenderer->MAZE_WIDTH + player_c;

	int k1 = (imposter_r + 1) * MazeRenderer->MAZE_WIDTH + imposter_c;
	int k2 = (imposter_r - 1) * MazeRenderer->MAZE_WIDTH + imposter_c;
	int k3 = imposter_r * MazeRenderer->MAZE_WIDTH + imposter_c + 1;
	int k4 = imposter_r * MazeRenderer->MAZE_WIDTH + imposter_c - 1;

	// vector<int> v = {player_r, player_c, imposter_r, imposter_c, i, j, k1, k2, k3, k4};
	// cout << v << endl;

	pff old_coord = this->travelled;
	pff want_coord = this->travelled;

	// cout << mp(imposter_r, imposter_c) << " " << mp(player_r, player_c) << endl;

	if (MazeRenderer->maze[imposter_r][imposter_c].IS_TOP_OPEN && (MazeRenderer->dist[i][j] == MazeRenderer->dist[i][k1] + MazeRenderer->dist[k1][j]))
	{
		// cout << "go from " << mp(imposter_r, imposter_c) << " to " << mp(imposter_r + 1, imposter_c) << endl;
		this->cur.ss += dt / 4;
		this->travelled.ss += dt / 4;
		want_coord = this->travelled;
		// this->mov_cnt++;

		if (this->CheckCollision(MazeRenderer))
		{
			// this->mov_cnt--;
			// cout << "top collision detected" << endl;
			this->cur.ss -= dt / 4;
			this->travelled.ss -= dt / 4;
		}

		// assert(!CheckCollision(MazeRenderer));
	}

	else if (MazeRenderer->maze[imposter_r][imposter_c].IS_BOTTOM_OPEN && (MazeRenderer->dist[i][j] == MazeRenderer->dist[i][k2] + MazeRenderer->dist[k2][j]))
	{
		// cout << "go from " << mp(imposter_r, imposter_c) << " to " << mp(imposter_r - 1, imposter_c) << endl;
		this->cur.ss -= dt / 4;
		this->travelled.ss -= dt / 4;
		want_coord = this->travelled;
		// this->mov_cnt++;

		if (this->CheckCollision(MazeRenderer))
		{
			// this->mov_cnt--;
			// cout << "bottom collision detected" << endl;
			this->cur.ss += dt / 4;
			this->travelled.ss += dt / 4;
		}

		// assert(!CheckCollision(MazeRenderer));
	}

	else if (MazeRenderer->maze[imposter_r][imposter_c].IS_RIGHT_OPEN && (MazeRenderer->dist[i][j] == MazeRenderer->dist[i][k3] + MazeRenderer->dist[k3][j]))
	{
		// cout << "go from " << mp(imposter_r, imposter_c) << " to " << mp(imposter_r, imposter_c + 1) << endl;
		this->cur.ff += dt / 4;
		this->travelled.ff += dt / 4;
		want_coord = this->travelled;
		this->mov_cnt++;
		this->going_left = false;

		if (this->CheckCollision(MazeRenderer))
		{
			this->mov_cnt--;
			// cout << "right collision detected" << endl;
			this->cur.ff -= dt / 4;
			this->travelled.ff -= dt / 4;
		}

		// assert(!CheckCollision(MazeRenderer));
	}

	else if (MazeRenderer->maze[imposter_r][imposter_c].IS_LEFT_OPEN && (MazeRenderer->dist[i][j] == MazeRenderer->dist[i][k4] + MazeRenderer->dist[k4][j]))
	{
		// cout << "go from " << mp(imposter_r, imposter_c) << " to " << mp(imposter_r, imposter_c - 1) << endl;
		this->cur.ff -= dt / 4;
		this->travelled.ff -= dt / 4;
		want_coord = this->travelled;
		this->mov_cnt++;

		this->going_left = true;

		if (this->CheckCollision(MazeRenderer))
		{
			this->mov_cnt--;
			// cout << "left collision detected" << endl;
			this->cur.ff += dt / 4;
			this->travelled.ff += dt / 4;
		}

		// assert(!CheckCollision(MazeRenderer));
	}

	pff new_coord = this->travelled;

	if (old_coord == new_coord && old_coord != want_coord)
	{
		if (old_coord.ff == want_coord.ff)
		{
			this->cur.ff -= dt / 4;
			this->travelled.ff -= dt / 4;
			this->mov_cnt++;
			this->going_left = true;

			// cout << "going left" << endl;

			if (this->CheckCollision(MazeRenderer))
			{
				this->mov_cnt--;
				this->cur.ff += dt / 4;
				this->travelled.ff += dt / 4;
			}
		}

		else if (old_coord.ss == want_coord.ss)
		{
			this->cur.ss -= dt / 4;
			this->travelled.ss -= dt / 4;
			// this->mov_cnt++;
			// cout << "going down" << endl;

			if (this->CheckCollision(MazeRenderer))
			{
				// this->mov_cnt--;
				this->cur.ss += dt / 4;
				this->travelled.ss += dt / 4;
			}
		}
	}

	// if (direction == UP)
	// {
	// 	this->cur.ss += dt;

	// 	if (CheckCollision(MazeRenderer))
	// 	{
	// 		cout << "top collision detected" << endl;
	// 		this->cur.ss -= dt;
	// 	}
	// }

	// else if (direction == DOWN)
	// {
	// 	this->cur.ss -= dt;

	// 	if (CheckCollision(MazeRenderer))
	// 	{
	// 		cout << "bottom collision detected" << endl;
	// 		this->cur.ss += dt;
	// 	}
	// }

	// else if (direction == LEFT)
	// {
	// 	this->cur.ff -= dt;

	// 	if (CheckCollision(MazeRenderer))
	// 	{
	// 		cout << "left collision detected" << endl;
	// 		this->cur.ff += dt;
	// 	}
	// }

	// else if (direction == RIGHT)
	// {
	// 	this->cur.ff += dt;

	// 	if (CheckCollision(MazeRenderer))
	// 	{
	// 		cout << "right collision detected" << endl;
	// 		this->cur.ff -= dt;
	// 	}
	// }
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
