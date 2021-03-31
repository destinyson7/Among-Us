#include "game.h"
#include "resource_manager.h"
#include "maze.h"
#include "player.h"
// #include "texture.h"

// Game-related State data
Maze *MazeRenderer;
Player *PlayerRenderer;

Game::Game(unsigned int width, unsigned int height)
	: State(GAME_ACTIVE), Keys(), Width(width), Height(height)
{
}

Game::~Game()
{
	delete MazeRenderer;
	delete PlayerRenderer;
}

void Game::Init()
{
	// load shaders
	ResourceManager::LoadShader("../source/shaders/maze.vert", "../source/shaders/maze.frag", nullptr, "maze");
	ResourceManager::LoadShader("../source/shaders/player.vert", "../source/shaders/player.frag", nullptr, "player");

	// configure shaders

	ResourceManager::GetShader("maze").Use().SetInteger("image", 0);
	ResourceManager::GetShader("player").Use().SetInteger("image", 0);

	// set render-specific controls
	Shader mazeShader = ResourceManager::GetShader("maze");
	MazeRenderer = new Maze(mazeShader);

	// load textures
	ResourceManager::LoadTexture("../source/textures/among_us.png", true, "player");

	Shader playerShader = ResourceManager::GetShader("player");
	PlayerRenderer = new Player(playerShader);
}

void Game::Update(float dt)
{
}

void Game::ProcessInput(float dt)
{
}

void Game::Render()
{
	MazeRenderer->DrawMaze();

	Texture2D playerTexture = ResourceManager::GetTexture("player");
	PlayerRenderer->DrawPlayer(playerTexture);
}
