#include <Windows.h>
#include "Game/Game.hpp"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow)
{
#ifdef DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
	Game* game = new Game();

	TGL::OS::APPLICATION_PARAM param;
		param.hInstance = hInstance;
		param.hPrevInstance = hPrevInstance;
		param.lpCmdLine = lpCmdLine;
		param.nCmdShow = nCmdShow;
		param.wndProc = game->MainWndProc;
		param.name = L"TGL Renderer";

	int local_return = game->Run(param);

	delete game;

	return local_return;
}

