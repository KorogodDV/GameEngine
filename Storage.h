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
		GameObjects.push_back(*new GameObject);
		GameObjects.back().name = name;
	}

	GameObject* GetObject(std::string name)
	{
		GameObject* obj = 0;
		for (GameObject gameobj : GameObjects)
		{
			if (gameobj.name == name)
			{
				obj = &gameobj;
				break;
			}
		}
		assert(obj);
		return obj;
	}


	//void DeleteObject(std::string name)
	//{
	//	GameObject* obj = 0;
	//	for (GameObject gameobj : GameObjects)
	//	{
	//		if (gameobj.name == name)
	//		{
	//			obj = &gameobj;
	//			break;
	//		}
	//	}
	//	assert(obj);
	//	for (Component* comp : obj.)
	//}
};