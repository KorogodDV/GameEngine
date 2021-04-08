#pragma once
#include "GraphicsManager.h"
#include "GameObject.h"
#include "Components.h"
#include <SFML/Graphics.hpp>
#include "Application.h"

GraphicsManagers::GraphicsManagers(Applications* app)
{
    Renderers = *new std::list<Renderer*>;
    this->app = app;
}

Applications* GraphicsManagers::GetApplication()
{
    return app;
}
   
void GraphicsManagers::AddRenderer(Renderer* newrend)
{
    Renderers.push_back(newrend);
}

void GraphicsManagers::RemoveRenderer(Renderer* rend)
{
    Renderers.remove(rend);
}

void GraphicsManagers::RemoveRenderer(GameObject* obj)
{
    std::cout << 1;
    Renderers.remove_if([obj](Renderer* rend) { return  rend->gameObject->name == obj->name; });
}

void GraphicsManagers::draw(sf::RenderWindow* window)
{
    for (Renderer* currrend : Renderers)
    {
        if (currrend->showSprite)
            window->draw(currrend->sprite);
        if (currrend->showHitboxesBoundary)
        {
            for (sf::ConvexShape hitbox : currrend->gameObject->GetComponent<Collider>()->hitboxes)
                window->draw(hitbox);
        }
    }
}

int GraphicsManagers::size()
{
    return Renderers.size();
}