#pragma once
#include <list>
#include <SFML/Graphics.hpp>
#include "Components.h"

class GameObject;

class PhysicsManagers {
private:

    std::list<Physics*> PhysicsComps;

public:

    void AddPhysics(Physics* newphysics);

    void RemovePhysics(Physics* physics);

    void RemovePhysics(GameObject* obj);

    void update(sf::Time time);

    int size();

};
