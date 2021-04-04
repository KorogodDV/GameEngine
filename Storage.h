#pragma once
#include <list>
#include <string>
#include "GameObject.h"

class Applications;

class Storages {
private:

	std::list<GameObject> GameObjects;
	Applications* application;

public:
	
	Storages(Applications* app);

	void CreateObject(std::string name);

	GameObject* GetObject(std::string name);

	void DeleteObject(std::string name);
};