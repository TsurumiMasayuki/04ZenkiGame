#include "Game.h"
#include "Device/GameDevice.h"
#include "Scene/TitleScene.h"
#include "Scene/HogeScene.h"
#include "Scene/EnemyTestScene.h"
#include "Scene/GameOverScene.h"
#include "Scene/ClearScene.h"
#include "Utility/JsonFileManager.h"

#include "Component/Player/PlayerStats.h"

#include "Device/ControllerInput.h"
#include "Effect/HitStop.h"

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
	GameDevice::getTextureManager().load("mask", L"Resources/textures/mask.png");
	GameDevice::getTextureManager().load("clear", L"Resources/textures/Ending.png");
	GameDevice::getTextureManager().load("select", L"Resources/textures/Select.png");
	GameDevice::getTextureManager().load("gameOver", L"Resources/textures/GameOverScene.png");
	GameDevice::getTextureManager().load("backGround", L"Resources/textures/background_floor.png");	
	GameDevice::getTextureManager().load("time",  L"Resources/textures/time.png");
	GameDevice::getTextureManager().load("point", L"Resources/textures/point.png");
	GameDevice::getTextureManager().load("colon", L"Resources/textures/colon.png");
	GameDevice::getTextureManager().load("accEffect", L"Resources/textures/accEffect.png");
	GameDevice::getTextureManager().load("1", L"Resources/textures/UI_1.png");
	GameDevice::getTextureManager().load("2", L"Resources/textures/UI_2.png");
	GameDevice::getTextureManager().load("3", L"Resources/textures/UI_3.png");
	GameDevice::getTextureManager().load("start", L"Resources/textures/UI_start.png");

	//Blockbenchモデル用画像読み込み
	GameDevice::getTextureManager().load("Player", L"Resources/BBModels/player.png");
	GameDevice::getTextureManager().load("monster_03", L"Resources/BBModels/moster_03.png");
	GameDevice::getTextureManager().load("monster_04", L"Resources/BBModels/moster_04.png");
	GameDevice::getTextureManager().load("monster_04b", L"Resources/BBModels/moster_04b.png");
	GameDevice::getTextureManager().load("block_wall", L"Resources/BBModels/block_wall.png");
	GameDevice::getTextureManager().load("block_floor", L"Resources/BBModels/block_floor.png");

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
	GameDevice::getAudioManager().loadWavFile("HitEnemy", L"Resources/Sounds/Player/Damage.wav");
	//敵
	GameDevice::getAudioManager().loadWavFile("EnemyDown", L"Resources/Sounds/Enemy/Enemy_Down.wav");
	//ステージ
	GameDevice::getAudioManager().loadWavFile("Stage1", L"Resources/Sounds/Stage/Stage1.wav");
	GameDevice::getAudioManager().loadWavFile("ClearJG", L"Resources/Sounds/Stage/ClearJG.wav");
	//BGM
	GameDevice::getAudioManager().loadWavFile("Title", L"Resources/Sounds/BGM/TitleBGM.wav");
	GameDevice::getAudioManager().loadWavFile("Endeng", L"Resources/Sounds/BGM/EndengBGM.wav");
	GameDevice::getAudioManager().loadWavFile("GameOver", L"Resources/Sounds/BGM/GameOverJG.wav");

	//プレイヤー設定ファイル読み込み
	JsonFileManager<PlayerStats>::getInstance().load("PlayerStats", "Resources/PlayerStats.json");

	m_SceneManager.addScene("Title", new TitleScene());
	m_SceneManager.addScene("Hoge", new HogeScene());
	m_SceneManager.addScene("EnemyTest", new EnemyTestScene());
	m_SceneManager.addScene("GameOver", new GameOverScene());
	m_SceneManager.addScene("Clear", new ClearScene());
	m_SceneManager.changeScene("Title");
	//m_SceneManager.changeScene("EnemyTest");
}

void Game::onUpdate()
{
	//プレイヤーのステータスをホットリロード
	if (GameDevice::getInput().isKeyDown(DIK_R))
		JsonFileManager<PlayerStats>::getInstance().load("PlayerStats", "Resources/PlayerStats.json");

	ControllerInput::getInstance().update();

	HitStop::getInstance().update();
}

void Game::onShutdown()
{
}