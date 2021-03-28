#pragma once
#include <list>
#include <string>
#include "GameObject.h"
#include <cassert>

class Storage {
private:

	std::list<GameObject> GameObjects;

public:

	void CreateObject(std::string name)
	{
		GameObjects.push_back(*(new GameObject));
		GameObjects.back().name = name;
	}

	GameObject* GetObject(std::string name)
	{
		auto searchRes = std::find_if(GameObjects.begin(), GameObjects.end(), [name](GameObject gameobj) { return  gameobj.name == name; });
		if (searchRes != GameObjects.end())
			return &(*searchRes);
		assert(0);
	}


	void DeleteObject(std::string name)
	{
		GameObject* obj = 0;
		auto searchRes = std::find_if(GameObjects.begin(), GameObjects.end(), [name](GameObject gameobj) { return  gameobj.name == name; });
		if (searchRes != GameObjects.end())
			obj = &(*searchRes);
		assert(obj);
		GraphicsManager.RemoveRenderer(obj);
		PhysicsManager.RemovePhysics(obj);
		ScriptManager.RemoveScript(obj);
		GameObjects.remove(*obj);
	}
};

Storage storage;