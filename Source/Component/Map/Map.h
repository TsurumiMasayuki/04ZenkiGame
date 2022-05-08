#pragma once
#include<fstream>
#include<sstream>
#include<unordered_map>
#include<functional>

class Map
{
public:
	using string = std::string;

	std::function<void()> functionObject[2];
	std::function<void()> functionMap[3];

public:
	Map();
	~Map();

	void Initialize(int stegNum);

	void FunctionInitialize();

	//Set
	void SetMap(int stegNumber);

	//Get

	//Load
	void LoadMap(int stegNumber);
	void LoadObject(int stegNumber);

	//Create
	void CreateMap();
	void CreateObject();

private:
	static const int mapsizeX = 60;
	static const int mapsizeY = 12;

	IGameMediator* pGameMeditor = this;

	int mapdata[mapsizeY][mapsizeX];
	int object[mapsizeY][mapsizeX];
};

