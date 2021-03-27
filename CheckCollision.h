#pragma once

float scalar(sf::Vector2f v_1, sf::Vector2f v_2 )
{
	return v_1.x * v_2.x + v_1.y * v_2.y;
}

sf::Vector2f cord_Pr1(sf::ConvexShape Hitbox, sf::Vector2f line,  sf::Vector2f point_0)
{
	float x_min = (line * (scalar(line, (Hitbox.getPoint(0) - point_0))) / (scalar(line, line))).x;
	float x_max = (line * (scalar(line, (Hitbox.getPoint(0) - point_0))) / (scalar(line, line))).x;

	for (int j = 1; j < Hitbox.getPointCount(); j++)
	{
		if ((line * (scalar(line, (Hitbox.getPoint(j) - point_0))) / (scalar(line, line))).x < x_min)
			x_min = (line * (scalar(line, (Hitbox.getPoint(j) - point_0))) / (scalar(line, line))).x;

		if ((line * (scalar(line, (Hitbox.getPoint(j) - point_0))) / (scalar(line, line))).x > x_max)
			x_max = (line * (scalar(line, (Hitbox.getPoint(j) - point_0))) / (scalar(line, line))).x;
	}
	return sf::Vector2f(x_min, x_max);
}

bool checkCollision(sf::ConvexShape Hitbox1, sf::ConvexShape Hitbox2)
{
	for (int i = 0; i < Hitbox1.getPointCount(); i++)
	{
		sf::Vector2f cord_Pr_Hitbox1 = cord_Pr1( Hitbox1, sf::Vector2f((Hitbox1.getPoint((i + 1) % Hitbox1.getPointCount()) - Hitbox1.getPoint(i)).y, -(Hitbox1.getPoint((i + 1) % Hitbox1.getPointCount()) - Hitbox1.getPoint(i)).x), Hitbox1.getPoint(i));
		float x_min_Hitbox1 = cord_Pr_Hitbox1.x;
		float x_max_Hitbox1 = cord_Pr_Hitbox1.y;

		sf::Vector2f cord_Pr_Hitbox2 = cord_Pr1(Hitbox2, sf::Vector2f((Hitbox1.getPoint((i + 1) % Hitbox1.getPointCount()) - Hitbox1.getPoint(i)).y, -(Hitbox1.getPoint((i + 1) % Hitbox1.getPointCount()) - Hitbox1.getPoint(i)).x), Hitbox1.getPoint(i));
		float x_min_Hitbox2 = cord_Pr_Hitbox2.x;
		float x_max_Hitbox2 = cord_Pr_Hitbox2.y;

		if ((x_max_Hitbox1 < x_min_Hitbox2 ) or (x_max_Hitbox2 < x_min_Hitbox1))
			return false;
	}
	return true;
}

