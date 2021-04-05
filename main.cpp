#include "Components.h"
#include "GameObject.h"
#include "PhysicsManager.h"
#include "ScriptManager.h"
#include "GraphicsManager.h"
#include "CheckÑollision.h"
#include "Storage.h"

const int window_length = 1330;
const int window_width = 750;

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
    float t = 0.5;
    sf::RenderWindow window(sf::VideoMode(window_length, window_width), "test");

    sf::ConvexShape Hitbox1(3);
    sf::ConvexShape Hitbox2(3);
    
    Hitbox1.setFillColor(sf::Color::Red);
    Hitbox2.setFillColor(sf::Color::Green);

    Hitbox1.setPoint(0, sf::Vector2f(100, 200));
    Hitbox1.setPoint(1, sf::Vector2f(100, 250));
    Hitbox1.setPoint(2, sf::Vector2f(200, 250));

    Hitbox2.setPoint(0, sf::Vector2f(300, 400));
    Hitbox2.setPoint(1, sf::Vector2f(300, 450));
    Hitbox2.setPoint(2, sf::Vector2f(400, 450));

    sf::ConvexShape Wall1(4);
    sf::ConvexShape Wall2(4);
    sf::ConvexShape Wall3(4);
    sf::ConvexShape Wall4(4);

    Wall1.setFillColor(sf::Color::Red);
    Wall2.setFillColor(sf::Color::Green);
    Wall3.setFillColor(sf::Color::Blue);
    Wall4.setFillColor(sf::Color::White);

    Wall1.setPoint(0, sf::Vector2f(0, 50));
    Wall1.setPoint(1, sf::Vector2f(0, 0));
    Wall1.setPoint(2, sf::Vector2f(1280, 0));
    Wall1.setPoint(3, sf::Vector2f(1280, 50));

    Wall2.setPoint(0, sf::Vector2f(1280, 0));
    Wall2.setPoint(1, sf::Vector2f(1280, 720));
    Wall2.setPoint(2, sf::Vector2f(1330, 720));
    Wall2.setPoint(3, sf::Vector2f(1330, 0));

    Wall3.setPoint(0, sf::Vector2f(0, 720));
    Wall3.setPoint(1, sf::Vector2f(0, 750));
    Wall3.setPoint(2, sf::Vector2f(1280, 750));
    Wall3.setPoint(3, sf::Vector2f(1280, 720));

    Wall4.setPoint(0, sf::Vector2f(50, 0));
    Wall4.setPoint(1, sf::Vector2f(0, 0));
    Wall4.setPoint(2, sf::Vector2f(0, 720));
    Wall4.setPoint(3, sf::Vector2f(50, 720));
    
    //std::cout << checkCollision(Hitbox1, Hitbox2) << std::endl;

    sf::Vector2f speed1(-1, 2);
    sf::Vector2f speed2(1, 1);

    while (window.isOpen())
    {
        sf::Event event;
        window.clear();
        window.draw(Hitbox1);
        window.draw(Hitbox2);
        window.draw(Wall1);
        window.draw(Wall2);
        window.draw(Wall3);
        window.draw(Wall4);
        window.display();

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
                break;
            }
        }

        mymove(&Hitbox1, speed1, t);
        mymove(&Hitbox2, speed2, t);


        if (checkCollision(Hitbox1, Hitbox2))
        {
            //std::cout << 1 << std::endl;
            /*for (int i = 0; i < 3; i++)
            {
                std::cout << Hitbox1.getPoint(i).x << ' ' << Hitbox1.getPoint(i).y << std::endl;
                std::cout << Hitbox2.getPoint(i).x << ' ' << Hitbox2.getPoint(i).y << std::endl;
            }*/
            
            collide(&Hitbox1, &Hitbox2, speed1, speed2, t);
            sf::Vector2f speed = speed1;
            speed1 = speed2;
            speed2 = speed;
        }

        if ((checkCollision(Hitbox1, Wall2)) or (checkCollision(Hitbox1, Wall4)))
        {
            speed1.x = -speed1.x;
        }
        if ((checkCollision(Hitbox1, Wall1)) or (checkCollision(Hitbox1, Wall3)))
        {
            speed1.y = -speed1.y;
        }
        if ((checkCollision(Hitbox2, Wall2)) or (checkCollision(Hitbox2, Wall4)))
        {
            speed2.x = -speed2.x;
        }
        if ((checkCollision(Hitbox2, Wall1)) or (checkCollision(Hitbox2, Wall3)))
        {
            speed2.y = -speed2.y;
        }
    }
    
    return 0;
}