#include "Components.h"
#include "GameObject.h"
#include "PhysicsManager.h"
#include "ScriptManager.h"
#include "GraphicsManager.h"
#include "Check�ollision.h"
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

int main()
{
    Applications App(1600, 900);

class RemoveBall : public Script {

public:

    void execute()
    {
        gameObject->GetApplication()->GetStorage()->DeleteObject(gameObject->name);
    }
};

int main()
{
    Applications App;
    App.GetStorage()->UploadScene("main scene.txt");
    //App.GetStorage()->UploadScene("Catching Balls normal main scene.txt");

    App.GetStorage()->GetObject("ball1")->AddComponent<Controller>();

    App.Run();

    return 0;
}