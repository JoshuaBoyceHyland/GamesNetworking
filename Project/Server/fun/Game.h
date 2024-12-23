/// <summary>
/// author Pete Lowe May 2019
/// you need to change the above line or lose marks
/// </summary>
#ifndef GAME_HPP
#define GAME_HPP
/// <summary>
/// include guards used so we don't process this file twice
/// same as #pragma once
/// Don't forget the endif at the bottom
/// </summary>
#include <SFML/Graphics.hpp>

#include "Host.h"
#include "Player.h"
#include "GameText.h"

class Game
{
public:
	Game();
	~Game();
	/// <summary>
	/// main method for game
	/// </summary>
	void run();

private:

	void processEvents();
	void processKeys(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();

	std::vector<UpdatePacket> createUpdatePacketsForClients();
	std::vector<UpdatePacket> checkForCollision(std::vector<UpdatePacket> t_updatePackets);
	

	sf::RenderWindow m_window; // main SFML window
	bool m_exitGame; // control exiting game

	Host m_host;

	int currentPlayer = 0;
	std::vector<Player> m_players;

	std::vector<sf::Vector2f> m_spawnLocations = { {0, 0}, {700, 500}, { 400, 400} };

	/// <summary>
	/// Keep track of total time the game has been going on
	/// </summary>
	sf::Clock m_timer;

	/// <summary>
	/// Text for game
	/// </summary>
	GameText m_text;
};


#endif // !GAME_HPP

