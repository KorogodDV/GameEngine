#include "Components.h"
#include "GameObject.h"
#include "PhysicsManager.h"
#include "ScriptManager.h"

const int window_length = 1280;
const int window_width = 720;


//void graphics(GameObject obj)
//{
//    Renderer* r = obj.GetComponent<Renderer>();
//}


int main()
{
    sf::RenderWindow window(sf::VideoMode(window_length, window_width), "test");


    GameObject obj;

    obj.AddComponent<Renderer>();
    obj.AddComponent<Collider>();
    obj.AddComponent<Physics>();
    obj.AddComponent<TestScript>();

    //sf::ConvexShape newHitbox;
    //newHitbox.setPointCount(3);

    Physics* ph = obj.GetComponent<Physics>();
    //ph->hitboxes.push_back(newHitbox);

    Collider* col = obj.GetComponent<Collider>();

    std::cout << col->geometry;
    //std::cout << obj.GetComponent<Renderer>()->sprite;
    //std::cout << obj.GetComponent<Collider>()->geometry;

    //graphics(obj);
}