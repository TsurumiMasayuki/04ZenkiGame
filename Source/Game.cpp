#include "Game.h"
#include "Device/GameDevice.h"
#include "Scene\HogeScene.h"
#include "Utility\JsonFileManager.h"

#include "Component/Player/PlayerStats.h"

#include "Device/ControllerInput.h"

Game::Game(HINSTANCE& hinstance, HWND& hwnd)
	: AbstractGame(hinstance, hwnd)
{
}

Game::~Game()
{
}

void Game::onStart()
{
	//四角形画像読み込み
	GameDevice::getTextureManager().load("BoxFill", L"Resources/BoxFill.png");

	//画像読み込み
	GameDevice::getTextureManager().load("white100x100", L"Resources/white100x100.png");
	GameDevice::getTextureManager().load("OptionBotton", L"Resources/button_A.png");
	GameDevice::getTextureManager().load("OptionCurBotton", L"Resources/button_B.png");
	GameDevice::getTextureManager().load("OptionBackGround", L"Resources/background.png");
	GameDevice::getTextureManager().load("healthStock", L"Resources/textures/healthStock.png");
	GameDevice::getTextureManager().load("healthStockBlack", L"Resources/textures/healthStockBlack.png");
	GameDevice::getTextureManager().load("accelerationEffect", L"Resources/textures/accelerationEffect.png");
	GameDevice::getTextureManager().load("accelerationGaugeFlame", L"Resources/textures/accelerationGaugeFlame.png");
	GameDevice::getTextureManager().load("accelerationGaugeCore", L"Resources/textures/accelerationGaugeCore.png");
	GameDevice::getTextureManager().load("goal", L"Resources/textures/goal.png")

	//モデル読み込み
	GameDevice::getModelManager().startLoading();
	GameDevice::getModelManager().load("Cube", "Resources/Models/cube/", "cube");
	GameDevice::getModelManager().load("Sphere", "Resources/Models/sphere/", "sphere");

	//サウンド読み込み
	GameDevice::getAudioManager().loadWavFile("Walk", L"Resources/Sounds/Player/Walk.wav");
	GameDevice::getAudioManager().loadWavFile("EnemyHit", L"Resources/Sounds/Enemy/Enemy_Hit.wav");

	//プレイヤー設定ファイル読み込み
	JsonFileManager<PlayerStats>::getInstance().load("PlayerStats", "Resources/PlayerStats.json");

	m_SceneManager.addScene("Hoge", new HogeScene());
	m_SceneManager.changeScene("Hoge");
}

void Game::onUpdate()
{
	//プレイヤーのステータスをホットリロード
	if (GameDevice::getInput().isKeyDown(DIK_R))
		JsonFileManager<PlayerStats>::getInstance().load("PlayerStats", "Resources/PlayerStats.json");

	ControllerInput::getInstance().update();
}

void Game::onShutdown()
{
}