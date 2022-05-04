#include "Game.h"
#include "Scene\HogeScene.h"

Game::Game(HINSTANCE& hinstance, HWND& hwnd)
	: AbstractGame(hinstance, hwnd)
{
}

Game::~Game()
{
}

void Game::onStart()
{
	//lŠpŒ`‰æ‘œ“Ç‚İ‚İ
	GameDevice::getTextureManager().load("BoxFill", L"Resources/BoxFill.png");

	//‰æ‘œ“Ç‚İ‚İ
	GameDevice::getTextureManager().load("white100x100", L"Resources/white100x100.png");

	//ƒ‚ƒfƒ‹“Ç‚İ‚İ
	GameDevice::getModelManager().startLoading();
	GameDevice::getModelManager().load("Cube", "Resources/Models/cube/", "cube");
	GameDevice::getModelManager().load("Sphere", "Resources/Models/sphere/", "sphere");

	m_SceneManager.addScene("Hoge", new HogeScene());
	m_SceneManager.changeScene("Hoge");
}

void Game::onUpdate()
{
}

void Game::onShutdown()
{
}