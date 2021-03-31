#include "game.h"
#include "resource_manager.h"
#include "maze.h"
#include "player.h"
#include "text_renderer.h"
#include "imposter.h"
#include "kill.h"

// Game-related State data
Maze *MazeRenderer;
Player *PlayerRenderer;
TextRenderer *Text;
Imposter *ImposterRenderer;
KillButton *KillButtonRenderer;

Game::Game(unsigned int width, unsigned int height)
	: State(GAME_ACTIVE), Keys(), Width(width), Height(height)
{
}

Game::~Game()
{
	delete MazeRenderer;
	delete PlayerRenderer;
	delete Text;
	delete ImposterRenderer;
	delete KillButtonRenderer;
}

void Game::Init()
{
	// load shaders
	ResourceManager::LoadShader("../source/shaders/maze.vert", "../source/shaders/maze.frag", nullptr, "maze");
	ResourceManager::LoadShader("../source/shaders/player.vert", "../source/shaders/player.frag", nullptr, "player");
	ResourceManager::LoadShader("../source/shaders/player.vert", "../source/shaders/player.frag", nullptr, "imposter");
	ResourceManager::LoadShader("../source/shaders/player.vert", "../source/shaders/player.frag", nullptr, "kill_button");

	// configure shaders

	ResourceManager::GetShader("maze").Use().SetInteger("image", 0);
	ResourceManager::GetShader("player").Use().SetInteger("image", 0);
	ResourceManager::GetShader("imposter").Use().SetInteger("image", 0);
	ResourceManager::GetShader("kill_button").Use().SetInteger("image", 0);

	// set render-specific controls
	Shader mazeShader = ResourceManager::GetShader("maze");
	MazeRenderer = new Maze(mazeShader);

	// load textures
	ResourceManager::LoadTexture("../source/textures/among_us.png", true, "player");
	ResourceManager::LoadTexture("../source/textures/imposter.png", true, "imposter");
	ResourceManager::LoadTexture("../source/textures/kill.png", true, "kill_button");

	Shader playerShader = ResourceManager::GetShader("player");
	PlayerRenderer = new Player(playerShader);

	Shader imposterShader = ResourceManager::GetShader("imposter");
	ImposterRenderer = new Imposter(imposterShader);

	Shader killButtonShader = ResourceManager::GetShader("kill_button");
	KillButtonRenderer = new KillButton(killButtonShader, MazeRenderer);

	Text = new TextRenderer(this->Width, this->Height);
	Text->Load("../source/fonts/OCRAEXT.TTF", 40);
}

void Game::Update(float dt)
{
}

void Game::ProcessInput(float dt)
{
	if (this->Keys[GLFW_KEY_W])
	{
		PlayerRenderer->move(UP, dt, MazeRenderer);
	}

	if (this->Keys[GLFW_KEY_S])
	{
		PlayerRenderer->move(DOWN, dt, MazeRenderer);
	}

	if (this->Keys[GLFW_KEY_A])
	{
		PlayerRenderer->move(LEFT, dt, MazeRenderer);
	}

	if (this->Keys[GLFW_KEY_D])
	{
		PlayerRenderer->move(RIGHT, dt, MazeRenderer);
	}

	if (this->Keys[GLFW_KEY_UP])
	{
		ImposterRenderer->move(UP, dt, MazeRenderer);
	}

	if (this->Keys[GLFW_KEY_DOWN])
	{
		ImposterRenderer->move(DOWN, dt, MazeRenderer);
	}

	if (this->Keys[GLFW_KEY_LEFT])
	{
		ImposterRenderer->move(LEFT, dt, MazeRenderer);
	}

	if (this->Keys[GLFW_KEY_RIGHT])
	{
		ImposterRenderer->move(RIGHT, dt, MazeRenderer);
	}
}

void Game::Render()
{
	MazeRenderer->DrawMaze();

	Texture2D playerTexture = ResourceManager::GetTexture("player");
	PlayerRenderer->DrawPlayer(playerTexture);

	Texture2D imposterTexture = ResourceManager::GetTexture("imposter");
	ImposterRenderer->DrawImposter(imposterTexture);

	Texture2D killButtonTexture = ResourceManager::GetTexture("kill_button");
	KillButtonRenderer->DrawKillButton(killButtonTexture);

	Text->RenderText("Health: " + to_string(PlayerRenderer->health), 170.0f, 25.0f, 1.0f);
	Text->RenderText("Tasks: " + to_string(PlayerRenderer->tasks_completed) + "/2", 170.0f, 60.0f, 1.0f);
	Text->RenderText("Light: " + MazeRenderer->lighting, 170.0f, 95.0f, 1.0f);
	Text->RenderText("Time: " + to_string(this->time_remaining), 170.0f, 130.0f, 1.0f);
}
