#include "Map.h"

#include "Component/Enemy/TestEnemy.h"
#include "Component/Enemy/LinearlyEnemy.h"
#include "Component/Player/PlayerMovement.h"
#include "Conmponent/Floor/Floor.h"


Map::Map(){}


Map::~Map()
{
}

void Map::Initialize(int stegNum)
{
	FunctionInitialize();

	SetMap(stegNumber);
}

void Map::FunctionInitialize()
{
	auto pCube = GameDevice::getModelManager().getModel("Cube");

	//空白
	//functionMap[0] = 
	//[pGameMeditor](Vec position)
	//{
	//}

	//基本的な床
	//functionObject[1] = 
	//[pGameMeditor](Vec position)
	//{
	//	auto pFloor =  ModelGameObjectHelper::instantiateModel<int>(this, pCube);
	// 
	//  pFloor->getTransform().setLocalPosition(Vec position);
	//	pFloor->addCompponent<Floor>;
	//}


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
	LoadObject(stegNumber);

	CreateMap();
	CreateObject();
}

//ステージ読み込み
void Map::LoadMap(int stegNumber)
{
	std::ifstream file;

	std::ostringstream StegNumber;
	StegNumber << stegNumber;

	const string modeIname = "Map";
	const string filename = modeIname + StegNumber.str() + ".txt";
	const string dilectoryPath = "Resources/" + modeIname + "/";

	file.open(dilectoryPath + filename);
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
void Map::LoadObject(int stegNumber)
{
	std::ifstream file;

	std::ostringstream StegNumber;
	StegNumber << stegNumber;

	const string modeIname = "Object";
	const string filename = modeIname + StegNumber.str() + ".txt";
	const string dilectoryPath = "Resources/" + modeIname + "/";

	file.open(dilectoryPath + filename);
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
	Vec position = { 0,0,0 };

	for (int y = 0; y < mapsizeY; y++)
	{
		for (int x = 0; x < mapsizeX; x++)
		{
			if (mapdata[y][x] != 0)
			{
				position = { x,0,y };
				functionMap[mapdata[y][x]](position);
			}
		}
	}
}

void Map::CreateObject()
{
	Vec position = { 0,0,-1.0f };

	for (int y = 0; y < mapsizeY; y++)
	{
		for (int x = 0; x < mapsizeX; x++)
		{
			if (object[y][x] != 0)
			{
				position = { x,-1.0,y };
				functionObject[object[y][x]](position);
			}
		}
	}

}
