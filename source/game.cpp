#include "game.h"
#include "resource_manager.h"
#include "maze.h"
#include "player.h"
// #include "texture.h"

// Game-related State data
Maze *Renderer;
Player *PlayerRenderer;

Game::Game(unsigned int width, unsigned int height)
	: State(GAME_ACTIVE), Keys(), Width(width), Height(height)
{
}

Game::~Game()
{
	delete Renderer;
	delete PlayerRenderer;
}

void Game::Init()
{
	// load shaders
	// ResourceManager::LoadShader("../source/shaders/shader.vert", "../source/shaders/shader.frag", nullptr, "sprite");
	ResourceManager::LoadShader("../source/shaders/player.vert", "../source/shaders/player.frag", nullptr, "player");

	// configure shaders
	glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->Width),
									  static_cast<float>(this->Height), 0.0f, -1.0f, 1.0f);

	// ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
	// ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);

	ResourceManager::GetShader("player").Use().SetInteger("image", 0);
	ResourceManager::GetShader("player").SetMatrix4("projection", projection);

	// set render-specific controls
	// Shader spriteShader = ResourceManager::GetShader("sprite");
	// Renderer = new Maze(spriteShader);

	// Renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));
	// load textures
	ResourceManager::LoadTexture("../source/textures/among_us.png", true, "face");

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
	// Renderer->DrawMaze();

	Texture2D playerTexture = ResourceManager::GetTexture("face");
	PlayerRenderer->DrawPlayer(playerTexture, glm::vec2(200.0f, 200.0f), glm::vec2(300.0f, 400.0f), 45.0f, glm::vec3(0.0f, 1.0f, 0.0f));
}
