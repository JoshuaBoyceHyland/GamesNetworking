#include "Player.h"

Player::Player()
{
	m_body.setPosition(m_position);
	m_body.setFillColor(sf::Color::Yellow);
	m_body.setSize({50, 50});
}

void Player::checkForInput(float deltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		m_speed += 5;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		m_speed -= 5;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		m_rotation -= 2.5;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		m_rotation += 2.5;
	}

	float radian = (m_rotation /*+ 270.0f*/) * (3.14159265359f / 180.0f);
	m_velocity.x = std::cos(radian) * m_speed * (deltaTime / 1000);
	m_velocity.y = std::sin(radian) * m_speed * (deltaTime / 1000);

	m_position += m_velocity;
	m_body.setPosition(m_position);
	m_body.setRotation(m_rotation);
	
	m_speed *= 0.99f;
}

void Player::draw(sf::RenderWindow& t_window)
{
	t_window.draw(m_body);
}
