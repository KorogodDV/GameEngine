#pragma once
#include "GraphicsManager.h"
#include "GameObject.h"
#include "Components.h"
#include <string>
#include <SFML/Graphics.hpp>
#include "Application.h"

GraphicsManagers::GraphicsManagers(Applications* app, std::string background_address)
{
    Renderers = *new std::list<Renderer*>;
    sf::Texture texture;
    background = *new sf::Sprite;
    texture.loadFromFile("textures/" + background_address);
    background.setTexture(texture);
    background.setPosition(0, 0);
    background.setScale(app->GetWindow()->getSize().x / background.getLocalBounds().width, app->GetWindow()->getSize().y / background.getLocalBounds().height);
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
    Renderers.remove_if([obj](Renderer* rend) { return  rend->gameObject->name == obj->name; });
}

void GraphicsManagers::draw(sf::RenderWindow* window)
{
    window->clear();
    window->draw(this->background);
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
    window->display();
}

void GraphicsManagers::SetBackground(std::string address)
{
    sf::Texture texture = *new sf::Texture;
    texture.loadFromFile("textures/" + address);
    this->background.setTexture(texture);
    this->background.setPosition(0, 0);
    this->background.setScale(app->GetWindow()->getSize().x / this->background.getLocalBounds().width, app->GetWindow()->getSize().y / this->background.getLocalBounds().height);
}

sf::Sprite GraphicsManagers::GetBackground()
{
    return this->background;
}

int GraphicsManagers::size()
{
    return Renderers.size();
}