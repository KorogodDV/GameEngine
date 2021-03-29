#pragma once

float scalar_prod(sf::Vector2f v_1, sf::Vector2f v_2 )
{
	return v_1.x * v_2.x + v_1.y * v_2.y;
}

sf::Vector2f projection(sf::Vector2f v_1, sf::Vector2f v_2)
{
	return v_1 * scalar_prod(v_1, v_2) / scalar_prod(v_1, v_1);
}

sf::Vector2f ort(sf::Vector2f v)
{
	return sf::Vector2f(-v.y, v.x);
}

sf::Vector2f cord_Pr(sf::ConvexShape Hitbox, sf::Vector2f line,  sf::Vector2f point_0)
{
	float x_min = (projection(line, Hitbox.getPoint(0) - point_0)).x;
	float x_max = (projection(line, Hitbox.getPoint(0) - point_0)).x;

	for (int j = 1; j < Hitbox.getPointCount(); j++)
	{
		if ((projection(line, Hitbox.getPoint(j) - point_0)).x < x_min)
			x_min = (projection(line, Hitbox.getPoint(j) - point_0)).x;

		if ((projection(line, Hitbox.getPoint(j) - point_0)).x > x_max)
			x_max = (projection(line, Hitbox.getPoint(j) - point_0)).x;
	}
	return sf::Vector2f(x_min, x_max);
}

bool checkCollision(sf::ConvexShape Hitbox1, sf::ConvexShape Hitbox2)
{
	for (int i = 0; i < Hitbox1.getPointCount(); i++)
	{
		sf::Vector2f cord_Pr_Hitbox1 = cord_Pr(Hitbox1, ort(Hitbox1.getPoint((i + 1) % Hitbox1.getPointCount()) - Hitbox1.getPoint(i)), Hitbox1.getPoint(i));
		float x_min_Hitbox1 = cord_Pr_Hitbox1.x;
		float x_max_Hitbox1 = cord_Pr_Hitbox1.y;

		sf::Vector2f cord_Pr_Hitbox2 = cord_Pr(Hitbox2, ort(Hitbox1.getPoint((i + 1) % Hitbox1.getPointCount()) - Hitbox1.getPoint(i)), Hitbox1.getPoint(i));
		float x_min_Hitbox2 = cord_Pr_Hitbox2.x;
		float x_max_Hitbox2 = cord_Pr_Hitbox2.y;

		if ((x_max_Hitbox1 < x_min_Hitbox2 ) or (x_max_Hitbox2 < x_min_Hitbox1))
			return false;
	}
	return true;
}

void mymove(sf::ConvexShape* Hitbox, sf::Vector2f speed, float t)
{
	for (int i = 0; i < Hitbox->getPointCount(); i++)
	{
		Hitbox->setPoint(i, Hitbox->getPoint(i) + speed * t);
	}
}

void move(sf::ConvexShape* Hitbox, sf::Vector2f speed,  float t)
{
	Hitbox->move(speed * t);
}

void collide(sf::ConvexShape* Hitbox1, sf::ConvexShape* Hitbox2, sf::Vector2f speed1, sf::Vector2f speed2, float t)
{
	sf::Vector2f Pr_speed1 = projection(speed1 + speed2, speed1);
	sf::Vector2f Pr_speed2 = projection(speed1 + speed2, speed2);

	for (int i = 0; i < 6; i++)
	{
		if (checkCollision(*Hitbox1, *Hitbox2))
		{
			mymove(Hitbox1, -Pr_speed1, t);
			mymove(Hitbox2, -Pr_speed2, t);
		}
		else
		{
			mymove(Hitbox1, Pr_speed1, t);
			mymove(Hitbox2, Pr_speed2, t);
		}
		
		Pr_speed1 = Pr_speed1 / 2.f;
		Pr_speed2 = Pr_speed2 / 2.f;
	}
}

