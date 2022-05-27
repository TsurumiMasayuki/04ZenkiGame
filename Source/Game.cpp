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
	//�l�p�`�摜�ǂݍ���
	GameDevice::getTextureManager().load("BoxFill", L"Resources/BoxFill.png");

	//�摜�ǂݍ���
	GameDevice::getTextureManager().load("white100x100", L"Resources/white100x100.png");
	GameDevice::getTextureManager().load("accelerationEffect", L"Resources/textures/accelerationEffect.png");
	GameDevice::getTextureManager().load("accelerationGaugeFlame", L"Resources/textures/accelerationGaugeFlame.png");
	GameDevice::getTextureManager().load("accelerationGaugeCore", L"Resources/textures/accelerationGaugeCore.png");

	//���f���ǂݍ���
	GameDevice::getModelManager().startLoading();
	GameDevice::getModelManager().load("Cube", "Resources/Models/cube/", "cube");
	GameDevice::getModelManager().load("Sphere", "Resources/Models/sphere/", "sphere");

	//�T�E���h�ǂݍ���
	GameDevice::getAudioManager().loadWavFile("Walk", L"Resources/Sounds/Player/Walk.wav");
	GameDevice::getAudioManager().loadWavFile("EnemyHit", L"Resources/Sounds/Enemy/Enemy_Hit.wav");

	//�v���C���[�ݒ�t�@�C���ǂݍ���
	JsonFileManager<PlayerStats>::getInstance().load("PlayerStats", "Resources/PlayerStats.json");

	m_SceneManager.addScene("Hoge", new HogeScene());
	m_SceneManager.changeScene("Hoge");
}

void Game::onUpdate()
{
	//�v���C���[�̃X�e�[�^�X���z�b�g�����[�h
	if (GameDevice::getInput().isKeyDown(DIK_R))
		JsonFileManager<PlayerStats>::getInstance().load("PlayerStats", "Resources/PlayerStats.json");

	ControllerInput::getInstance().update();
}

void Game::onShutdown()
{
}