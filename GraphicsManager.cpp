#pragma once
#include "GraphicsManager.h"
#include "GameObject.h"
#include "Components.h"

   
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
        Renderers.remove_if([obj](Renderer* rend) { return  rend->gameObject == obj; });
    }

    void GraphicsManagers::draw(sf::RenderWindow* window)
    {
        for (Renderer* currrend : Renderers)
        {
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