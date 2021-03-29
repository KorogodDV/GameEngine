#include "Components.h"
#include "GameObject.h"
#include "PhysicsManager.h"
#include "ScriptManager.h"
#include "GraphicsManager.h"
#include "CheckÑollision.h"
#include "Storage.h"

const int window_length = 1280;
const int window_width = 720;

/*
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
}*/

int main()
{
    float t = 0.1;
    sf::RenderWindow window(sf::VideoMode(window_length, window_width), "test");

    sf::ConvexShape Hitbox1(3);
    sf::ConvexShape Hitbox2(3);
    
    Hitbox1.setFillColor(sf::Color::Red);
    Hitbox2.setFillColor(sf::Color::Green);

    Hitbox1.setPoint(0, sf::Vector2f(200, 200));
    Hitbox1.setPoint(1, sf::Vector2f(250, 250));
    Hitbox1.setPoint(2, sf::Vector2f(200, 250));

    Hitbox2.setPoint(0, sf::Vector2f(500, 550));
    Hitbox2.setPoint(1, sf::Vector2f(450, 500));
    Hitbox2.setPoint(2, sf::Vector2f(500, 450));
    
    //std::cout << checkCollision(Hitbox1, Hitbox2) << std::endl;

    sf::Vector2f speed1(1,1);
    sf::Vector2f speed2(-1, -1);

    while (window.isOpen())
    {
        sf::Event event;
        window.clear();
        window.draw(Hitbox1);
        window.draw(Hitbox2);
        window.display();

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
                break;
            }
        }

        if (checkCollision(Hitbox1, Hitbox2))
        {
            std::cout << 1 << std::endl;
            collide(&Hitbox1, &Hitbox2, speed1, speed2, t);
            sf::Vector2f speed = speed1;
            speed1 = sf::Vector2f(0, 0);
            speed2 = sf::Vector2f(0, 0);
        }

        if ((Hitbox1.getPoint(0).x < 0) or (Hitbox1.getPoint(0).x > 1150))
        {
            speed1.x = -speed1.x;
        }
        if ((Hitbox1.getPoint(0).y < 0) or (Hitbox1.getPoint(0).y > 670))
        {
            speed1.y = -speed1.y;
        }
        if ((Hitbox2.getPoint(0).x < 0) or (Hitbox2.getPoint(0).x > 1150))
        {
            speed2.x = -speed2.x;
        }
        if ((Hitbox2.getPoint(0).y < 0) or (Hitbox2.getPoint(0).y > 670))
        {
            speed2.y = -speed2.y;
        }

        mymove(&Hitbox1, speed1, t);
        mymove(&Hitbox2, speed2, t);
    }
    
    return 0;
}