#pragma once
#include <list>
#include <string>
#include "GameObject.h"
#include "ScriptManager.h"
#include "GraphicsManager.h"
#include "PhysicsManager.h"
#include <cassert>

class Applications;

class Storages {
private:

	std::list<GameObject> GameObjects;

public:
	Applications* application;

	void CreateObject(std::string name);

	GameObject* GetObject(std::string name);

	void DeleteObject(std::string name);
};