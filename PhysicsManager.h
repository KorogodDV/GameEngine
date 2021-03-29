#pragma once
#include <list>
#include <SFML/Graphics.hpp>
#include "Components.h"

class PhysicsManagers {
private:

    std::list<Physics*> PhysicsComps;

public:

    void AddPhysics(Physics* newphysics)
    {
        PhysicsComps.push_back(newphysics);
    }

    void RemovePhysics(Physics* physics)
    {
        PhysicsComps.remove(physics);
    }

    void RemovePhysics(GameObject* obj)
    {
        PhysicsComps.remove_if([obj](Physics* physics) { return  physics->gameObject == obj; });
    }

    void update() {};

    int size()
    {
        return PhysicsComps.size();
    }

};

PhysicsManagers PhysicsManager;
