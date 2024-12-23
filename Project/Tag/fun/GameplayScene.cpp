#include "GameplayScene.h"

GameplayScene::GameplayScene(sf::RenderWindow& t_window) : Scene(t_window)
{

	
	
}

void GameplayScene::update(sf::Time t_deltaTime)
{

}

void GameplayScene::render()
{
	m_window.clear(sf::Color::Black);/*sf::Color(139, 90, 43, 255)*/


	m_window.display();


}

void GameplayScene::processKeys(sf::Event t_event)
{
	if (sf::Keyboard::Escape == t_event.key.code)
	{
		m_window.close();
	}



}

void GameplayScene::processMousePress(sf::Event t_event)
{


}

void GameplayScene::processMouseRelease(sf::Event t_event)
{
	
}

void GameplayScene::processMouseMove(sf::Event t_event)
{

	
}

void GameplayScene::processMouseWheel(sf::Event t_event)
{

}
