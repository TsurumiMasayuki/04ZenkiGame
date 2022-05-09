#pragma once
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <functional>
#include "Math/Vec3.h"

class IGameMediator;

class Map
{
public:
	using string = std::string;

	std::function<void(Vec3)> functionObject[2];
	std::function<void(Vec3)> functionMap[3];

public:
	Map();
	~Map();

	void Initialize(int stageNumber, IGameMediator* pGameMediator);

	void FunctionInitialize();

	//Set
	void SetMap(int stageNumber);

	//Get

	//Load
	void LoadMap(int stageNumber);
	void LoadObject(int stageNumber);

	//Create
	void CreateMap();
	void CreateObject();

private:
	static const int mapsizeX = 60;
	static const int mapsizeY = 12;

	IGameMediator* m_pGameMediator;

	int mapdata[mapsizeY][mapsizeX];
	int object[mapsizeY][mapsizeX];
};

