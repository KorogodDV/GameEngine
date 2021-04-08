#pragma once
#include "GraphicsManager.h"
#include "PhysicsManager.h"
#include "ScriptManager.h"
#include "GameObject.h"
#include <SFML/Graphics.hpp>

class Storages;

class Applications {

	Storages* Storage;
	ScriptManagers* ScriptManager;
	PhysicsManagers* PhysicsManager;
	GraphicsManagers* GraphicsManager;
	sf::RenderWindow* window;
	sf::Clock LastFrameDuration;

public:

	Applications(int window_length = 1280, int window_width = 720);

	void Run();

	Storages* GetStorage();

	ScriptManagers* GetScriptManager();

	PhysicsManagers* GetPhysicsManager();

	GraphicsManagers* GetGraphicsManager();

	sf::RenderWindow* GetWindow();

	float GetLastFrameDurationAsSeconds();

};