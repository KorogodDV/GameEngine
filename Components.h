#pragma once
#include <iostream>
#include <list>
#include <SFML/Graphics.hpp>


class Component {

};

class Collider : public Component {
public:

    int geometry;

};

class Renderer : public Component {
public:

    int sprite;

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

