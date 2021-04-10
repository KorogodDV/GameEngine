#pragma once
#include <list>
#include <SFML/Graphics.hpp>
#include "Components.h"
#include "PhysicsManager.h"
#include "GameObject.h"
#include "Check—ollision.h"
#include <iostream>
#include "Application.h"

PhysicsManagers::PhysicsManagers(Applications* app)
{
    PhysicsComps = *new std::list<Physics*>;
    this->app = app;
}

Applications* PhysicsManagers::GetApplication()
{
    return app;
}

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
        PhysicsComps.remove_if([obj](Physics* physics) { return  physics->gameObject->name == obj->name; });
    }

void PhysicsManagers::update()
{
    int PhysicsComps_len = PhysicsComps.size();
    auto iter = PhysicsComps.begin();
    while (iter != PhysicsComps.end())
    {
        bool collide_iter = false;
        if ((*iter)->collisionType)
        {
            int PhysicsComps_len1 = PhysicsComps.size();
            auto iter1 = next(iter);
            while (iter1 != PhysicsComps.end())
            {
                if ((*iter1)->collisionType)
                {
                    if (checkCollision((*(*iter)->gameObject->GetComponent<Collider>()->hitboxes.begin()), (*(*iter1)->gameObject->GetComponent<Collider>()->hitboxes.begin())))
                    {
                        collide_iter = true;
                        app->GetScriptManager()->ObjectOnCollide((*iter1)->gameObject);
                        //collide(&(*(*iter)->gameObject->GetComponent<Collider>()->hitboxes.begin()), &(*(*iter1)->gameObject->GetComponent<Collider>()->hitboxes.begin()), (*iter)->speed, (*iter1)->speed, 0.1);
                    }
                }
                if (PhysicsComps_len1 > PhysicsComps.size())
                {
                    --iter1;
                    PhysicsComps_len = PhysicsComps.size();
                    PhysicsComps_len1 = PhysicsComps.size();
                }
                ++iter1;
            }
        }

        if (collide_iter)
        {
            app->GetScriptManager()->ObjectOnCollide((*iter)->gameObject);
        }

        if (PhysicsComps_len > PhysicsComps.size())
        {
            --iter;
            PhysicsComps_len = PhysicsComps.size();
        }
        ++iter;
    //std::cout << "\n \n \n";
    }
    
}

int PhysicsManagers::size()
    {
        return PhysicsComps.size();
    }
