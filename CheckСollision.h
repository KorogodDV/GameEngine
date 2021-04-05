#pragma once

float scalar_prod(sf::Vector2f v_1, sf::Vector2f v_2 )
{
	return v_1.x * v_2.x + v_1.y * v_2.y;
}

float projection(sf::Vector2f v_1, sf::Vector2f v_2)
{
	return scalar_prod(v_1, v_2) / sqrt(scalar_prod(v_1, v_1));
}

sf::Vector2f projection_v(sf::Vector2f v_1, sf::Vector2f v_2)
{
	return v_1 * scalar_prod(v_1, v_2) / scalar_prod(v_1, v_1);
}

sf::Vector2f ort(sf::Vector2f v)
{
	return sf::Vector2f(-v.y, v.x);
}

sf::Vector2f cord_Pr(sf::ConvexShape Hitbox, sf::Vector2f line,  sf::Vector2f point_0)
{
	float min = (projection(line, Hitbox.getPoint(0) - point_0));
	float max = (projection(line, Hitbox.getPoint(0) - point_0));

	for (int j = 1; j < Hitbox.getPointCount(); j++)
	{
		if (projection(line, Hitbox.getPoint(j) - point_0) < min)
			min = projection(line, Hitbox.getPoint(j) - point_0);

		if (projection(line, Hitbox.getPoint(j) - point_0) > max)
			max = projection(line, Hitbox.getPoint(j) - point_0);
	}
	return sf::Vector2f(min, max);
}

bool checkCollision(sf::ConvexShape Hitbox1, sf::ConvexShape Hitbox2)
{
	for (int i = 0; i < Hitbox1.getPointCount(); i++)
	{
		sf::Vector2f cord_Pr_Hitbox1 = cord_Pr(Hitbox1, ort(Hitbox1.getPoint((i + 1) % Hitbox1.getPointCount()) - Hitbox1.getPoint(i)), Hitbox1.getPoint(i));
		float min_Hitbox1 = cord_Pr_Hitbox1.x;
		float max_Hitbox1 = cord_Pr_Hitbox1.y;

		sf::Vector2f cord_Pr_Hitbox2 = cord_Pr(Hitbox2, ort(Hitbox1.getPoint((i + 1) % Hitbox1.getPointCount()) - Hitbox1.getPoint(i)), Hitbox1.getPoint(i));
		float min_Hitbox2 = cord_Pr_Hitbox2.x;
		float max_Hitbox2 = cord_Pr_Hitbox2.y;

		if ((max_Hitbox1 < min_Hitbox2 ) or (max_Hitbox2 < min_Hitbox1))
			return false;
	}
	for (int i = 0; i < Hitbox2.getPointCount(); i++)
	{
		sf::Vector2f cord_Pr_Hitbox1 = cord_Pr(Hitbox1, ort(Hitbox2.getPoint((i + 1) % Hitbox2.getPointCount()) - Hitbox2.getPoint(i)), Hitbox2.getPoint(i));
		float min_Hitbox1 = cord_Pr_Hitbox1.x;
		float max_Hitbox1 = cord_Pr_Hitbox1.y;
		//std::cout << x_min_Hitbox1  << std::endl;
		//std::cout << x_max_Hitbox1 << std::endl;

		sf::Vector2f cord_Pr_Hitbox2 = cord_Pr(Hitbox2, ort(Hitbox2.getPoint((i + 1) % Hitbox2.getPointCount()) - Hitbox2.getPoint(i)), Hitbox2.getPoint(i));
		float min_Hitbox2 = cord_Pr_Hitbox2.x;
		float max_Hitbox2 = cord_Pr_Hitbox2.y;
		//std::cout << x_min_Hitbox2 << std::endl;
		//std::cout << x_max_Hitbox2 << std::endl;

		if ((max_Hitbox1 < min_Hitbox2) or (max_Hitbox2 < min_Hitbox1))
			return false;
	}
	return true;
}

void mymove(sf::ConvexShape* Hitbox, sf::Vector2f speed, float t)
{
	//std::cout << 1 << std::endl;
	for (int i = 0; i < Hitbox->getPointCount(); i++)
	{
		Hitbox->setPoint(i, Hitbox->getPoint(i) + speed * t);
		//std::cout << Hitbox->getPoint(i).x << Hitbox->getPoint(i).y << std::endl;
	}
}

void collide(sf::ConvexShape* Hitbox1, sf::ConvexShape* Hitbox2, sf::Vector2f speed1, sf::Vector2f speed2, float t)
{
	std::cout << 2 << std::endl;
	sf::Vector2f Pr_speed1;
	sf::Vector2f Pr_speed2;
	if (speed1 + speed2 == sf::Vector2f(0, 0))
	{
		Pr_speed1 = speed1;
		Pr_speed2 = projection_v(speed1, speed2);
	}
	else
	{
		Pr_speed1 = projection_v(speed1 + speed2, speed1);
		Pr_speed2 = projection_v(speed1 + speed2, speed2);
	}

	for (int i = 0; i < 6; i++)
	{
		Pr_speed1 = Pr_speed1 / 2.f;
		Pr_speed2 = Pr_speed2 / 2.f;

		if (checkCollision(*Hitbox1, *Hitbox2))
		{
			mymove(Hitbox1, -Pr_speed1, t);
			mymove(Hitbox2, -Pr_speed2, t);
			//std::cout << (-Pr_speed1 * t).x << ' ' << (-Pr_speed1 * t).y << std::endl;
			//std::cout << (-Pr_speed2 * t).x << ' ' << (-Pr_speed2 * t).y << std::endl;
		}
		else
		{
			mymove(Hitbox1, Pr_speed1, t);
			mymove(Hitbox2, Pr_speed2, t);
			//std::cout << (Pr_speed1 * t).x << ' ' << (Pr_speed1 * t).y << std::endl;
			//std::cout << (Pr_speed2 * t).x << ' ' << (Pr_speed2 * t).y << std::endl;
		}
	
	}
}

