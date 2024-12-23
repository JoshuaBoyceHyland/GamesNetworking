#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class GameText
{

	public:
		GameText(sf::Vector2f t_position);

		void update();

		void makeText(std::string t_string, float t_timeToLive);

		void disableText();

		void draw(sf::RenderWindow& t_window);

	private:

		bool m_active = false;
		float m_timeToLive;
		std::string m_string;
		sf::Text m_text;
		sf::Font m_font;
		sf::Clock m_timer;

};

