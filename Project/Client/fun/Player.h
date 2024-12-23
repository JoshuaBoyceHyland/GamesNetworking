#pragma once
#include <SFML/Graphics.hpp>
#include "Client.h"

enum class Color { Red = 0, Blue = 1, Green = 2, Yellow = 3 };

class Player
{
	public:
		Player();

		Player(Color t_playerColor, sf::Vector2f t_spawnLocation);

		/// <summary>
		/// Updates the player with the update packet, setting their postion
		/// </summary>
		/// <param name="t_updatePacket"></param>
		void updateWithPacket(UpdatePacket t_updatePacket);

		/// <summary>
		/// checks if player can double speed and resets it after certain amount of time
		/// </summary>
		void checkForSpeedPowerUp();

		/// <summary>
		/// Checks for inputs related to movement
		/// </summary>
		/// <param name="deltaTime"></param>
		/// <returns></returns>
		sf::Vector2f checkForInput(float deltaTime);

		void draw(sf::RenderWindow& t_window);

		/// <summary>
		/// Whether they are alive or not
		/// </summary>
		bool m_active = true;

		/// <summary>
		/// Players color
		/// </summary>
		std::string m_color;


		sf::Vector2f m_position = { 0, 0 };


		sf::CircleShape m_body;
	private:

		// maps for color
		std::map<Color, sf::Color> m_colorMap = { {Color::Red, sf::Color::Red}, {Color::Blue, sf::Color::Blue}, {Color::Green, sf::Color::Green},{Color::Yellow, sf::Color::Yellow} };
		std::map<Color, std::string> m_colorStringMap = { {Color::Red, "Red" }, {Color::Blue, "Blue"}, {Color::Green, "Green"},{Color::Yellow, "Yellow"} };
	
		float m_speed = 2.5;

		sf::Vector2f m_velocity = { 0, 0 };

		float m_powerUpDuration = 1;
		/// <summary>
		/// Power up can only be used once by a non chaser
		/// </summary>
		bool m_powerUpUsed = false;

		bool m_powerUpActive = false;

		/// <summary>
		/// Power Up timer
		/// </summary>
		sf::Clock m_powerUpTimer;
};

