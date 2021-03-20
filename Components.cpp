#include <map>
#include <string>
#include <typeinfo>
#include <iostream>
#include <cassert>
#include <list>
#include <type_traits>

class Component {

};

class Collider : public Component {
public:

    int geometry;

};

class Renderer : public Component {
public:

    int sprite;

};

class Script : public Component {
public:

    virtual void execute() {};

};

class TestScript : public Script {

    int val = 10;

public:

    void execute()
    {
        std::cout << val << "   ";
    };
};

class ScriptManagers {
private:

    std::list<Script*> scripts;

public:

    void AddScript(Script* newscript) 
    {
        scripts.push_back(newscript);
    };

    void RemoveScript(Script* script)
    {
        scripts.remove(script);
    };

    void update()
    {
        for (Script* currscript : scripts)
            currscript->execute();
    };

    int length()
    {
        return scripts.size();
    };

};

ScriptManagers ScriptManager;

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
    };

    template <typename T>
    void RemoveComponent()
    {
        if (std::is_base_of<Script, T>::value)
            ScriptManager.RemoveScript(static_cast<Script*>(components[typeid(T).name()]));
        else
            delete components[typeid(T).name()];
        components.erase(typeid(T).name());
    };
};

//void graphics(GameObject obj)
//{
//    Renderer* r = obj.GetComponent<Renderer>();
//}


int main()
{
    GameObject obj;

    obj.AddComponent<Renderer>();
    obj.AddComponent<Collider>();
    obj.AddComponent<Script>();
    obj.AddComponent<TestScript>();

    ScriptManager.update();

    std::cout << ScriptManager.length() << "   ";

    obj.RemoveComponent<Script>();

    ScriptManager.update();

    std::cout << ScriptManager.length() << "   ";

    obj.RemoveComponent<TestScript>();

    ScriptManager.update();

    std::cout << ScriptManager.length() << "   ";

    obj.RemoveComponent<Renderer>();

    Collider* col = obj.GetComponent<Collider>();

    std::cout << col->geometry;
    //std::cout << obj.GetComponent<Renderer>()->sprite;
    //std::cout << obj.GetComponent<Collider>()->geometry;

    //graphics(obj);
}