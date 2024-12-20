#pragma once
#include <SFML/Graphics.hpp>
#include "Host.h"

enum class Color{ Red = 0, Blue = 1, Green = 2, Yellow = 3};

class Player
{
public:
	Player();
	Player(Color t_playerColor);
	void updateWithPacket(UpdatePacket t_updatePacket);

	void checkForInput(float deltaTime);

	void draw(sf::RenderWindow& t_window);

	float m_rotation = 0;

	sf::Vector2f m_position = { 0, 0 };

	sf::CircleShape m_body;
private:

	
	std::map<Color, sf::Color> m_colorMap = { {Color::Red, sf::Color::Red}, {Color::Blue, sf::Color::Blue}, {Color::Green, sf::Color::Green},{Color::Yellow, sf::Color::Yellow} };
	float m_speed = 1;
	sf::Vector2f m_velocity;
	
};

