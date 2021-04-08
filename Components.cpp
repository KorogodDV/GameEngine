#pragma once
#include <iostream>
#include <list>
#include <SFML/Graphics.hpp>
#include "Components.h"
#include "GameObject.h"
#include "Application.h"

void Move::execute()
{
    gameObject->GetComponent<Physics>()->speed += gameObject->GetComponent<Physics>()->acceleration * gameObject->GetApplication()->GetLastFrameDurationAsSeconds();
    gameObject->GetComponent<Physics>()->pos += gameObject->GetComponent<Physics>()->speed * gameObject->GetApplication()->GetLastFrameDurationAsSeconds();
    (gameObject->GetComponent<Renderer>()->sprite).move(gameObject->GetApplication()->GetLastFrameDurationAsSeconds() * gameObject->GetComponent<Physics>()->speed);
    for (int i = 0; i < gameObject->GetComponent<Collider>()->hitboxes.begin()->getPointCount(); i++)
    {
        gameObject->GetComponent<Collider>()->hitboxes.begin()->setPoint(i, gameObject->GetComponent<Collider>()->hitboxes.begin()->getPoint(i) + gameObject->GetComponent<Physics>()->speed * gameObject->GetApplication()->GetLastFrameDurationAsSeconds());
    }
}