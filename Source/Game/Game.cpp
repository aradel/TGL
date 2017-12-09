#include "Game.hpp"

void Game::Initialize() 
{

}

void Game::CleanUp() 
{

}

bool Game::Update(float fDeltaTime) 
{
	if (inputDevice->IsKeyDown(TGL::Key::Escape))
		return false;

	return true;
}

void Game::Draw() 
{

}