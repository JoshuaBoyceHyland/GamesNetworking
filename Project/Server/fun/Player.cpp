#include "Player.h"

Player::Player()
{
	m_body.setPosition(m_position);
	m_body.setFillColor(sf::Color::Yellow);
	m_body.setRadius(50);
	m_body.setOrigin({ 25, 25 });
}

Player::Player(Color t_playerColor, sf::Vector2f t_spawnLocation) : m_position( t_spawnLocation)
{
	m_body.setPosition(m_position);
	m_body.setFillColor(m_colorMap[t_playerColor]);
	m_body.setRadius(50);
	m_body.setOrigin({ 25, 25 });
}

void Player::updateWithPacket(UpdatePacket t_updatePacket)
{
	m_body.setPosition({ (float)t_updatePacket.x, (float)t_updatePacket.y });
	m_body.setRotation({ t_updatePacket.rotation });
}

void Player::checkForInput(float deltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		m_speed += 5;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) )
	{
		m_speed -= 5;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) )
	{
		m_rotation -= 2.5;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) )
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

void Player::boundsCheck()
{
}
