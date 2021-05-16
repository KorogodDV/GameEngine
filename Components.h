#pragma once
#include <iostream>
#include <list>
#include <SFML/Graphics.hpp>

class GameObject;


class Component {
public:
    GameObject* gameObject;
};

class Collider : public Component {
public:

    std::list<sf::ConvexShape> hitboxes;

};

class Renderer : public Component {
public:

    sf::Image image;
    sf::Texture texture;
    sf::Sprite sprite;
    bool showSprite = 1;
    bool showHitboxesBoundary = 0;

};

class Script : public Component {
public:

    virtual void execute() {};
    virtual void onCollide(GameObject* obj) {};

};

class Physics : public Component {
public:

    sf::Vector2f pos = sf::Vector2f(0, 0);
    sf::Vector2f speed = sf::Vector2f(0, 0);
    sf::Vector2f acceleration = sf::Vector2f(0, 0);

    float mass = 0;

    bool gravity = 0;
    int collisionType = 0;

};

class Move : public Script {

public:

    void execute();
};

