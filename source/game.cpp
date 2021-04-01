#include "game.h"
#include "resource_manager.h"
#include "maze.h"
#include "player.h"
#include "text_renderer.h"
#include "imposter.h"
#include "button.h"

// Game-related State data
Maze *MazeRenderer;
Player *PlayerRenderer;
TextRenderer *Text;
Imposter *ImposterRenderer;
Button *KillButtonRenderer;
Button *ActivateButtonRenderer;
Button *coinRenderer1;
Button *coinRenderer2;
Button *coinRenderer3;
Button *bombRenderer1;
Button *bombRenderer2;

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
	delete ActivateButtonRenderer;
}

void Game::Init()
{
	// load shaders
	ResourceManager::LoadShader("../source/shaders/maze.vert", "../source/shaders/maze.frag", nullptr, "maze");
	ResourceManager::LoadShader("../source/shaders/player.vert", "../source/shaders/player.frag", nullptr, "player");
	ResourceManager::LoadShader("../source/shaders/player.vert", "../source/shaders/player.frag", nullptr, "imposter");
	ResourceManager::LoadShader("../source/shaders/player.vert", "../source/shaders/player.frag", nullptr, "button");

	// configure shaders

	ResourceManager::GetShader("maze").Use().SetInteger("image", 0);
	ResourceManager::GetShader("player").Use().SetInteger("image", 0);
	ResourceManager::GetShader("imposter").Use().SetInteger("image", 0);
	ResourceManager::GetShader("button").Use().SetInteger("image", 0);

	// set render-specific controls
	Shader mazeShader = ResourceManager::GetShader("maze");
	MazeRenderer = new Maze(mazeShader);

	// load textures
	ResourceManager::LoadTexture("../source/textures/among_us.png", true, "player");
	ResourceManager::LoadTexture("../source/textures/imposter.png", true, "imposter");
	ResourceManager::LoadTexture("../source/textures/kill.jpeg", true, "kill_button");
	ResourceManager::LoadTexture("../source/textures/boost.png", true, "activate_button");
	ResourceManager::LoadTexture("../source/textures/coin.png", true, "coin_button");
	ResourceManager::LoadTexture("../source/textures/bomb.png", true, "bomb_button");

	Shader playerShader = ResourceManager::GetShader("player");
	PlayerRenderer = new Player(playerShader);

	Shader imposterShader = ResourceManager::GetShader("imposter");
	ImposterRenderer = new Imposter(imposterShader);

	Shader killButtonShader = ResourceManager::GetShader("button");
	KillButtonRenderer = new Button(killButtonShader, MazeRenderer);

	Shader activateButtonShader = ResourceManager::GetShader("button");
	ActivateButtonRenderer = new Button(activateButtonShader, MazeRenderer);

	Shader coinShader = ResourceManager::GetShader("button");
	coinRenderer1 = new Button(coinShader, MazeRenderer);
	coinRenderer2 = new Button(coinShader, MazeRenderer);
	coinRenderer3 = new Button(coinShader, MazeRenderer);

	coinRenderer1->exists = false;
	coinRenderer2->exists = false;
	coinRenderer3->exists = false;

	Shader bombShader = ResourceManager::GetShader("button");
	bombRenderer1 = new Button(bombShader, MazeRenderer);
	bombRenderer2 = new Button(bombShader, MazeRenderer);

	bombRenderer1->exists = false;
	bombRenderer2->exists = false;

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

	if (ImposterRenderer->exists)
	{
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

		if (KillButtonRenderer->CheckCollision(PlayerRenderer))
		{
			KillButtonRenderer->exists = false;
			ImposterRenderer->exists = false;
		}
	}

	if (ActivateButtonRenderer->exists && ActivateButtonRenderer->CheckCollision(PlayerRenderer))
	{
		ActivateButtonRenderer->exists = false;
		coinRenderer1->exists = true;
		coinRenderer2->exists = true;
		coinRenderer3->exists = true;
		bombRenderer1->exists = true;
		bombRenderer2->exists = true;
	}

	if (coinRenderer1->exists && coinRenderer1->CheckCollision(PlayerRenderer))
	{
		coinRenderer1->exists = false;
		PlayerRenderer->health += 20;
	}

	if (coinRenderer2->exists && coinRenderer2->CheckCollision(PlayerRenderer))
	{
		coinRenderer2->exists = false;
		PlayerRenderer->health += 20;
	}

	if (coinRenderer3->exists && coinRenderer3->CheckCollision(PlayerRenderer))
	{
		coinRenderer3->exists = false;
		PlayerRenderer->health += 20;
	}

	if (bombRenderer1->exists && bombRenderer1->CheckCollision(PlayerRenderer))
	{
		bombRenderer1->exists = false;
		PlayerRenderer->health -= 50;
	}

	if (bombRenderer2->exists && bombRenderer2->CheckCollision(PlayerRenderer))
	{
		bombRenderer2->exists = false;
		PlayerRenderer->health -= 50;
	}

	if ((!(ImposterRenderer->exists)) && ((!(coinRenderer1->exists) && !(coinRenderer2->exists) && !(coinRenderer3->exists)) && !(ActivateButtonRenderer->exists)))
	{
		PlayerRenderer->tasks_completed = 2;
	}

	else if ((!(ImposterRenderer->exists)) || ((!(coinRenderer1->exists) && !(coinRenderer2->exists) && !(coinRenderer3->exists)) && !(ActivateButtonRenderer->exists)))
	{
		PlayerRenderer->tasks_completed = 1;
	}
}

void Game::Render()
{
	MazeRenderer->DrawMaze();

	Texture2D playerTexture = ResourceManager::GetTexture("player");
	PlayerRenderer->DrawPlayer(playerTexture);

	if (ImposterRenderer->exists)
	{
		Texture2D imposterTexture = ResourceManager::GetTexture("imposter");
		ImposterRenderer->DrawImposter(imposterTexture);
	}

	if (KillButtonRenderer->exists)
	{
		Texture2D killButtonTexture = ResourceManager::GetTexture("kill_button");
		KillButtonRenderer->DrawButton(killButtonTexture);
	}

	if (ActivateButtonRenderer->exists)
	{
		Texture2D activateButtonTexture = ResourceManager::GetTexture("activate_button");
		ActivateButtonRenderer->DrawButton(activateButtonTexture);
	}

	if (coinRenderer1->exists)
	{
		Texture2D coinTexture1 = ResourceManager::GetTexture("coin_button");
		coinRenderer1->DrawButton(coinTexture1);
	}

	if (coinRenderer2->exists)
	{
		Texture2D coinTexture2 = ResourceManager::GetTexture("coin_button");
		coinRenderer2->DrawButton(coinTexture2);
	}

	if (coinRenderer3->exists)
	{
		Texture2D coinTexture3 = ResourceManager::GetTexture("coin_button");
		coinRenderer3->DrawButton(coinTexture3);
	}

	if (bombRenderer1->exists)
	{
		Texture2D bombTexture1 = ResourceManager::GetTexture("bomb_button");
		bombRenderer1->DrawButton(bombTexture1);
	}

	if (bombRenderer2->exists)
	{
		Texture2D bombTexture2 = ResourceManager::GetTexture("bomb_button");
		bombRenderer2->DrawButton(bombTexture2);
	}

	Text->RenderText("Health: " + to_string(PlayerRenderer->health), 170.0f, 25.0f, 1.0f);
	Text->RenderText("Tasks: " + to_string(PlayerRenderer->tasks_completed) + "/2", 170.0f, 60.0f, 1.0f);
	Text->RenderText("Light: " + MazeRenderer->lighting, 170.0f, 95.0f, 1.0f);
	Text->RenderText("Time: " + to_string(this->time_remaining), 170.0f, 130.0f, 1.0f);
}
