#pragma once
#include <list>
#include "Components.h"

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

    void update()
    {
        for (Script* currscript : scripts)
            currscript->execute();
    }

};

ScriptManagers ScriptManager;
