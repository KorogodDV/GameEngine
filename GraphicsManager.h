#pragma once
#include <list>
#include <string>
#include <SFML/Graphics.hpp>
#include "Components.h"

class GameObject;
class Applications;

class GraphicsManagers {
private:

    std::list<Renderer*> Renderers;
    Applications* app;
    sf::Sprite background;

public:
    GraphicsManagers(Applications* app, std::string background_address);

    Applications* GetApplication();

    void AddRenderer(Renderer* newrend);

    void RemoveRenderer(Renderer* rend);

    void RemoveRenderer(GameObject* obj);

    void draw(sf::RenderWindow* window);

    void SetBackground(std::string address);

    sf::Sprite GetBackground();

    int size();
};