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
#include "Globals.h"


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

	/// <summary>
	/// Sets up game with players
	/// </summary>
	void findPlayers();

	/// <summary>
	/// gathers player data to be sent to clietns
	/// </summary>
	/// <returns>List of packets to be sent out</returns>
	std::vector<UpdatePacket> createUpdatePacketsForClients();

	/// <summary>
	/// Checks data for collision, sends out packet to say whether there was or wasnt a collision
	/// </summary>
	/// <param name="t_updatePackets"></param>
	void checkForCollision(std::vector<UpdatePacket> t_updatePackets);
	

	sf::RenderWindow m_window; // main SFML window
	bool m_exitGame; // control exiting game

	/// <summary>
	/// Host networking
	/// </summary>
	Host m_host;

	/// <summary>
	/// Players caught so far
	/// </summary>
	int m_playersCaught = 0;

	/// <summary>
	/// Number of players in game
	/// </summary>
	int m_numOfPlayers = 3;

	/// <summary>
	/// Player who is the chaser
	/// </summary>
	int m_chaser;

	/// <summary>
	/// The player who is the host
	/// </summary>
	int m_hostPlayer = 0;

	/// <summary>
	/// List of all players
	/// </summary>
	std::vector<Player> m_players;

	/// <summary>
	/// Spawn locations
	/// </summary>
	std::vector<sf::Vector2f> m_spawnLocations = { {0, 0}, {700, 500}, { 700, 0} };

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

