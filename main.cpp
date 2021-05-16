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
#include <random>

void collideWithWall(GameObject* obj)
{
    obj->GetComponent<Physics>()->speed.y = -obj->GetComponent<Physics>()->speed.y;
}

class Controller : public Script {

public:
    void execute()
    {
        sf::Vector2f dir;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            dir += sf::Vector2f(0, -1);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            dir += sf::Vector2f(-1, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            dir += sf::Vector2f(0, 1);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            dir += sf::Vector2f(1, 0);
        }
        float speed = 10;
        this->gameObject->GetComponent<Physics>()->pos += speed * dir;
        (this->gameObject->GetComponent<Renderer>()->sprite).move(speed * dir);
        for (int i = 0; i < this->gameObject->GetComponent<Collider>()->hitboxes.begin()->getPointCount(); i++)
        {
            this->gameObject->GetComponent<Collider>()->hitboxes.begin()->setPoint(i, this->gameObject->GetComponent<Collider>()->hitboxes.begin()->getPoint(i) + speed * dir);
        }
    }
};

class RemoveBall : public Script {

public:

    void onCollide()
    {
        (this->gameObject->GetApplication()->GetObjectsForRemove())->insert(this->gameObject->name);
    }
};

class Bullet : public Script {

public:

    void onCollide(GameObject* obj)
    {
        if ((obj->type != "player") and (obj->type != "bullet"))
        {
            (this->gameObject->GetApplication()->GetObjectsForRemove())->insert(this->gameObject->name);
        }
    }
};

class Player : public Script {

public:

    void onCollide(GameObject* obj)
    {
        if (obj->type == "wall")
        {
            collideWithWall(this->gameObject);
        }
        if ((obj->type == "fast_enemy") or (obj->type == "slow_enemy") or (obj->type == "shooting_enemy") or (obj->type == "bullet"))
        {
            this->gameObject->GetApplication()->GetStorage()->UploadScene("endgame.txt");
            std::cout << 0;
        }
        
    }
};

class Enemy : public Script {

public:

    void onCollide(GameObject* obj)
    {
        if (obj->type == "bullet")
        {
            (this->gameObject->GetApplication()->GetObjectsForRemove())->insert(this->gameObject->name);
        }

        if (obj->type == "wall")
        {
            collideWithWall(this->gameObject);
        }

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

class RemoveBullet : public Script {

public:
    void execute()
    {
        if ((this->gameObject->GetComponent<Collider>()->hitboxes.front().getPoint(1).x > this->gameObject->GetApplication()->GetWindow()->getSize().x) or
            ((this->gameObject->GetComponent<Collider>()->hitboxes.front().getPoint(1).x < 0)))
        {
            (this->gameObject->GetApplication()->GetObjectsForRemove())->insert(this->gameObject->name);
        }
    }
};

class BulletSpawner : public Script {

public:
    void execute()
    {
        int bulletpersecond = 5;
        if (int(this->gameObject->GetApplication()->GetWorkTimeAsSeconds() * bulletpersecond) != int((this->gameObject->GetApplication()->GetWorkTimeAsSeconds() - this->gameObject->GetApplication()->GetLastFrameDurationAsSeconds()) * bulletpersecond))
        {
            float width = 10;
            float length = 20;
            if (this->gameObject->name == "player")
            {
                this->gameObject->GetApplication()->GetStorage()->CreateBullet("bullet " + std::string("bullet1_") +
                    std::to_string(int(this->gameObject->GetApplication()->GetWorkTimeAsSeconds() * 1000)) +
                    " bullet.png " + std::to_string(this->gameObject->GetComponent<Physics>()->pos.x + 50) + " " +
                    std::to_string(this->gameObject->GetComponent<Physics>()->pos.y) + " " +
                    std::to_string(602) + " 0 " + std::to_string(length) + " " + std::to_string(width) + " 0");
                this->gameObject->GetApplication()->GetStorage()->GetObject(std::string("bullet1_") +
                    std::to_string(int(this->gameObject->GetApplication()->GetWorkTimeAsSeconds() * 1000)))->AddComponent<Bullet>();
                this->gameObject->GetApplication()->GetStorage()->GetObject(std::string("bullet1_") +
                    std::to_string(int(this->gameObject->GetApplication()->GetWorkTimeAsSeconds() * 1000)))->AddComponent<RemoveBullet>();
            }
            else
            {
                this->gameObject->GetApplication()->GetStorage()->CreateBullet("bullet " + std::string("bullet2_") +
                    std::to_string(int(this->gameObject->GetApplication()->GetWorkTimeAsSeconds() * 1000)) +
                    " bullet.png " + std::to_string(this->gameObject->GetComponent<Physics>()->pos.x - 50) + " " +
                    std::to_string(this->gameObject->GetComponent<Physics>()->pos.y) + " " +
                    std::to_string(-100) + " 0 " + std::to_string(length) + " " + std::to_string(width) + " 0");
                this->gameObject->GetApplication()->GetStorage()->GetObject(std::string("bullet2_") +
                    std::to_string(int(this->gameObject->GetApplication()->GetWorkTimeAsSeconds() * 1000)))->AddComponent<Bullet>();
                this->gameObject->GetApplication()->GetStorage()->GetObject(std::string("bullet2_") +
                    std::to_string(int(this->gameObject->GetApplication()->GetWorkTimeAsSeconds() * 1000)))->AddComponent<RemoveBullet>();
            }
        }
    }
};

class EnemySpawner : public Script {

public: 
    void execute()
    {
        if (int(this->gameObject->GetApplication()->GetWorkTimeAsSeconds()) / 3 != (int(this->gameObject->GetApplication()->GetWorkTimeAsSeconds() - this->gameObject->GetApplication()->GetLastFrameDurationAsSeconds())) / 3)
        {
            float width;
            float length;
            std::random_device rd;
            switch(rd() % 5)
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
                        this->gameObject->GetApplication()->GetStorage()->GetObject(std::string("fast_enemy") +
                            std::to_string(int(this->gameObject->GetApplication()->GetWorkTimeAsSeconds()) / 3) + std::to_string(i + 1))->AddComponent<Enemy>();
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
                        this->gameObject->GetApplication()->GetStorage()->GetObject(std::string("slow_enemy") +
                            std::to_string(int(this->gameObject->GetApplication()->GetWorkTimeAsSeconds()) / 3) + std::to_string(i + 1))->AddComponent<Enemy>();
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
                        this->gameObject->GetApplication()->GetStorage()->GetObject(std::string("shooting_enemy") +
                            std::to_string(int(this->gameObject->GetApplication()->GetWorkTimeAsSeconds()) / 3) + std::to_string(i + 1))->AddComponent<Enemy>();
                        this->gameObject->GetApplication()->GetStorage()->GetObject(std::string("shooting_enemy") +
                            std::to_string(int(this->gameObject->GetApplication()->GetWorkTimeAsSeconds()) / 3) + std::to_string(i + 1))->AddComponent<BulletSpawner>();
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
    App.GetStorage()->GetObject("player")->AddComponent<Player>();
    App.GetStorage()->GetObject("player")->AddComponent<BulletSpawner>();
    App.GetStorage()->GetObject("player")->RemoveComponent<Move>();
    
    App.GetStorage()->CreateObject("EnemySpawner");
    App.GetStorage()->GetObject("EnemySpawner")->AddComponent<EnemySpawner>();
   
    App.Run();

    return 0;
}