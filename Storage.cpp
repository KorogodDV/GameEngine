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

void Storages::CreateBall(std::string params)
{
	std::vector<std::string> param;
	split(params, param, ' ');

	GameObject* obj = new GameObject(param[1], application, param[0]);

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
	//rend->showHitboxesBoundary = 1;
	//rend->showSprite = 0;
	rend->image.loadFromFile("textures/"/*ball.png*/ + param[2]);
	rend->image.createMaskFromColor(sf::Color::White);
	rend->texture.loadFromImage(rend->image);
	rend->sprite.setTexture(rend->texture);
	rend->sprite.setPosition(std::stof(param[3]) - std::stof(param[7]), std::stof(param[4]) - std::stof(param[7]));
	rend->sprite.setScale(2.f * sf::Vector2f(std::stof(param[7]) / rend->sprite.getLocalBounds().width, std::stof(param[7]) / rend->sprite.getLocalBounds().height));

	GameObjects.push_back(*obj);
}

void Storages::CreateBullet(std::string params)
{
	std::vector<std::string> param;
	split(params, param, ' ');

	GameObject* obj = new GameObject(param[1], application, param[0]);

	obj->AddComponent<Move>();
	obj->AddComponent<Physics>();
	Physics* physics = obj->GetComponent<Physics>();
	physics->pos = sf::Vector2f(std::stof(param[3]), std::stof(param[4]));
	physics->speed = sf::Vector2f(std::stof(param[5]), std::stof(param[6]));
	physics->mass = 0;
	physics->gravity = std::stof(param[9]);
	physics->collisionType = 1;

	obj->AddComponent<Collider>();
	Collider* coll = obj->GetComponent<Collider>();
	sf::ConvexShape* newHitBox = new sf::ConvexShape(10);
	newHitBox->setFillColor(sf::Color(0));
	newHitBox->setOutlineColor(sf::Color::Blue);
	newHitBox->setOutlineThickness(1);
	float bulletLength = std::stof(param[7]);
	float bulletWidth = std::stof(param[8]);
	for (int i = 0; i < 10; i++)
	{
		if (i < 5)
			newHitBox->setPoint(i, (sf::Vector2f(std::stof(param[3]) + bulletLength - bulletWidth / 2, std::stof(param[4]) + bulletWidth / 2) + (sf::Vector2f(0, -1 * bulletWidth / 2) -
				sf::Vector2f(-1 * bulletWidth / 2 * sin(2 * PI / 10 * (i + 0.5)), -1 * bulletWidth / 2 * (1 - cos(2 * PI / 10 * (i + 0.5)))))));
		else
			newHitBox->setPoint(i, (sf::Vector2f(std::stof(param[3]) + bulletWidth / 2, std::stof(param[4]) + bulletWidth / 2) + (sf::Vector2f(0, -1 * bulletWidth / 2) -
				sf::Vector2f(-1 * bulletWidth / 2 * sin(2 * PI / 10 * (i + 0.5)), -1 * bulletWidth / 2 * (1 - cos(2 * PI / 10 * (i + 0.5)))))));
	}
	coll->hitboxes.push_back(*newHitBox);

	obj->AddComponent<Renderer>();
	Renderer* rend = obj->GetComponent<Renderer>();
	//rend->showHitboxesBoundary = 1;
	//rend->showSprite = 0;
	rend->image.loadFromFile("textures/" + param[2]);
	rend->image.createMaskFromColor(sf::Color::White);
	rend->texture.loadFromImage(rend->image);
	rend->sprite.setTexture(rend->texture);
	rend->sprite.setPosition(std::stof(param[3]), std::stof(param[4]));
	rend->sprite.setScale(bulletLength / rend->sprite.getLocalBounds().width, bulletWidth / rend->sprite.getLocalBounds().height);

	GameObjects.push_back(*obj);
}

void Storages::CreateUnit(std::string params)
{
	std::vector<std::string> param;
	split(params, param, ' ');

	GameObject* obj = new GameObject(param[1], application, param[0]);

	obj->AddComponent<Move>();
	obj->AddComponent<Physics>();
	Physics* physics = obj->GetComponent<Physics>();
	physics->pos = sf::Vector2f(std::stof(param[3]) + std::stof(param[7]) / 2, std::stof(param[4]) + std::stof(param[8]) / 2);
	physics->speed = sf::Vector2f(std::stof(param[5]), std::stof(param[6]));
	physics->mass = std::stof(param[9]);
	physics->gravity = std::stof(param[10]);
	physics->collisionType = std::stof(param[11]);

	obj->AddComponent<Collider>();
	Collider* coll = obj->GetComponent<Collider>();
	sf::ConvexShape* newHitBox = new sf::ConvexShape(4);
	newHitBox->setFillColor(sf::Color(0));
	newHitBox->setOutlineColor(sf::Color::Blue);
	newHitBox->setOutlineThickness(1);
	newHitBox->setPoint(0, sf::Vector2f(std::stof(param[3]), std::stof(param[4])));
	newHitBox->setPoint(1, sf::Vector2f(std::stof(param[3]) + std::stof(param[7]), std::stof(param[4])));
	newHitBox->setPoint(2, sf::Vector2f(std::stof(param[3]) + std::stof(param[7]), std::stof(param[4]) + std::stof(param[8])));
	newHitBox->setPoint(3, sf::Vector2f(std::stof(param[3]), std::stof(param[4]) + std::stof(param[8])));
	coll->hitboxes.push_back(*newHitBox);

	obj->AddComponent<Renderer>();
	Renderer* rend = obj->GetComponent<Renderer>();
	rend->showHitboxesBoundary = 1;
	//rend->showSprite = 0;
	rend->image.loadFromFile("textures/" + param[2]);
	rend->image.createMaskFromColor(sf::Color::White);
	rend->texture.loadFromImage(rend->image);
	rend->sprite.setTexture(rend->texture);
	rend->sprite.setPosition(std::stof(param[3]), std::stof(param[4]));
	rend->sprite.setScale(std::stof(param[7]) / rend->sprite.getLocalBounds().width, std::stof(param[8]) / rend->sprite.getLocalBounds().height);

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

	std::vector<std::vector<std::string>> objparams(objects.size());
	for (int i = 0; i < objects.size(); i++)
	{
		split(objects[i], objparams[i], ' ');
		if (objparams[i][0] == "ball")
			this->CreateBall(objects[i]);
		else if (objparams[i][0] == "bullet")
			this->CreateBullet(objects[i]);
		else if (objparams[i][0] == "player" || objparams[i][0] == "fast_enemy" || objparams[i][0] == "slow_enemy" || objparams[i][0] == "shooting_enemy")
			this->CreateUnit(objects[i]);
		else if (objparams[i][0] == "background")
			this->application->GetGraphicsManager()->SetBackground(objparams[i][1]);
		//this->CreateBasicObject(objects[i]);
	}
}


GameObject* Storages::GetObject(std::string name)
{
	auto searchRes = std::find_if(GameObjects.begin(), GameObjects.end(), [name](GameObject gameobj) { return  gameobj.name == name; });
	if (searchRes != GameObjects.end())
		return &(*searchRes);
	assert(0 && "There is no object with this name in the storage");
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