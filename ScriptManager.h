#pragma once
#include <list>
#include "Components.h"

class GameObject;
class Applications;

class ScriptManagers {
private:

    std::list<Script*> scripts;
    Applications* app;

public:

    ScriptManagers(Applications* app);

    Applications* GetApplication();

    void AddScript(Script* newscript);

    void RemoveScript(Script* script);

    void RemoveScript(GameObject* obj);

    void ObjectOnCollide(GameObject* obj1, GameObject* obj2);

    void update();

    int size();
};
