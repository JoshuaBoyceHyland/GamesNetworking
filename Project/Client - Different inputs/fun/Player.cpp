#include "Player.h"

Player::Player()
{
	m_body.setPosition(m_position);
	m_body.setFillColor(sf::Color::Yellow);
	m_body.setRadius(50);
	m_body.setOrigin({ 25, 25 });
	m_color = m_colorStringMap[Color::Yellow];
}

Player::Player(Color t_playerColor, sf::Vector2f t_spawnLocation) : m_position( t_spawnLocation)
{
	m_body.setPosition(m_position);
	m_body.setFillColor(m_colorMap[t_playerColor]);
	m_body.setRadius(50);
	m_body.setOrigin({ 25, 25 });
	m_color = m_colorStringMap[t_playerColor];

	m_powerUpTimer.restart();
}

void Player::updateWithPacket(UpdatePacket t_updatePacket)
{
	m_body.setPosition({ t_updatePacket.x, t_updatePacket.y });
}

void Player::checkForSpeedPowerUp()
{

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::O))
	{
		if (!m_powerUpUsed)
		{
			m_speed *= 2;
			m_powerUpActive = true;
			m_powerUpUsed = true;
			m_powerUpTimer.restart();
		}
	}

	if (m_powerUpTimer.getElapsedTime().asSeconds() > m_powerUpDuration &&  m_powerUpActive)
	{ 
		m_speed /= 2;
		m_powerUpActive = false;
	}
}

sf::Vector2f Player::checkForInput(float deltaTime)
{
	
	checkForSpeedPowerUp();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::I))
	{
		m_velocity.y = -m_speed;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::K))
	{
		m_velocity.y = m_speed;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::J))
	{
		m_velocity.x = -m_speed;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
	{
		m_velocity.x = m_speed;
	}

	m_velocity *= 0.99f;

	return m_velocity;
}

void Player::draw(sf::RenderWindow& t_window)
{
	t_window.draw(m_body);
}
