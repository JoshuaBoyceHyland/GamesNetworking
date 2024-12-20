#pragma once
#include <SFML/Graphics.hpp>

class Player
{
public:
	Player();

	void checkForInput(float deltaTime);

	void draw(sf::RenderWindow& t_window);

	sf::Vector2f m_position = { 0, 0 };

private:

	float m_rotation = 0;
	float m_speed = 1;
	sf::Vector2f m_velocity;

	sf::RectangleShape m_body;
};

