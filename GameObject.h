#pragma once
#include <map>
#include <string>
#include <typeinfo>
#include <cassert>
#include <SFML/Graphics.hpp>
#include "Components.h"
#include "PhysicsManager.h"
#include "ScriptManager.h"



class GameObject
{
    std::map<std::string, Component*> components;

public:

    template <typename T>
    T* GetComponent()
    {
        assert(components[typeid(T).name()] != 0);
        return static_cast<T*>(components[typeid(T).name()]);
    };

    template <typename T>
    void AddComponent()
    {
        components[typeid(T).name()] = new T;
        if (std::is_base_of<Script, T>::value)
            ScriptManager.AddScript(static_cast<Script*>(components[typeid(T).name()]));
        if (typeid(T).name() == typeid(Physics).name())
            PhysicsManager.AddPhysics(static_cast<Physics*>(components[typeid(T).name()]));
    };

    template <typename T>
    void RemoveComponent()
    {
        if (std::is_base_of<Script, T>::value)
            ScriptManager.RemoveScript(static_cast<Script*>(components[typeid(T).name()]));
        else if (typeid(T).name() == typeid(Physics).name())
            PhysicsManager.RemovePhysics(static_cast<Physics*>(components[typeid(T).name()]));
        else
            delete components[typeid(T).name()];
        components.erase(typeid(T).name());
    };
};