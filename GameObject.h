#pragma once
#include <map>
#include <string>
#include <typeinfo>
#include <cassert>
#include <SFML/Graphics.hpp>
#include "Components.h"
#include "PhysicsManager.h"
#include "ScriptManager.h"
#include "GraphicsManager.h"
#include "Application.h"

class GameObject
{
    std::map<std::string, Component*> components;

public:

    Applications* application;
    std::string name;

    template <typename T>
    T* GetComponent()
    {
        assert(components[typeid(T).name()] != 0);
        return static_cast<T*>(components[typeid(T).name()]);
    }

    template <typename T>
    void AddComponent()
    {
        T* newcomp = new T;
        newcomp->gameObject = this;
        components[typeid(T).name()] = newcomp;
        if (std::is_base_of<Script, T>::value)
            application->ScriptManager.AddScript(static_cast<Script*>(components[typeid(T).name()]));
        if (typeid(T).name() == typeid(Physics).name())
            application->PhysicsManager.AddPhysics(static_cast<Physics*>(components[typeid(T).name()]));
        if (typeid(T).name() == typeid(Renderer).name())
            application->GraphicsManager.AddRenderer(static_cast<Renderer*>(components[typeid(T).name()]));
    }

    template <typename T>
    void RemoveComponent()
    {
        if (std::is_base_of<Script, T>::value)
            application->ScriptManager.RemoveScript(static_cast<Script*>(components[typeid(T).name()]));
        else if (typeid(T).name() == typeid(Physics).name())
            application->PhysicsManager.RemovePhysics(static_cast<Physics*>(components[typeid(T).name()]));
        else if (typeid(T).name() == typeid(Renderer).name())
            application->GraphicsManager.RemoveRenderer(static_cast<Renderer*>(components[typeid(T).name()]));
        else
            delete components[typeid(T).name()];
        components.erase(typeid(T).name());
    }
};

bool operator==(GameObject obj1, GameObject obj2)
{
    return obj1.name == obj2.name;
}