#pragma once
#include <list>
#include "Components.h"

class GameObject;

class ScriptManagers {
private:

    std::list<Script*> scripts;

public:

    void AddScript(Script* newscript)
    {
        scripts.push_back(newscript);
    }

    void RemoveScript(Script* script)
    {
        scripts.remove(script);
    }

    void RemoveScript(GameObject* obj)
    {
        scripts.remove_if([obj](Script* script) { return  script->gameObject == obj; });
    }

    void update()
    {
        for (Script* currscript : scripts)
            currscript->execute();
    }

    int size()
    {
        return scripts.size();
    }
};
