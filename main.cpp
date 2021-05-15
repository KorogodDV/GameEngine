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

class ReturnToField : public Script {

public:
    void execute()
    {
        if (this->gameObject->GetComponent<Collider>()->hitboxes.front().getPoint(1).x < 0)
        {
            float length = -1 * this->gameObject->GetComponent<Collider>()->hitboxes.front().getPoint(0).x;
            gameObject->GetComponent<Physics>()->pos.x += this->gameObject->GetApplication()->GetWindow()->getSize().x + 2 * length;
            (gameObject->GetComponent<Renderer>()->sprite).move(this->gameObject->GetApplication()->GetWindow()->getSize().x + 2 * length, 0);
            for (int i = 0; i < gameObject->GetComponent<Collider>()->hitboxes.begin()->getPointCount(); i++)
            {
                gameObject->GetComponent<Collider>()->hitboxes.begin()->setPoint(i, gameObject->GetComponent<Collider>()->hitboxes.begin()->getPoint(i) + sf::Vector2f(this->gameObject->GetApplication()->GetWindow()->getSize().x + 2 * length, 0));
            }
        }
    }
};


class EnemySpawner : public Script {

public: 
    void execute()
    {
        if (int(this->gameObject->GetApplication()->GetWorkTimeAsSeconds()) / 3 != (int(this->gameObject->GetApplication()->GetWorkTimeAsSeconds() + this->gameObject->GetApplication()->GetLastFrameDurationAsSeconds())) / 3)
        {
            float width;
            float length;
            switch(rand() % 5)
            {
            case 0: case 1:
                    width = 50;
                    length = 100;
                    for (int i = 0; i < 6; i++)
                    {
                        this->gameObject->GetApplication()->GetStorage()->CreateUnit("fast_enemy " + std::string("fast_enemy") + 
                            std::to_string(int(this->gameObject->GetApplication()->GetWorkTimeAsSeconds()) / 3) + std::to_string(i + 1) + 
                            " fast_enemy.png " + std::to_string(this->gameObject->GetApplication()->GetWindow()->getSize().x + (length + 1)* i) + " "  + 
                            std::to_string(rand() % int(this->gameObject->GetApplication()->GetWindow()->getSize().y - 2 * width) + width) + " " + 
                            std::to_string(-150 * (int(this->gameObject->GetApplication()->GetWorkTimeAsSeconds()) / 9 + 1)) +
                            " 0 " + std::to_string(length) + " " + std::to_string(width) + " 1 0 1");
                        this->gameObject->GetApplication()->GetStorage()->GetObject(std::string("fast_enemy") +
                            std::to_string(int(this->gameObject->GetApplication()->GetWorkTimeAsSeconds()) / 3) + std::to_string(i + 1))->AddComponent<ReturnToField>();
                    }
                    break;
            case 2: case 3:
                    width = 20;
                    length = 40;
                    for (int i = 0; i < 6; i++)
                    {
                        this->gameObject->GetApplication()->GetStorage()->CreateUnit("slow_enemy " + std::string("slow_enemy") +
                            std::to_string(int(this->gameObject->GetApplication()->GetWorkTimeAsSeconds()) / 3) + std::to_string(i + 1) +
                            " slow_enemy.png " + std::to_string(this->gameObject->GetApplication()->GetWindow()->getSize().x + (length + 1) * i) + " " +
                            std::to_string(rand() % int(this->gameObject->GetApplication()->GetWindow()->getSize().y - 2 * width) + width) + " " +
                            std::to_string(-100 * (int(this->gameObject->GetApplication()->GetWorkTimeAsSeconds()) / 9 + 1)) +
                            " 0 " + std::to_string(length) + " " + std::to_string(width) + " 1 0 1");
                        this->gameObject->GetApplication()->GetStorage()->GetObject(std::string("slow_enemy") +
                            std::to_string(int(this->gameObject->GetApplication()->GetWorkTimeAsSeconds()) / 3) + std::to_string(i + 1))->AddComponent<ReturnToField>();
                    }
                    break;
                case 4:
                    width = 50;
                    length = 50;
                    for (int i = 0; i < 6; i++)
                    {
                        this->gameObject->GetApplication()->GetStorage()->CreateUnit("shooting_enemy " + std::string("shooting_enemy") +
                            std::to_string(int(this->gameObject->GetApplication()->GetWorkTimeAsSeconds()) / 3) + std::to_string(i + 1) +
                            " shooting_enemy.png " + std::to_string(this->gameObject->GetApplication()->GetWindow()->getSize().x + (length + 1) * i) + " " +
                            std::to_string(rand() % int(this->gameObject->GetApplication()->GetWindow()->getSize().y - 2 * width) + width) + " " +
                            std::to_string(-50 * (int(this->gameObject->GetApplication()->GetWorkTimeAsSeconds()) / 9 + 1)) +
                            " 0 " + std::to_string(length) + " " + std::to_string(width) + " 1 0 1");
                        this->gameObject->GetApplication()->GetStorage()->GetObject(std::string("shooting_enemy") +
                            std::to_string(int(this->gameObject->GetApplication()->GetWorkTimeAsSeconds()) / 3) + std::to_string(i + 1))->AddComponent<ReturnToField>();
                    }
                    break;
            }
        }
    }
};


int main()
{
    Applications App(1600, 900);

    App.GetStorage()->UploadScene("Aliens main scene.txt");

    App.GetStorage()->GetObject("player")->AddComponent<Controller>();
        
    App.GetStorage()->CreateObject("EnemySpawner");
    App.GetStorage()->GetObject("EnemySpawner")->AddComponent<EnemySpawner>();
   
    App.Run();

    return 0;
}