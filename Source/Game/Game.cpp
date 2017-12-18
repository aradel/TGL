#include "Game.hpp"

void Game::Initialize() 
{

}

void Game::CleanUp() 
{

}

bool Game::Update(float fDeltaTime) 
{
	if (pInputDevice->IsKeyDown(TGL::Input::Key::Escape))
		return false;

	return true;
}

void Game::Draw() 
{

}