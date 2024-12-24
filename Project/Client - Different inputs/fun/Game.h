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

#include "Client.h"
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

	void updatePlayers();


	sf::RenderWindow m_window; // main SFML window
	bool m_exitGame; // control exiting game

	Client m_client;

	/// <summary>
	/// Player who is the client
	/// </summary>
	int m_clientPlayer;

	/// <summary>
	/// List of all players
	/// </summary>
	std::vector<Player> m_players;

	/// <summary>
	/// Text for the game
	/// </summary>
	GameText m_gameText;

	/// <summary>
	/// Number of players
	/// </summary>
	int numOfPlayers;
};


#endif // !GAME_HPP

