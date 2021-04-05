#pragma once
#include <list>
#include "Components.h"

class GameObject;

class ScriptManagers {
private:

    std::list<Script*> scripts;

public:

    void AddScript(Script* newscript);

    void RemoveScript(Script* script);

    void RemoveScript(GameObject* obj);

    void update();

    int size();
};
