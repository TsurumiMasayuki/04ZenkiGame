#include "Map.h"

#include "Actor/Base/GameObject.h"

#include "Device/GameDevice.h"
#include "Utility/ModelGameObjectHelper.h"

#include "Component/Enemy/TestEnemy.h"
#include "Component/Enemy/LinearlyEnemy.h"
#include "Component/Player/PlayerMovement.h"
#include "Component/Floor/Floor.h"

Map::Map() {}


Map::~Map()
{
}

void Map::Initialize(int stegNum, IGameMediator* pGameMediator)
{
	m_pGameMediator = pGameMediator;

	FunctionInitialize();
	SetMap(stegNum);
}

void Map::FunctionInitialize()
{
	auto pCube = GameDevice::getModelManager().getModel("Cube");

	auto pGameMediator = m_pGameMediator;

	//空白
	functionMap[0] =
		[](Vec3 position)
	{
	};

	//基本的な床
	functionMap[1] =
		[pGameMediator, pCube](Vec3 position)
	{
		auto pFloor = ModelGameObjectHelper::instantiateModel<int>(pGameMediator, pCube);
		pFloor->getChildren().at(0)->getComponent<MeshRenderer>()->setColor(Color(0.25f, 0.25f, 0.25f, 1.0f));

		pFloor->getTransform().setLocalPosition(position);
		pFloor->addComponent<Floor>();
	};

	//基本的な壁
	functionMap[2] =
		[pGameMediator, pCube](Vec3 position)
	{
		auto pFloor = ModelGameObjectHelper::instantiateModel<int>(pGameMediator, pCube);
		pFloor->getTransform().setLocalScale(Vec3(1.0f, 2.0f, 1.0f));
		pFloor->getChildren().at(0)->getComponent<MeshRenderer>()->setColor(Color(0.5f, 0.5f, 0.5f, 1.0f));

		pFloor->getTransform().setLocalPosition(position + Vec3(0.0f, 1.0f, 0.0f));
		pFloor->addComponent<Floor>();
	};

	//空白
	//functionObject[0] = 
	//[pGameMeditor](Vec position)
	//{
	//}

	//pleyer
	//functionObject[1] = 
	//[pGameMeditor](Vec position)
	//{
		//auto pPlayer = ModelGameObjectHelper::instantiateModel<int>(this, pCube);

		//pPlayer->getChildren().at(0)->getComponent<MeshRenderer>()->setColor(Color(1.0f, 1.0f, 1.0f, 1.0f));

		//pPlayer->getTransform().setLocalPosition(position);
		//pPlayer->addComponent<PlayerMovement>();

	//}

	//testEnemy
	//functionObject[2] = 
	//[pGameMeditor](Vec position)
	//{
		//auto pEnemy = ModelGameObjectHelper::instantiateModel<int>(this, pCube);
		//pEnemy->setTag("Enemy");
		//pEnemy->getTransform().setLocalPosition(position);

		//auto pBoxCollider = pEnemy->addComponent<BoxColiiderBt>();
		//pBoxCollider->setMass(1.0f);
		//pBoxCollider->setTrigger(false);
		//pBoxCollider->setUseGravity(false);

		//auto pTestEnemy = pEnemy->addComponent<TestEnemy>();
		//pTestEnemy->SetTarget(pPlayer);
	//}

}

void Map::SetMap(int stegNumber)
{
	LoadMap(stegNumber);
	//LoadObject(stageNumber);

	CreateMap();
	//CreateObject();
}

//ステージ読み込み
void Map::LoadMap(int stageNumber)
{
	std::ifstream file;

	std::ostringstream StegNumber;
	StegNumber << stageNumber;

	const string modelname = "Map";
	const string filename = modelname + StegNumber.str() + ".txt";
	const string directoryPath = "Resources/" + modelname + "/";

	file.open(directoryPath + filename);
	string line;
	int y = 0;
	while (getline(file, line))
	{
		std::istringstream line_stream(line);

		string key;
		getline(line_stream, key, '	');

		if (key == "v")
		{
			for (int x = 0; x < mapsizeX; x++)
			{
				line_stream >> mapdata[y][x];
			}
		}
		y++;
	}
	file.close();
}

//オブジェクト読み込み(プレイヤーや敵とか)
void Map::LoadObject(int stageNumber)
{
	std::ifstream file;

	std::ostringstream StegNumber;
	StegNumber << stageNumber;

	const string modelName = "Object";
	const string filename = modelName + StegNumber.str() + ".txt";
	const string directoryPath = "Resources/" + modelName + "/";

	file.open(directoryPath + filename);
	string line;
	int y = 0;
	while (getline(file, line))
	{
		std::istringstream line_stream(line);

		string key;
		getline(line_stream, key, '	');

		if (key == "v")
		{
			for (int x = 0; x < mapsizeX; x++)
			{
				line_stream >> object[y][x];
			}
		}
		y++;
	}
	file.close();
}

void Map::CreateMap()
{
	Vec3 position = Vec3{ 0,0,0 };

	for (int y = 0; y < mapsizeY; y++)
	{
		for (int x = 0; x < mapsizeX; x++)
		{
			if (mapdata[y][x] != 0)
			{
				position = Vec3{ (float)x,0,(float)y };
				functionMap[mapdata[y][x]](position);
			}
		}
	}
}

void Map::CreateObject()
{
	Vec3 position = Vec3{ 0,0,-1.0f };

	for (int y = 0; y < mapsizeY; y++)
	{
		for (int x = 0; x < mapsizeX; x++)
		{
			if (object[y][x] != 0)
			{
				position = Vec3{ (float)x,-1.0,(float)y };
				functionObject[object[y][x]](position);
			}
		}
	}

}
