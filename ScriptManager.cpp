#pragma once
#include <list>
#include "Components.h"
#include "GameObject.h"
#include "ScriptManager.h"
#include "Application.h"

ScriptManagers::ScriptManagers(Applications* app)
{
    scripts = *new std::list<Script*>;
    this->app = app;
}

Applications* ScriptManagers::GetApplication()
{
    return app;
}

void ScriptManagers::AddScript(Script* newscript)
{
    scripts.push_back(newscript);
}

void ScriptManagers::RemoveScript(Script* script)
{
    scripts.remove(script);
}

void ScriptManagers::RemoveScript(GameObject* obj)
{
    scripts.remove_if([obj](Script* script) { return  script->gameObject->name == obj->name; });
}

void ScriptManagers::ObjectOnCollide(GameObject* obj)
{
    for (Script* script : scripts)
    {
        if (script->gameObject->name == obj->name)
            script->onCollide();
    }
}

void ScriptManagers::update()
{
    for (Script* currscript : scripts)
        currscript->execute();
}

int ScriptManagers::size()
{
    return scripts.size();
}

