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

    sf::Sprite sprite;

};

class Script : public Component {
public:

    virtual void execute() {};
    virtual void onCollide() {};

};

class Physics : public Component {
public:

    sf::Vector2f speed = sf::Vector2f(0, 0);
    sf::Vector2f acceleration = sf::Vector2f(0, 0);

    float mass;

    bool gravity = 0;
    int collisionType = 0;

};

class TestScript : public Script {

    int val = 10;

public:

    void execute()
    {
        std::cout << val << "   ";
    }
};

