#pragma once
#include <list>
#include "Components.h"
#include "GameObject.h"
#include "ScriptManager.h"

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
        scripts.remove_if([obj](Script* script) { return  script->gameObject == obj; });
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

