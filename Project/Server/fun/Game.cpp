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
	m_window{ sf::VideoMode{ 800U, 600U, 32U }, "Host" },
	m_exitGame{false}, 
	m_text({100, 100})
{

	std::vector<PlayerInitPacket> outGoingPackets;

	// player 1 which is the host

	Color color = Color::Red;
	m_players.push_back(Player(color, m_spawnLocations[0]));
	outGoingPackets.push_back({ 0, 0 });


	listen(m_host.m_socket, SOMAXCONN);
	
	// rest of players which are clients
	for (int i = 1; i < 3; i++)
	{
		color = Color(i);
		m_host.listenForClient();
		m_players.push_back(Player(color, m_spawnLocations[i]));
		m_host.initializeClient(i - 1, { i, 3 });
		outGoingPackets.push_back({ i , i, m_spawnLocations[i].x, m_spawnLocations[i].y});
		
	}


	m_host.initializeClientColor(outGoingPackets);
	

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
	m_text.update();
	m_players[0].checkForInput(t_deltaTime.asMilliseconds());

	
	std::vector<InputPacket> inputPackets = m_host.recieveClientData();

	inputPackets.push_back({ 0, m_players[0].m_velocity.x, m_players[0].m_velocity.y });
	
	for (int i = 0; i < inputPackets.size(); i++)
	{
		m_players[inputPackets[i].player].updateWithPacket(inputPackets[i]);
	}

	
	std::vector<UpdatePacket> updatePackets = createUpdatePacketsForClients();

	

	m_host.updateClients(updatePackets);
	checkForCollision(updatePackets);
	
}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::Black);
	for (int i = 0; i <m_players.size(); i++)
	{
		if (m_players[i].m_alive)
		{
			m_players[i].draw(m_window);
		}
		
	}
	m_text.draw(m_window);
	m_window.display();
}

std::vector<UpdatePacket> Game::createUpdatePacketsForClients()
{
	UpdatePacket current;
	std::vector<UpdatePacket> updatePackets;
	for (int i = 0; i < m_players.size(); i++)
	{
		current.player = i;
		current.x = m_players[i].m_position.x;
		current.y = m_players[i].m_position.y;

		updatePackets.push_back(current);
	}
	return updatePackets;
}

void Game::checkForCollision(std::vector<UpdatePacket> t_updatePackets)
{
	CollisionPacket possibleCollision;
	for (int i = 0; i < m_players.size(); i++)
	{

		if (currentPlayer != i)
		{
			if (m_players[i].m_alive)
			{
				if (m_players[currentPlayer].m_body.getGlobalBounds().intersects(m_players[i].m_body.getGlobalBounds()))
				{
					
					m_players[i].m_alive = false;
					int timeLived = m_timer.getElapsedTime().asSeconds();
					std::string str = "Player: " + std::to_string(i) + " lasted: " + std::to_string(timeLived) + " seconds";
					float TTL = 5;
					m_text.makeText(str, 5);


					possibleCollision.player = i;
					possibleCollision.playerLifeSpan = timeLived;
					possibleCollision.popUpTTL = TTL;
					possibleCollision.wasCollision = true;
				

				}
			}
			
		}

	}

	
	
	m_host.notifyClientsOfCollision(possibleCollision);
}


