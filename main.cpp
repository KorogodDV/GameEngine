#include "Components.h"
#include "GameObject.h"
#include "PhysicsManager.h"
#include "ScriptManager.h"
#include "Checkcollision.h"

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

    /*sf::ConvexShape newHitbox;
    newHitbox.setFillColor(sf::Color::Red);
    newHitbox.setPointCount(3);
    newHitbox.setPoint(0, sf::Vector2f(100, 100));
    newHitbox.setPoint(1, sf::Vector2f(600, 100));
    newHitbox.setPoint(2, sf::Vector2f(600, 600));

    Physics* ph = obj.GetComponent<Physics>();
    ph->hitboxes.push_back(newHitbox);

    newHitbox.setFillColor(sf::Color::Green);
    newHitbox.setPoint(0, sf::Vector2f(100, 100));
    newHitbox.setPoint(1, sf::Vector2f(200, 100));
    newHitbox.setPoint(2, sf::Vector2f(300, 200));

    ph->hitboxes.push_back(newHitbox);

    ph = obj.GetComponent<Physics>();*/

    sf::ConvexShape newHitbox1;
    newHitbox1.setFillColor(sf::Color::Red);
    newHitbox1.setPointCount(3);
    newHitbox1.setPoint(0, sf::Vector2f(100, 100));
    newHitbox1.setPoint(1, sf::Vector2f(200, 100));
    newHitbox1.setPoint(2, sf::Vector2f(200, 200));

    sf::ConvexShape newHitbox2;
    newHitbox2.setFillColor(sf::Color::Green);
    newHitbox2.setPointCount(3);
    newHitbox2.setPoint(0, sf::Vector2f(100, 100));
    newHitbox2.setPoint(1, sf::Vector2f(100, 200));
    newHitbox2.setPoint(2, sf::Vector2f(200, 200));

   std::cout << checkCollision(newHitbox1, newHitbox2) << std::endl;
    

    while (window.isOpen())
    {
        sf::Event event;
        window.clear();
        //for (sf::ConvexShape hitbox : ph->hitboxes)
            //window.draw(hitbox);
        
        window.draw(newHitbox1);
        window.draw(newHitbox2);
        window.display();

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
                break;
            }
        }
    }
    //Collider* col = obj.GetComponent<Collider>();

    std::cout << 111 << std::endl;

    //std::cout << col->geometry;
    //std::cout << obj.GetComponent<Renderer>()->sprite;
    //std::cout << obj.GetComponent<Collider>()->geometry;

    //graphics(obj);
}