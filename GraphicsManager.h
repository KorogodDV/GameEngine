#pragma once
#include <list>
#include <SFML/Graphics.hpp>
#include "Components.h"

class GameObject;
class Applications;

class GraphicsManagers {
private:

    std::list<Renderer*> Renderers;
    Applications* app;

public:
    GraphicsManagers(Applications* app);

    Applications* GetApplication();

    void AddRenderer(Renderer* newrend);

    void RemoveRenderer(Renderer* rend);

    void RemoveRenderer(GameObject* obj);

    void draw(sf::RenderWindow* window);

    int size();
};