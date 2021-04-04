#pragma once
#include <list>
#include <SFML/Graphics.hpp>
#include "Components.h"
#include "PhysicsManager.h"
#include "GameObject.h"

void PhysicsManagers::AddPhysics(Physics* newphysics)
    {
        PhysicsComps.push_back(newphysics);
    }

void PhysicsManagers::RemovePhysics(Physics* physics)
    {
        PhysicsComps.remove(physics);
    }

void PhysicsManagers::RemovePhysics(GameObject* obj)
    {
        PhysicsComps.remove_if([obj](Physics* physics) { return  physics->gameObject == obj; });
    }

void PhysicsManagers::update() {};

int PhysicsManagers::size()
    {
        return PhysicsComps.size();
    }
