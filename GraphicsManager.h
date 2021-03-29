#pragma once
#include <list>
#include <SFML/Graphics.hpp>
#include "Components.h"


class GraphicsManagers {
private:

    std::list<Renderer*> Renderers;

public:

    void AddRenderer(Renderer* newrend)
    {
        Renderers.push_back(newrend);
    }

    void RemoveRenderer(Renderer* rend)
    {
        Renderers.remove(rend);
    }

    void RemoveRenderer(GameObject* obj)
    {
        Renderers.remove_if([obj](Renderer* rend) { return  rend->gameObject == obj; });
    }

    void draw(sf::RenderWindow* window) {
        for (Renderer* currrend : Renderers)
            window->draw(currrend->sprite);
    }

    int size()
    {
        return Renderers.size();
    }

};

GraphicsManagers GraphicsManager;