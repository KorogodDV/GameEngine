#include "Components.h"
#include "GameObject.h"
#include "PhysicsManager.h"
#include "ScriptManager.h"
#include "GraphicsManager.h"
#include "Check—ollision.h"
#include "Storage.h"
#include "Application.h"
#include "uploadingStringFromTxt.h"
#include "VectorMath.h"

class Controller : public Script {

public:
    void execute()
    {
        if (0 < sf::Mouse::getPosition(*gameObject->GetApplication()->GetWindow()).x < gameObject->GetApplication()->GetWindow()->getSize().x or 0 < sf::Mouse::getPosition(*gameObject->GetApplication()->GetWindow()).y < gameObject->GetApplication()->GetWindow()->getSize().y)
            gameObject->GetComponent<Physics>()->acceleration = normalize(sf::Vector2f(sf::Mouse::getPosition(*gameObject->GetApplication()->GetWindow())) - gameObject->GetComponent<Physics>()->pos) * 400.f ;
        else
            gameObject->GetComponent<Physics>()->acceleration = sf::Vector2f(0, 0);
    }
};

class RemoveBall : public Script {

public:

    void onCollide()
    {
        (gameObject->GetApplication()->GetObjectsForRemove())->push_back(gameObject->name);
    }
};

int main()
{
    Applications App(1600, 900);

    App.GetStorage()->UploadScene("Aliens main scene.txt");
    App.GetStorage()->GetObject("player")->AddComponent<Controller>();
   
    App.Run();

    return 0;
}