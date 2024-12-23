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

void Player::updateWithPacket(InputPacket t_updatePacket)
{
	m_position.x += t_updatePacket.xDirection;
	m_position.y += t_updatePacket.yDirection;

	m_body.setPosition(m_position);
}

void Player::checkForInput(float deltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		m_position.y -= 2.5;
		m_velocity.y = -2.5;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		m_position.y += 2.5;
		m_velocity.y = 2.5;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		m_position.x -= 2.5;
		m_velocity.x = -2.5;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		m_position.x += 2.5;
		m_velocity.x = 2.5;
	}

	m_velocity *= 0.99f;
	//m_body.setPosition(m_position);
}

void Player::draw(sf::RenderWindow& t_window)
{
	t_window.draw(m_body);
}

void Player::boundsCheck()
{
}
