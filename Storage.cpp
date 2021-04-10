#pragma once
#include <list>
#include <string>
#include "GameObject.h"
#include "ScriptManager.h"
#include "GraphicsManager.h"
#include "PhysicsManager.h"
#include <cassert>
#include <vector>
#include "Application.h"
#include "Storage.h"
#include "uploadingStringFromTxt.h"
#include "Components.h"
#include <SFML/Graphics.hpp>
#include "math.h"
#include <iostream>

#define PI 3.14159265

Storages::Storages(Applications* app)
{
	GameObjects = *(new std::list<GameObject>);
	application = app;
}

void Storages::CreateObject(std::string name)
{
	GameObjects.push_back(*(new GameObject(name, application)));
}

void Storages::CreateBasicObject(std::string objparams)
{
	std::vector<std::string> param;
	split(objparams, param, ' ');

	GameObject* obj = new GameObject(param[0], application);

	if (param[1] == "ball")
	{
		obj->AddComponent<Move>();
		obj->AddComponent<Physics>();
		Physics* physics = obj->GetComponent<Physics>();
		physics->pos = sf::Vector2f(std::stof(param[3]), std::stof(param[4]));
		physics->speed = sf::Vector2f(std::stof(param[5]), std::stof(param[6]));
		physics->mass = std::stof(param[8]);
		physics->gravity = std::stof(param[9]);
		physics->collisionType = std::stof(param[10]);

		obj->AddComponent<Collider>();
		Collider* coll = obj->GetComponent<Collider>();
		sf::ConvexShape* newHitBox = new sf::ConvexShape(std::stof(param[11]));
		newHitBox->setFillColor(sf::Color(0));
		newHitBox->setOutlineColor(sf::Color::Blue);
		newHitBox->setOutlineThickness(1);
		for (int i = 0; i < std::stof(param[11]); i++)
		{
			newHitBox->setPoint(i, (sf::Vector2f(std::stof(param[3]), std::stof(param[4])) + (sf::Vector2f(0, -1 * std::stof(param[7])) - 
				sf::Vector2f(-1 * std::stof(param[7]) * sin(2 * PI / std::stof(param[11]) * i), -1 * std::stof(param[7]) * (1 - cos(2 * PI / std::stof(param[11]) * i))))));
		}
		coll->hitboxes.push_back(*newHitBox);

		obj->AddComponent<Renderer>();
		Renderer* rend = obj->GetComponent<Renderer>();
		rend->showHitboxesBoundary = 1;
		//rend->showSprite = 0;
		rend->image.loadFromFile("textures/"/*ball.png*/ + param[2]);
		rend->image.createMaskFromColor(sf::Color::White);
		rend->texture.loadFromImage(rend->image);
		rend->sprite.setTexture(rend->texture);
		rend->sprite.setPosition(std::stof(param[3]) - std::stof(param[7]), std::stof(param[4]) - std::stof(param[7]));
		rend->sprite.setScale(2.f * sf::Vector2f(std::stof(param[7]) / rend->sprite.getLocalBounds().width, std::stof(param[7]) / rend->sprite.getLocalBounds().height));
	}

	GameObjects.push_back(*obj);
}

void Storages::UploadScene(std::string address)
{
	while (GameObjects.size() != 0)
		this->DeleteObject(GameObjects.front().name);

	std::string scene = uploadBufferFromFile(("scenes/" + address).c_str());
	std::vector<std::string> objects;
	split(scene, objects, '\n');
	while (objects[0][0] == '/')
		objects.erase(objects.begin());
	for (std::string newobj : objects)
		this->CreateBasicObject(newobj);
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
	application->GetGraphicsManager()->RemoveRenderer(obj);
	application->GetPhysicsManager()->RemovePhysics(obj);
	application->GetScriptManager()->RemoveScript(obj);
	GameObjects.remove(*obj);
}