#include "Components.h"
#include "GameObject.h"
#include "PhysicsManager.h"
#include "ScriptManager.h"
#include "Check—ollision.h"

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


   sf::Image ballImage;
   ballImage.loadFromFile("textures/ball.png");
   ballImage.createMaskFromColor(sf::Color::White);

   sf::Texture balltexture;
   balltexture.loadFromImage(ballImage);
   sf::Sprite sphere(balltexture);
   sphere.setPosition(500, 500);
    

    while (window.isOpen())
    {
        sf::Event event;
        window.clear();
        window.draw(sphere);
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