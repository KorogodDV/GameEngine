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

    int geometry;

};

class Renderer : public Component {
public:

    sf::Sprite sprite;

};

class Script : public Component {
public:

    virtual void execute() {};

};

class Physics : public Component {
public:

    std::list<sf::ConvexShape> hitboxes;

};

class TestScript : public Script {

    int val = 10;

public:

    void execute()
    {
        std::cout << val << "   ";
    };
};

