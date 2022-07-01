#include "Game.h"
#include "Device/GameDevice.h"
#include "Scene/TitleScene.h"
#include "Scene/HogeScene.h"
#include "Scene/EnemyTestScene.h"
#include "Utility/JsonFileManager.h"

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
	GameDevice::getTextureManager().load("collectItemF", L"Resources/textures/ui_starA.png");
	GameDevice::getTextureManager().load("collectItemB", L"Resources/textures/ui_starB.png");
	GameDevice::getTextureManager().load("goal", L"Resources/textures/goal.png");
	GameDevice::getTextureManager().load("title", L"Resources/textures/TITLE2.png");
	GameDevice::getTextureManager().load("titleBG", L"Resources/textures/titleBG.png");
	GameDevice::getTextureManager().load("fire", L"Resources/textures/fire.png");
	GameDevice::getTextureManager().load("erase", L"Resources/textures/erase.png");
	GameDevice::getTextureManager().load("num0", L"Resources/textures/0.png");
	GameDevice::getTextureManager().load("num1", L"Resources/textures/1.png");
	GameDevice::getTextureManager().load("num2", L"Resources/textures/2.png");
	GameDevice::getTextureManager().load("num3", L"Resources/textures/3.png");
	GameDevice::getTextureManager().load("num4", L"Resources/textures/4.png");
	GameDevice::getTextureManager().load("num5", L"Resources/textures/5.png");
	GameDevice::getTextureManager().load("num6", L"Resources/textures/6.png");
	GameDevice::getTextureManager().load("num7", L"Resources/textures/7.png");
	GameDevice::getTextureManager().load("num8", L"Resources/textures/8.png");
	GameDevice::getTextureManager().load("num9", L"Resources/textures/9.png");

	//Blockbenchモデル用画像読み込み
	GameDevice::getTextureManager().load("Player", L"Resources/BBModels/player.png");
	GameDevice::getTextureManager().load("ui_crystal", L"Resources/ui_crystal/crystal_red_tex.png");

	//モデル読み込み
	GameDevice::getModelManager().startLoading();
	GameDevice::getModelManager().load("Cube", "Resources/Models/cube/", "cube");
	GameDevice::getModelManager().load("Sphere", "Resources/Models/sphere/", "sphere");

	//サウンド読み込み
	//プレイヤー
	GameDevice::getAudioManager().loadWavFile("Walk", L"Resources/Sounds/Player/Walk.wav");
	GameDevice::getAudioManager().loadWavFile("Dash", L"Resources/Sounds/Player/Dash.wav");
	GameDevice::getAudioManager().loadWavFile("Sliding", L"Resources/Sounds/Player/Sliding.wav");
	//敵
	GameDevice::getAudioManager().loadWavFile("EnemyDown", L"Resources/Sounds/Enemy/Enemy_Down.wav");
	GameDevice::getAudioManager().loadWavFile("EnemyHit", L"Resources/Sounds/Enemy/Enemy_Hit.wav");
	//ステージ
	GameDevice::getAudioManager().loadWavFile("Stage1", L"Resources/Sounds/Stage/Stage1.wav");


	//プレイヤー設定ファイル読み込み
	JsonFileManager<PlayerStats>::getInstance().load("PlayerStats", "Resources/PlayerStats.json");

	m_SceneManager.addScene("Title", new TitleScene());
	m_SceneManager.addScene("Hoge", new HogeScene());
	m_SceneManager.addScene("EnemyTest", new EnemyTestScene());

	m_SceneManager.changeScene("Title");
	//m_SceneManager.changeScene("EnemyTest");
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