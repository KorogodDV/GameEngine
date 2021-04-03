#pragma once
#include <list>
#include <string>
#include "GameObject.h"
#include "ScriptManager.h"
#include "GraphicsManager.h"
#include "PhysicsManager.h"
#include <cassert>
#include "Application.h"
#include "Storage.h"

void Storages::CreateObject(std::string name)
	{
		GameObjects.push_back(*(new GameObject));
		GameObjects.back().name = name;
		GameObjects.back().application = application;
	}

GameObject* Storages::GetObject(std::string name)
	{
		auto searchRes = std::find_if(GameObjects.begin(), GameObjects.end(), [name](GameObject gameobj) { return  gameobj.name == name; });
		if (searchRes != GameObjects.end())
			return &(*searchRes);
		assert(0);
	}


void Storages::DeleteObject(std::string name)
	{
		GameObject* obj = 0;
		auto searchRes = std::find_if(GameObjects.begin(), GameObjects.end(), [name](GameObject gameobj) { return  gameobj.name == name; });
		if (searchRes != GameObjects.end())
			obj = &(*searchRes);
		assert(obj);
		application->GraphicsManager.RemoveRenderer(obj);
		application->PhysicsManager.RemovePhysics(obj);
		application->ScriptManager.RemoveScript(obj);
		GameObjects.remove(*obj);
	}