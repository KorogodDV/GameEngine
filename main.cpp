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

    App.Storage->CreateObject("obj1");
    App.Storage->CreateObject("obj2");

    GameObject* obj1 = App.Storage->GetObject("obj1");

    obj1->AddComponent<Collider>();
    obj1->AddComponent<Renderer>();
    obj1->AddComponent<Physics>();
    //obj1->AddComponent<TestScript>();
    obj1->AddComponent<Script>();

    GameObject* obj2 = App.Storage->GetObject("obj2");
    obj2->AddComponent<Renderer>();
    //obj2->AddComponent<TestScript>();

   sf::Image ballImage;
   ballImage.loadFromFile("textures/ball2.png");
   ballImage.createMaskFromColor(sf::Color::White);

   sf::Texture balltexture;
   balltexture.loadFromImage(ballImage);
   sf::Sprite sphere(balltexture);
   sphere.setPosition(434, 434);

   obj1->GetComponent<Renderer>()->sprite = sphere;
   obj1->GetComponent<Renderer>()->showHitboxesBoundary = 1;

   sphere.setPosition(1200, 200);
   sphere.setColor(sf::Color::White);

   obj2->GetComponent<Renderer>()->sprite = sphere;

   sf::ConvexShape hitbox(4);
   hitbox.setFillColor(sf::Color(0));
   hitbox.setOutlineColor(sf::Color::Blue);
   hitbox.setOutlineThickness(1);
   hitbox.setPoint(0, sf::Vector2f(400, 400));
   hitbox.setPoint(1, sf::Vector2f(600, 400));
   hitbox.setPoint(2, sf::Vector2f(600, 600));
   hitbox.setPoint(3, sf::Vector2f(400, 600));
   obj1->GetComponent<Collider>()->hitboxes.push_back(hitbox);

   App.Storage->CreateBasicObject("ball1 ball ball2.png 200 200 0 0 10 1 0 0 5");

   //std::string buffer = uploadBufferFromFile("scenes/main scene.txt");
   //std::vector<std::string> objects;
   //split(buffer, objects, '\n');
   //while (objects[0][0] == '/')
   //    objects.erase(objects.begin());
   //for (std::string str : objects)
   // std::cout << "   \n NEWLINE  " << str;

   App.Run();


   return 0;
}

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