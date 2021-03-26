#pragma once
class Line
{
public:
	float a;
	float b;
	float c;

	Line(float a, float b, float c)
	{
		this->a = a;
		this->b = b;
		this->c = c;
	}

	Line(sf::Vector2f A, sf::Vector2f B)
	{
		if (A.y == B.y)
		{
			this->a = 0;
			this->b = 1;
			this->c = -A.y;
		}
		else
		{
			this->a = 1;
			this->b = (B.x - A.x)/(A.y - B.y);
			this->c = -A.x - b * A.y;
		}
	}

	Line perpendicular(sf::Vector2f A)
	{
		return Line(-b, a, b * A.x - a * A.y);
	}

	sf::Vector2f crossing_with_perpendicular(Line line)
	{
		float x;
		float y;

		if (a == 0)
		{
			y = -c / b;
			x = -line.c / line.a;
		}
		else if (b == 0)
		{
			x = -c / a;
			y = -line.c / line.b;
		}
		else
		{
			y = (line.a * c / a - line.c) / (line.b - line.a * b / a);
			x = -c / a - b * y / a;
		}

		return sf::Vector2f(x, y);
	}
};

sf::Vector2f coordinates_projection(sf::ConvexShape Hitbox, Line line)
{
	sf::Vector2f B = Hitbox.getPoint(0);
	Line perpendicular = line.perpendicular(B);
	sf::Vector2f O = line.crossing_with_perpendicular(perpendicular);

	float x_min = O.x;
	float x_max = O.x;

	for (int j = 1; j < Hitbox.getPointCount(); j++)
	{
		sf::Vector2f B = Hitbox.getPoint(j);
		Line perpendicular = line.perpendicular(B);
		sf::Vector2f O = line.crossing_with_perpendicular(perpendicular);

		if (O.x < x_min)
			x_min = O.x;

		if (O.x > x_max)
			x_max = O.x;
	}
	return sf::Vector2f(x_min, x_max);
}

bool checkCollision(sf::ConvexShape Hitbox1, sf::ConvexShape Hitbox2)
{
	bool result = true;
	
	for (int i = 0; i < Hitbox1.getPointCount(); i++)
	{
		sf::Vector2f A = Hitbox1.getPoint(i);
		
		Line side_Shape(A, Hitbox1.getPoint((i + 1) % Hitbox1.getPointCount()));
		Line line = side_Shape.perpendicular(A);

		sf::Vector2f coordinates_projection_Hitbox1 = coordinates_projection( Hitbox1, line);
		float x_min_Hitbox1 = coordinates_projection_Hitbox1.x;
		float x_max_Hitbox1 = coordinates_projection_Hitbox1.y;

		sf::Vector2f coordinates_projection_Hitbox2 = coordinates_projection( Hitbox2, line);
		float x_min_Hitbox2 = coordinates_projection_Hitbox2.x;
		float x_max_Hitbox2 = coordinates_projection_Hitbox2.y;

		if ((x_max_Hitbox1 < x_min_Hitbox2 ) or (x_max_Hitbox2 < x_min_Hitbox1))
			result = false;
	}

	return result;
}

