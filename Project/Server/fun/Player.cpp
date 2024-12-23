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
}

void Player::updateWithPacket(InputPacket t_updatePacket)
{
	m_position.x += t_updatePacket.xDirection;
	m_position.y += t_updatePacket.yDirection;
	boundsCheck();

	m_body.setPosition(m_position);
}

void Player::checkForInput(float deltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		m_velocity.y = -2.5;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		m_velocity.y = 2.5;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		m_velocity.x = -2.5;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		m_velocity.x = 2.5;
	}

	m_velocity *= 0.99f;
}

void Player::draw(sf::RenderWindow& t_window)
{
	t_window.draw(m_body);
}

void Player::boundsCheck()
{

	if (m_position.x > Globals::SCREEN_WIDTH - m_body.getRadius())
	{
		m_position.x = 0;
	}
	else if (m_position.x < -m_body.getRadius())
	{
		m_position.x = Globals::SCREEN_WIDTH - m_body.getRadius();
	}

	if (m_position.y > Globals::SCREEN_HEIGHT - m_body.getRadius())
	{
		m_position.y = 0;
	}
	else if (m_position.y < -m_body.getRadius())
	{
		m_position.y = Globals::SCREEN_HEIGHT - m_body.getRadius();
	}
}

