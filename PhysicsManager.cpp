#pragma once
#include <list>
#include <SFML/Graphics.hpp>
#include "Components.h"
#include "PhysicsManager.h"
#include "GameObject.h"
#include "Check—ollision.h"
#include <iostream>

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

void PhysicsManagers::update(sf::Time time)
{
    for (auto iter = PhysicsComps.begin(); iter != PhysicsComps.end(); ++iter)
    {
        if ((*iter)->collisionType)
            for (auto iter1 = next(iter); iter1 != PhysicsComps.end(); ++iter1)
                if ((*iter1)->collisionType)
                    if (checkCollision((*(*iter)->gameObject->GetComponent<Collider>()->hitboxes.begin()), (*(*iter1)->gameObject->GetComponent<Collider>()->hitboxes.begin())))
                    {
                        std::cout << 1 << std::endl;
                        //collide(&(*(*iter)->gameObject->GetComponent<Collider>()->hitboxes.begin()), &(*(*iter1)->gameObject->GetComponent<Collider>()->hitboxes.begin()), (*iter)->speed, (*iter1)->speed, 0.1);
                    }
        mymove(&(*(*iter)->gameObject->GetComponent<Collider>()->hitboxes.begin()), (*iter)->speed, time.asSeconds());
        ((*iter)->gameObject->GetComponent<Renderer>()->sprite).move(time.asSeconds() * (*iter)->speed);
        //std::cout << (*(*iter)->gameObject->GetComponent<Collider>()->hitboxes.begin()).getPoint(0).x << std::endl;
    }
    
};

int PhysicsManagers::size()
    {
        return PhysicsComps.size();
    }
