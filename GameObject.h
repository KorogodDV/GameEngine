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
    Applications* application;

public:

    std::string name;
    std::string type;
    
    GameObject(std::string name, Applications* app, std::string type = "");

    template <typename T>
    T* GetComponent()
    {
        assert(components[typeid(T).name()]);
        return static_cast<T*>(components[typeid(T).name()]);
    }

    template <typename T>
    void AddComponent()
    {
        T* newcomp = new T;
        newcomp->gameObject = this;
        components[typeid(T).name()] = newcomp;
        if (std::is_base_of<Script, T>::value)
            application->GetScriptManager()->AddScript(static_cast<Script*>(components[typeid(T).name()]));
        if (typeid(T).name() == typeid(Physics).name())
            application->GetPhysicsManager()->AddPhysics(static_cast<Physics*>(components[typeid(T).name()]));
        if (typeid(T).name() == typeid(Renderer).name())
            application->GetGraphicsManager()->AddRenderer(static_cast<Renderer*>(components[typeid(T).name()]));
    }

    template <typename T>
    void RemoveComponent()
    {
        if (std::is_base_of<Script, T>::value)
            application->GetScriptManager()->RemoveScript(static_cast<Script*>(components[typeid(T).name()]));
        else if (typeid(T).name() == typeid(Physics).name())
            application->GetPhysicsManager()->RemovePhysics(static_cast<Physics*>(components[typeid(T).name()]));
        else if (typeid(T).name() == typeid(Renderer).name())
            application->GetGraphicsManager()->RemoveRenderer(static_cast<Renderer*>(components[typeid(T).name()]));
        else
            delete components[typeid(T).name()];
        components.erase(typeid(T).name());
    }

    Applications* GetApplication();
};

inline bool operator==(GameObject obj1, GameObject obj2)
{
    return obj1.name == obj2.name;
}