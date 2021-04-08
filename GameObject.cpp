#pragma once
#include <map>
#include <string>
#include <typeinfo>
#include <cassert>
#include <SFML/Graphics.hpp>
#include "Components.h"
#include "PhysicsManager.h"
#include "ScriptManager.h"
#include "GraphicsManager.h"
#include "GameObject.h"
#include "Application.h"

GameObject::GameObject(std::string name, Applications* app)
{
    this->name = name;
    application = app;
}

Applications* GameObject::GetApplication()
{
    return this->application;
}