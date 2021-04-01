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
Button *exitDoorRenderer;

Game::Game(unsigned int width, unsigned int height)
	: State(GAME_ACTIVE), Keys(), KeysProcessed(), Width(width), Height(height)
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
	delete coinRenderer1;
	delete coinRenderer2;
	delete coinRenderer3;
	delete bombRenderer1;
	delete bombRenderer2;
	delete exitDoorRenderer;
}

void Game::Init()
{
	// load shaders
	ResourceManager::LoadShader("../src/shaders/maze.vert", "../src/shaders/maze.frag", nullptr, "maze");
	ResourceManager::LoadShader("../src/shaders/player.vert", "../src/shaders/player.frag", nullptr, "player");
	ResourceManager::LoadShader("../src/shaders/player.vert", "../src/shaders/player.frag", nullptr, "imposter");
	ResourceManager::LoadShader("../src/shaders/player.vert", "../src/shaders/player.frag", nullptr, "button");

	// configure shaders

	ResourceManager::GetShader("maze").Use().SetInteger("image", 0);
	ResourceManager::GetShader("player").Use().SetInteger("image", 0);
	ResourceManager::GetShader("imposter").Use().SetInteger("image", 0);
	ResourceManager::GetShader("button").Use().SetInteger("image", 0);
	ResourceManager::GetShader("maze").Use().SetVector3f("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
	ResourceManager::GetShader("player").Use().SetVector3f("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
	ResourceManager::GetShader("imposter").Use().SetVector3f("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
	ResourceManager::GetShader("button").Use().SetVector3f("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));

	// set render-specific controls
	Shader mazeShader = ResourceManager::GetShader("maze");
	MazeRenderer = new Maze(mazeShader);

	// load textures
	ResourceManager::LoadTexture("../src/textures/among_us.png", true, "player");
	ResourceManager::LoadTexture("../src/textures/imposter.png", true, "imposter");
	ResourceManager::LoadTexture("../src/textures/kill.jpeg", true, "kill_button");
	ResourceManager::LoadTexture("../src/textures/boost.png", true, "activate_button");
	ResourceManager::LoadTexture("../src/textures/coin.png", true, "coin_button");
	ResourceManager::LoadTexture("../src/textures/bomb.png", true, "bomb_button");
	ResourceManager::LoadTexture("../src/textures/exit.jpeg", false, "exit_button");

	ResourceManager::LoadTexture("../src/textures/player0.png", true, "player0");
	ResourceManager::LoadTexture("../src/textures/player1.png", true, "player1");
	ResourceManager::LoadTexture("../src/textures/player2.png", true, "player2");
	ResourceManager::LoadTexture("../src/textures/player3.png", true, "player3");
	ResourceManager::LoadTexture("../src/textures/player4.png", true, "player4");

	ResourceManager::LoadTexture("../src/textures/imposter0.png", true, "imposter0");
	ResourceManager::LoadTexture("../src/textures/imposter1.png", true, "imposter1");
	ResourceManager::LoadTexture("../src/textures/imposter2.png", true, "imposter2");
	ResourceManager::LoadTexture("../src/textures/imposter3.png", true, "imposter3");
	ResourceManager::LoadTexture("../src/textures/imposter4.png", true, "imposter4");

	Shader playerShader = ResourceManager::GetShader("player");
	PlayerRenderer = new Player(playerShader, MazeRenderer);

	Shader imposterShader = ResourceManager::GetShader("imposter");
	ImposterRenderer = new Imposter(imposterShader, MazeRenderer);

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

	Shader exitShader = ResourceManager::GetShader("button");
	exitDoorRenderer = new Button(exitShader, MazeRenderer);
	exitDoorRenderer->exists = false;

	Text = new TextRenderer(this->Width, this->Height);
	Text->Load("../src/fonts/OCRAEXT.TTF", 40);
}

void Game::Update(float dt)
{
	if (this->are_lights_off)
	{
		this->iter_cnt++;

		if (this->iter_cnt == 60)
		{
			this->iter_cnt = 0;
			PlayerRenderer->health++;
		}
	}

	ResourceManager::GetShader("maze").Use().SetVector3f("lightPos", glm::vec3(PlayerRenderer->cur.ff, PlayerRenderer->cur.ss, 1.0f));
	ResourceManager::GetShader("player").Use().SetVector3f("lightPos", glm::vec3(PlayerRenderer->cur.ff, PlayerRenderer->cur.ss, 1.0f));
	ResourceManager::GetShader("imposter").Use().SetVector3f("lightPos", glm::vec3(PlayerRenderer->cur.ff, PlayerRenderer->cur.ss, 1.0f));
	ResourceManager::GetShader("button").Use().SetVector3f("lightPos", glm::vec3(PlayerRenderer->cur.ff, PlayerRenderer->cur.ss, 1.0f));

	if (this->are_lights_off)
	{
		ResourceManager::GetShader("maze").Use().SetFloat("lightCutOff", 1.1f);
		ResourceManager::GetShader("player").Use().SetFloat("lightCutOff", 1.1f);
		ResourceManager::GetShader("imposter").Use().SetFloat("lightCutOff", 1.1f);
		ResourceManager::GetShader("button").Use().SetFloat("lightCutOff", 1.1f);

		ResourceManager::GetShader("maze").Use().SetInteger("isOn", 0);
		ResourceManager::GetShader("player").Use().SetInteger("isOn", 0);
		ResourceManager::GetShader("imposter").Use().SetInteger("isOn", 0);
		ResourceManager::GetShader("button").Use().SetInteger("isOn", 0);
	}

	else
	{
		ResourceManager::GetShader("maze").Use().SetFloat("lightCutOff", 100000.0f);
		ResourceManager::GetShader("player").Use().SetFloat("lightCutOff", 100000.0f);
		ResourceManager::GetShader("imposter").Use().SetFloat("lightCutOff", 100000.0f);
		ResourceManager::GetShader("button").Use().SetFloat("lightCutOff", 100000.0f);

		ResourceManager::GetShader("maze").Use().SetInteger("isOn", 1);
		ResourceManager::GetShader("player").Use().SetInteger("isOn", 1);
		ResourceManager::GetShader("imposter").Use().SetInteger("isOn", 1);
		ResourceManager::GetShader("button").Use().SetInteger("isOn", 1);
	}
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

	if (this->Keys[GLFW_KEY_T] && !this->KeysProcessed[GLFW_KEY_T])
	{
		this->are_lights_off ^= true;
		this->KeysProcessed[GLFW_KEY_T] = true;

		if (MazeRenderer->lighting == "On")
		{
			MazeRenderer->lighting = "Off";
		}

		else
		{
			MazeRenderer->lighting = "On";
		}
	}

	if (ImposterRenderer->exists)
	{
		ImposterRenderer->move(PlayerRenderer, dt, MazeRenderer);
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
		PlayerRenderer->health = max(0, PlayerRenderer->health);
	}

	if (bombRenderer2->exists && bombRenderer2->CheckCollision(PlayerRenderer))
	{
		bombRenderer2->exists = false;
		PlayerRenderer->health -= 50;
		PlayerRenderer->health = max(0, PlayerRenderer->health);
	}

	if ((!(ImposterRenderer->exists)) && ((!(coinRenderer1->exists) && !(coinRenderer2->exists) && !(coinRenderer3->exists)) && !(ActivateButtonRenderer->exists)))
	{
		PlayerRenderer->tasks_completed = 2;
	}

	else if ((!(ImposterRenderer->exists)) || ((!(coinRenderer1->exists) && !(coinRenderer2->exists) && !(coinRenderer3->exists)) && !(ActivateButtonRenderer->exists)))
	{
		PlayerRenderer->tasks_completed = 1;
	}

	if (PlayerRenderer->tasks_completed == 2)
	{
		exitDoorRenderer->exists = true;
	}

	if (exitDoorRenderer->exists && exitDoorRenderer->CheckCollision(PlayerRenderer))
	{
		this->State = GAME_WIN;
	}

	if (PlayerRenderer->health <= 0 || this->time_remaining <= 0)
	{
		this->State = GAME_LOSE;
	}
}

void Game::Render()
{
	if (this->State == GAME_ACTIVE)
	{
		MazeRenderer->DrawMaze();

		string texture_cnt = "player" + to_string((PlayerRenderer->move_cnt / 7) % 5);
		Texture2D playerTexture = ResourceManager::GetTexture(texture_cnt);
		PlayerRenderer->DrawPlayer(playerTexture);

		if (ImposterRenderer->exists)
		{
			if (ImposterRenderer->CheckCollisionWithPlayer(PlayerRenderer))
			{
				ImposterRenderer->exists = false;
				PlayerRenderer->health -= 75;
				PlayerRenderer->health = max(0, PlayerRenderer->health);
				KillButtonRenderer->exists = false;
			}

			if (KillButtonRenderer->CheckCollision(PlayerRenderer))
			{
				KillButtonRenderer->exists = false;
				ImposterRenderer->exists = false;
			}
		}

		if (ImposterRenderer->exists)
		{
			string texture_cnt1 = "imposter" + to_string((ImposterRenderer->mov_cnt / 7) % 5);
			Texture2D imposterTexture = ResourceManager::GetTexture(texture_cnt1);
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

		if (exitDoorRenderer->exists)
		{
			Texture2D exitTexture = ResourceManager::GetTexture("exit_button");
			exitDoorRenderer->DrawButton(exitTexture);
		}

		Text->RenderText("Health: " + to_string(PlayerRenderer->health), 170.0f, 25.0f, 1.0f);
		Text->RenderText("Tasks: " + to_string(PlayerRenderer->tasks_completed) + "/2", 170.0f, 60.0f, 1.0f);
		Text->RenderText("Light: " + MazeRenderer->lighting, 170.0f, 95.0f, 1.0f);
		Text->RenderText("Time: " + to_string(this->time_remaining), 170.0f, 130.0f, 1.0f);
	}

	else if (this->State == GAME_WIN)
	{
		Text->RenderText("GAME OVER. YOU WON :)", 160.0f, 450.0f, 2.0f);
	}

	else if (this->State == GAME_LOSE)
	{
		Text->RenderText("GAME OVER. YOU LOST :(", 160.0f, 450.0f, 2.0f);
	}
}
