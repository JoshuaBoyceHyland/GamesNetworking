#include "GameText.h"

GameText::GameText(sf::Vector2f t_position)
{

	if (!m_font.loadFromFile("ASSETS/FONTS/font.ttf"))
	{
		std::cout << "couldnt load font" << std::endl;
	}
	m_text.setPosition(t_position);
	m_text.setFont(m_font);
	m_text.setCharacterSize(25);
	m_text.setFillColor(sf::Color::White);
	
}

void GameText::update()
{

	if (m_active)
	{
		if (m_timer.getElapsedTime().asSeconds() > m_timeToLive)
		{
			m_active = false;
		}
	}

}

void GameText::makeText(std::string t_string, float t_timeToLive)
{
	m_timer.restart();
	m_text.setString(t_string);
	m_active = true;
	m_timeToLive = t_timeToLive;
}

void GameText::draw(sf::RenderWindow& t_window)
{
	if (m_active)
	{
		t_window.draw(m_text);
	}
}
