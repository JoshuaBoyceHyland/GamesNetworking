#pragma once
#include <SFML/Graphics.hpp>


/// <summary>
/// Interface Class that all scenes that will inherit from
/// </summary>
class Scene
{

	public:
		Scene(sf::RenderWindow& t_window);

		virtual void update(sf::Time t_deltaTime) = 0;

		virtual void render() = 0;

		virtual void processKeys(sf::Event t_event) = 0;

		virtual void processMousePress(sf::Event t_event) = 0;

		virtual void processMouseRelease(sf::Event t_event) = 0;

		virtual void processMouseMove(sf::Event t_event) = 0;

		virtual void processMouseWheel(sf::Event t_event) = 0;
	
	protected:

		/// <summary>
		/// reference of windo we are drawing to
		/// </summary>
		sf::RenderWindow& m_window;

};