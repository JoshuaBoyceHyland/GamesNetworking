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
	m_body.setPosition({ t_updatePacket.x, t_updatePacket.y });
}

sf::Vector2f Player::checkForInput(float deltaTime)
{

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		m_position.y -= 2.5;
		m_velocity.y = -2.5;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		m_position.y += 2.5;
		m_velocity.y = 2.5;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		m_position.x -= 2.5;
		m_velocity.x = -2.5;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		m_position.x += 2.5;
		m_velocity.x = 2.5;
	}
	m_velocity *= 0.99f;
	//m_body.setPosition(m_position);

	return m_velocity;
}

void Player::draw(sf::RenderWindow& t_window)
{
	t_window.draw(m_body);
}
