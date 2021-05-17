#pragma once
#include "GraphicsManager.h"
#include "PhysicsManager.h"
#include "ScriptManager.h"
#include "Storage.h"
#include "GameObject.h"
#include <SFML/Graphics.hpp>
#include "Application.h"
#include <set>

Applications::Applications(int window_length, int window_width, std::string background_address)
    {
        window = new sf::RenderWindow(sf::VideoMode(window_length, window_width), "App");
        Storage = new Storages(this);
        ScriptManager = new ScriptManagers(this);
        PhysicsManager = new PhysicsManagers(this);
        GraphicsManager = new GraphicsManagers(this, background_address);
        window->setFramerateLimit(60);
        WorkTime = *new sf::Clock;
        WorkTimeBeforeThisFrame = -1;
        LastFrameDuration = 0;
        ObjectsForRemove = *new std::set<std::string>;
    }

void Applications::Run()
    {
        while (window->isOpen())
        {
            sf::Event event;

            while (window->pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    window->close();
                    break;
                }
            }
            GraphicsManager->draw(window);
            PhysicsManager->update();
            ScriptManager->update();
            LastFrameDuration = WorkTime.getElapsedTime().asSeconds() - WorkTimeBeforeThisFrame;
            if (WorkTimeBeforeThisFrame < 0)
                WorkTimeBeforeThisFrame = 0;
            else
                WorkTimeBeforeThisFrame += LastFrameDuration;
            for (std::string gameObject_name : ObjectsForRemove)
            {
                Storage->DeleteObject(gameObject_name);
            }
            ObjectsForRemove.clear();
        }
    }

Storages* Applications::GetStorage()
{
    return this->Storage;
}

ScriptManagers* Applications::GetScriptManager()
{
    return this->ScriptManager;
}

PhysicsManagers* Applications::GetPhysicsManager()
{
    return this->PhysicsManager;
}

GraphicsManagers* Applications::GetGraphicsManager()
{
    return this->GraphicsManager;
}

sf::RenderWindow* Applications::GetWindow()
{
    return this->window;
}

float Applications::GetLastFrameDurationAsSeconds()
{
    return LastFrameDuration;
}

float Applications::GetWorkTimeAsSeconds()
{
    return WorkTimeBeforeThisFrame + LastFrameDuration;
}

std::set<std::string>* Applications::GetObjectsForRemove()
{
    return &this->ObjectsForRemove;
}