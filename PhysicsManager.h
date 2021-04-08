#pragma once
#include <list>
#include <SFML/Graphics.hpp>
#include "Components.h"

class GameObject;
class Applications;

class PhysicsManagers {
private:

    Applications* app;
    std::list<Physics*> PhysicsComps;

public:

    PhysicsManagers(Applications* app);

    Applications* GetApplication();

    void AddPhysics(Physics* newphysics);

    void RemovePhysics(Physics* physics);

    void RemovePhysics(GameObject* obj);

    void update();

    int size();

};
