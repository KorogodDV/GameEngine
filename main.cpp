#include "Components.h"
#include "GameObject.h"
#include "PhysicsManager.h"
#include "ScriptManager.h"
#include "GraphicsManager.h"
#include "Check—ollision.h"
#include "Storage.h"
#include "Application.h"
#include "uploadingStringFromTxt.h"

class Controller : public Script {

public:

    void execute()
    {
        if (0 < sf::Mouse::getPosition(*gameObject->GetApplication()->GetWindow()).x < gameObject->GetApplication()->GetWindow()->getSize().x or 0 < sf::Mouse::getPosition(*gameObject->GetApplication()->GetWindow()).y < gameObject->GetApplication()->GetWindow()->getSize().y)
            gameObject->GetComponent<Physics>()->acceleration = (sf::Vector2f(sf::Mouse::getPosition(*gameObject->GetApplication()->GetWindow())) - gameObject->GetComponent<Physics>()->pos) * 10.f;
        else
            gameObject->GetComponent<Physics>()->acceleration = sf::Vector2f(0, 0);
    }

};

class Move : public Script {

public:

    void execute()
    {
        gameObject->GetComponent<Physics>()->speed += gameObject->GetComponent<Physics>()->acceleration * gameObject->GetApplication()->GetLastFrameDurationAsSeconds();
        gameObject->GetComponent<Physics>()->pos += gameObject->GetComponent<Physics>()->speed * gameObject->GetApplication()->GetLastFrameDurationAsSeconds();
        (gameObject->GetComponent<Renderer>()->sprite).move(gameObject->GetApplication()->GetLastFrameDurationAsSeconds() * gameObject->GetComponent<Physics>()->speed);
        for (int i = 0; i < gameObject->GetComponent<Collider>()->hitboxes.begin()->getPointCount(); i++)
        {
            gameObject->GetComponent<Collider>()->hitboxes.begin()->setPoint(i, gameObject->GetComponent<Collider>()->hitboxes.begin()->getPoint(i) + gameObject->GetComponent<Physics>()->speed * gameObject->GetApplication()->GetLastFrameDurationAsSeconds());
        }
    }

};

int main()
{
    Applications App;
    App.GetStorage()->UploadScene("main scene.txt");
    App.GetStorage()->GetObject("ball1")->AddComponent<Controller>();
    App.GetStorage()->GetObject("ball1")->AddComponent<Move>();
    App.GetStorage()->GetObject("ball2")->AddComponent<Move>();
    App.GetStorage()->GetObject("ball3")->AddComponent<Move>();


    App.Run();

    return 0;
}