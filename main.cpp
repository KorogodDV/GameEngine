#include "Components.h"
#include "GameObject.h"
#include "PhysicsManager.h"
#include "ScriptManager.h"
#include "GraphicsManager.h"
#include "CheckÑollision.h"
#include "Storage.h"
#include "Application.h"
#include "uploadingStringFromTxt.h"

const int window_length = 1330;
const int window_width = 750;

/*
int main()
{
    Applications App;

    App.Storage->UploadScene("main scene.txt");

    App.Run();

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

    }