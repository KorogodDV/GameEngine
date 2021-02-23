#include <map>
#include <string>
#include <typeinfo>
#include <iostream>
#include <cassert>

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

class GameObject
{
    std::map<std::string, Component*> components;

public:
    template <typename T>
    T* GetComponent()
    {
        assert(components[typeid(T).name()] != 0);
        std::cout << components.size();
        std::cout << typeid(T).name();
        std::cout << components[typeid(T).name()] << "     ";
        std::cout << static_cast<Renderer*>(components[typeid(T).name()]) << "    ";
        std::cout << static_cast<Renderer*>(components[typeid(T).name()])->sprite << "     ";
        T* comp = new T;
        comp = static_cast<T*>(components[typeid(T).name()]);
        return comp;
    };

    template <typename T>
    void AddComponent(T component)
    {
        std::cout << components.size();
        components[typeid(component).name()] = &component;
        std::cout << &component;
        //std::cout << component.sprite << "     ";
        //std::cout << static_cast<Renderer*>(components[typeid(component).name()])->sprite << "     ";
    };

    //RemoveComponent
};

void graphics(GameObject obj)
{
    Renderer* r = obj.GetComponent<Renderer>();
}

int main()
{
    GameObject obj;

    Renderer rend;
    rend.sprite = 1525;

    Collider coll;
    coll.geometry = 101;

    //std::map<std::string, Component*> test;
    //test[typeid(rend).name()] = &rend;
    //std::cout << static_cast<Renderer*>(test[typeid(rend).name()])->sprite;

    obj.AddComponent<Renderer>(rend);
    //obj.AddComponent<Collider>(coll);

    //Renderer* newrend = obj.GetComponent<Renderer>();
    //std::cout << newrend->sprite;
    std::cout << obj.GetComponent<Renderer>()->sprite;

    //graphics(obj);
}