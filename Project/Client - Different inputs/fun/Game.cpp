/// <summary>
/// @author Peter Lowe
/// @date May 2019
///
/// you need to change the above lines or lose marks
/// </summary>

#include "Game.h"
#include <iostream>



/// <summary>
/// default constructor
/// setup the window properties
/// load and setup the text 
/// load and setup thne image
/// </summary>
Game::Game() :
	m_window{ sf::VideoMode{ 800U, 600U, 32U }, "Client" },
	m_exitGame{ false },
	m_client(), 
	m_gameText( {25, 10})
{


	GameInitPacket initPacket = m_client.recieveGameInitialisation();

	// recieving info about the clients and which player we aree
	m_clientPlayer = initPacket.yourPlayer;
	numOfPlayers = initPacket.numOfPlayers;
	

	PlayerInitPacket playerInitPacket;
	// recievinh information about other players
	for (int i = 0; i < initPacket.numOfPlayers; i++)
	{
		
		playerInitPacket = m_client.recievePlayerInitialization();

		m_players.push_back( Player( (Color)playerInitPacket.color, { playerInitPacket.x, playerInitPacket.y }));

		std::cout << "Player " << playerInitPacket.player<< " Color " << playerInitPacket.color << std::endl;
				
	}

	m_gameText.makeText(m_players[initPacket.chaser].m_color + " Player is the chaser", 10);
	

}

/// <summary>
/// default destructor we didn't dynamically allocate anything
/// so we don't need to free it, but mthod needs to be here
/// </summary>
Game::~Game()
{
}


/// <summary>
/// main game loop
/// update 60 times per second,
/// process update as often as possible and at least 60 times per second
/// draw as often as possible but only updates are on time
/// if updates run slow then don't render frames
/// </summary>
void Game::run()
{	
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float fps{ 60.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / fps); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}
		render(); // as many as possible
	}
}
/// <summary>
/// handle user and system events/ input
/// get key presses/ mouse moves etc. from OS
/// and user :: Don't do game update here
/// </summary>
void Game::processEvents()
{
	sf::Event newEvent;
	while (m_window.pollEvent(newEvent))
	{
		if ( sf::Event::Closed == newEvent.type) // window message
		{
			m_exitGame = true;
		}
		if (sf::Event::KeyPressed == newEvent.type) //user pressed a key
		{
			processKeys(newEvent);
		}

	}
}

//
///// <summary>
///// deal with key presses from the user
///// </summary>
///// <param name="t_event">key press event</param>
void Game::processKeys(sf::Event t_event)
{
	if (sf::Keyboard::Escape == t_event.key.code)
	{
		m_exitGame = true;
	}
}

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}
	
	sf::Vector2 direction = m_players[m_clientPlayer].checkForInput(t_deltaTime.asMilliseconds());

	m_client.sendClientInput(m_clientPlayer, direction.x, direction.y);

	updatePlayers();
	m_gameText.update();
}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::Black);
	for (int i = 0; i < m_players.size(); i++)
	{
		if (m_players[i].m_active)
		{
			m_players[i].draw(m_window);
		}
	}
	m_gameText.draw(m_window);
	m_window.display();
}

void Game::updatePlayers()
{
	
	UpdatePacket recievingPacket;

	//// recievinh information about other players
	for (int i = 0; i < numOfPlayers; i++)
	{
		recievingPacket = m_client.recievePlayerUpdate();

		m_players[recievingPacket.player].updateWithPacket(recievingPacket);
		
	}

	CollisionPacket possibleCollision = m_client.recievePossibleCollisionEvent();

	if (possibleCollision.wasCollision)
	{
		m_players[possibleCollision.player].m_active = false;
		std::string str;
		
		if (possibleCollision.gameOver)
		{
			str = "GameOver! " + m_players[possibleCollision.player].m_color + " Player" + " lasted: " + std::to_string(possibleCollision.playerLifeSpan) + " seconds";
		}
		else
		{
			str = m_players[possibleCollision.player].m_color + " Player" + " lasted: " + std::to_string(possibleCollision.playerLifeSpan) + " seconds";
		}
		
		m_gameText.makeText(str, possibleCollision.popUpTTL);
	}

	
}


