#pragma once
#include "AbstractGame.h"

class Game
	: public AbstractGame
{
public:
	Game(HINSTANCE& hinstance, HWND& hwnd);
	~Game();

	virtual void onStart() override;
	virtual void onUpdate() override;
	virtual void onShutdown() override;
};