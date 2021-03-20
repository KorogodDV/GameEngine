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
    };

    void RemovePhysics(Physics* physics)
    {
        PhysicsComps.remove(physics);
    };

    //void update()
    //{
    //    for (Physics* currscript : PhysicsComps)
    //        currscript->execute();
    //};

    int length()
    {
        return PhysicsComps.size();
    };

};

PhysicsManagers PhysicsManager;
