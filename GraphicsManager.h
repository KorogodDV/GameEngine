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

    void RemovePhysics(Renderer* rend)
    {
        Renderers.remove(rend);
    }

    void draw(sf::RenderWindow* window) {
        for (Renderer* currrend : Renderers)
            window->draw(currrend->sprite);
    }

};

GraphicsManagers GraphicsManager;