#include "Components.h"
#include "GameObject.h"
#include "PhysicsManager.h"
#include "ScriptManager.h"
#include "GraphicsManager.h"
#include "CheckÑollision.h"
#include "Storage.h"

const int window_length = 1280;
const int window_width = 720;

int main()
{
    sf::RenderWindow window(sf::VideoMode(window_length, window_width), "test");

    storage.CreateObject("obj1");
    storage.CreateObject("obj2");

    GameObject* obj1 = storage.GetObject("obj1");

    obj1->AddComponent<Collider>();
    obj1->AddComponent<Renderer>();
    obj1->AddComponent<Physics>();
    obj1->AddComponent<TestScript>();
    obj1->AddComponent<Script>();

    GameObject* obj2 = storage.GetObject("obj2");
    obj2->AddComponent<Renderer>();
    obj2->AddComponent<TestScript>();

   sf::Image ballImage;
   ballImage.loadFromFile("textures/ball.png");
   ballImage.createMaskFromColor(sf::Color::White);

   sf::Texture balltexture;
   balltexture.loadFromImage(ballImage);
   sf::Sprite sphere(balltexture);
   sphere.setPosition(500, 500);

   obj1->GetComponent<Renderer>()->sprite = sphere;

   sphere.setPosition(200, 200);

   obj2->GetComponent<Renderer>()->sprite = sphere;

    while (window.isOpen())
    {
        sf::Event event;
        window.clear();
        GraphicsManager.draw(&window);
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
    return 0;
}