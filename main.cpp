#include "Components.h"
#include "GameObject.h"
#include "PhysicsManager.h"
#include "ScriptManager.h"
#include "GraphicsManager.h"
#include "CheckÑollision.h"
#include "Storage.h"
#include "Application.h"

int main()
{
    Applications App;

    App.Storage.CreateObject("obj1");
    App.Storage.CreateObject("obj2");

    GameObject* obj1 = App.Storage.GetObject("obj1");

    obj1->AddComponent<Collider>();
    obj1->AddComponent<Renderer>();
    obj1->AddComponent<Physics>();
    obj1->AddComponent<TestScript>();
    obj1->AddComponent<Script>();

    GameObject* obj2 = App.Storage.GetObject("obj2");
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
   obj1->GetComponent<Renderer>()->showHitboxesBoundary = 1;

   sphere.setPosition(200, 200);

   obj2->GetComponent<Renderer>()->sprite = sphere;

   sf::ConvexShape hitbox(4);
   hitbox.setFillColor(sf::Color(0));
   hitbox.setOutlineColor(sf::Color::Blue);
   hitbox.setPoint(0, sf::Vector2f(400, 400));
   hitbox.setPoint(1, sf::Vector2f(600, 400));
   hitbox.setPoint(2, sf::Vector2f(600, 600));
   hitbox.setPoint(3, sf::Vector2f(400, 600));
   obj1->GetComponent<Collider>()->hitboxes.push_back(hitbox);

   App.Run();
   return 0;
}