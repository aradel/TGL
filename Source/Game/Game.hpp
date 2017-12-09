#ifndef GAME_HPP
#define GAME_HPP
#include "../Application/Application.hpp"

class Game : public TGL::Application {
public:
	Game() = default;
	~Game() = default;
private: // TGL::Appplication
	virtual void Initialize();
	virtual void CleanUp();
	virtual bool Update(float fDeltaTime);
	virtual void Draw();
};


#endif