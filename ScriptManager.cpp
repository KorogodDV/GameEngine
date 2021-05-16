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

void ScriptManagers::ObjectOnCollide(GameObject* obj1, GameObject* obj2)
{
    for (Script* script : scripts)
    {
        if (script->gameObject->name == obj1->name)
        {
            script->onCollide(obj2);
        }
    }
}

void ScriptManagers::update()
{
    int scripts_len = scripts.size();
    auto iter = scripts.begin();
    while (iter != scripts.end())
    {
        (*iter)->execute();
        if (scripts_len > scripts.size())
        {
            --iter;
            scripts_len = scripts.size();
        }
        ++iter;
    }
}

int ScriptManagers::size()
{
    return scripts.size();
}
