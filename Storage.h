#pragma once
#include <list>
#include <string>
#include <vector>
#include "GameObject.h"

class Applications;

class Storages {
private:

	std::list<GameObject> GameObjects;
	Applications* application;

public:
	
	Storages(Applications* app);

	void CreateObject(std::string name);

	void CreateBall(std::vector<std::string> param);

	void CreateBullet(std::vector<std::string> param);

	void CreatePlayer(std::vector<std::string> param);

	void CreateFastEnemy(std::vector<std::string> param);

	void UploadScene(std::string address);

	GameObject* GetObject(std::string name);

	void DeleteObject(std::string name);
};