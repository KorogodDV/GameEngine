#include "Components.h"
#include "GameObject.h"
#include "PhysicsManager.h"
#include "ScriptManager.h"
#include "GraphicsManager.h"
#include "CheckÑollision.h"
#include "Storage.h"
#include "Application.h"
#include "uploadingStringFromTxt.h"

int main()
{
    Applications App;

    App.GetStorage()->UploadScene("main scene.txt");

    App.Run();

    return 0;
}

//int main()
//{
//    float t = 0.5;
//    sf::RenderWindow window(sf::VideoMode(window_length, window_width), "test");
//
//    sf::ConvexShape Hitbox1(3);
//    sf::ConvexShape Hitbox2(3);
//    
//    Hitbox1.setFillColor(sf::Color::Red);
//    Hitbox2.setFillColor(sf::Color::Green);
//
//    Hitbox1.setPoint(0, sf::Vector2f(100, 200));
//    Hitbox1.setPoint(1, sf::Vector2f(100, 250));
//    Hitbox1.setPoint(2, sf::Vector2f(200, 250));
//
//    Hitbox2.setPoint(0, sf::Vector2f(300, 400));
//    Hitbox2.setPoint(1, sf::Vector2f(300, 450));
//    Hitbox2.setPoint(2, sf::Vector2f(400, 450));
//
//    sf::ConvexShape Wall1(4);
//    sf::ConvexShape Wall2(4);
//    sf::ConvexShape Wall3(4);
//    sf::ConvexShape Wall4(4);
//
//    Wall1.setFillColor(sf::Color::Red);
//    Wall2.setFillColor(sf::Color::Green);
//    Wall3.setFillColor(sf::Color::Blue);
//    Wall4.setFillColor(sf::Color::White);
//
//    Wall1.setPoint(0, sf::Vector2f(0, 50));
//    Wall1.setPoint(1, sf::Vector2f(0, 0));
//    Wall1.setPoint(2, sf::Vector2f(1280, 0));
//    Wall1.setPoint(3, sf::Vector2f(1280, 50));
//
//    Wall2.setPoint(0, sf::Vector2f(1280, 0));
//    Wall2.setPoint(1, sf::Vector2f(1280, 720));
//    Wall2.setPoint(2, sf::Vector2f(1330, 720));
//    Wall2.setPoint(3, sf::Vector2f(1330, 0));
//
//    Wall3.setPoint(0, sf::Vector2f(0, 720));
//    Wall3.setPoint(1, sf::Vector2f(0, 750));
//    Wall3.setPoint(2, sf::Vector2f(1280, 750));
//    Wall3.setPoint(3, sf::Vector2f(1280, 720));
//
//    Wall4.setPoint(0, sf::Vector2f(50, 0));
//    Wall4.setPoint(1, sf::Vector2f(0, 0));
//    Wall4.setPoint(2, sf::Vector2f(0, 720));
//    Wall4.setPoint(3, sf::Vector2f(50, 720));
//    
//    //std::cout << checkCollision(Hitbox1, Hitbox2) << std::endl;
//
//    sf::Vector2f speed1(-1, 2);
//    sf::Vector2f speed2(1, 1);
//
//    while (window.isOpen())
//    {
//        sf::Event event;
//        window.clear();
//        window.draw(Hitbox1);
//        window.draw(Hitbox2);
//        window.draw(Wall1);
//        window.draw(Wall2);
//        window.draw(Wall3);
//        window.draw(Wall4);
//        window.display();
//
//        while (window.pollEvent(event))
//        {
//            if (event.type == sf::Event::Closed)
//            {
//                window.close();
//                break;
//            }
//        }

//int main()
//{
//    float t = 0.0001;
//    sf::RenderWindow window(sf::VideoMode(window_length, window_width), "test");
//
//    sf::ConvexShape Hitbox1(3);
//    sf::ConvexShape Hitbox2(3);
//    
//    Hitbox1.setFillColor(sf::Color::Red);
//    Hitbox2.setFillColor(sf::Color::Green);
//
//    Hitbox1.setPoint(0, sf::Vector2f(1, 200));
//    Hitbox1.setPoint(1, sf::Vector2f(51, 250));
//    Hitbox1.setPoint(2, sf::Vector2f(1, 250));
//
//    Hitbox2.setPoint(0, sf::Vector2f(51, 200));
//    Hitbox2.setPoint(1, sf::Vector2f(51, 250));
//    Hitbox2.setPoint(2, sf::Vector2f(101, 250));
//    
//    //std::cout << checkCollision(Hitbox1, Hitbox2) << std::endl;
//
//    sf::Vector2f speed1(-1, 0);
//    sf::Vector2f speed2(-1, 0);
//
//    while (window.isOpen())
//    {
//        sf::Event event;
//        window.clear();
//        window.draw(Hitbox1);
//        window.draw(Hitbox2);
//        window.display();
//
//        while (window.pollEvent(event))
//        {
//            if (event.type == sf::Event::Closed)
//            {
//                window.close();
//                break;
//            }
//        }
//
//        mymove(&Hitbox1, speed1, t);
//        mymove(&Hitbox2, speed2, t);
//
//        if (checkCollision(Hitbox1, Hitbox2))
//        {
//            std::cout << 1 << std::endl;
//            for (int i = 0; i < 3; i++)
//            {
//                std::cout << Hitbox1.getPoint(i).x << ' ' << Hitbox1.getPoint(i).y << std::endl;
//                std::cout << Hitbox2.getPoint(i).x << ' ' << Hitbox2.getPoint(i).y << std::endl;
//            }
//            
//            collide(&Hitbox1, &Hitbox2, speed1, speed2, t);
//            sf::Vector2f speed = speed1;
//            speed1 = speed2;
//            speed2 = speed;
//        }
//
//        if ((Hitbox1.getPoint(0).x < 0) or (Hitbox1.getPoint(0).x > 1200))
//        {
//            speed1.x = -speed1.x;
//        }
//        if ((Hitbox1.getPoint(0).y < 0) or (Hitbox1.getPoint(0).y > 720))
//        {
//            speed1.y = -speed1.y;
//        }
//        if ((Hitbox2.getPoint(0).x < 0) or (Hitbox2.getPoint(0).x > 1200))
//        {
//            speed2.x = -speed2.x;
//        }
//        if ((Hitbox2.getPoint(0).y < 0) or (Hitbox2.getPoint(0).y > 720))
//        {
//            speed2.y = -speed2.y;
//        }
//    }
//    
//    return 0;
//}