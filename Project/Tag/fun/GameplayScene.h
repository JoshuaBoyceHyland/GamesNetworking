#pragma once
#include "Scene.h"


/// <summary>
/// scene where game is played
/// </summary>
class GameplayScene : public Scene
{
	public:
		GameplayScene( sf::RenderWindow& t_window);

		/// <summary>
		/// Updates the Gameplay scene
		/// </summary>
		/// <param name="t_deltaTime">Time between last frame</param>
		void update(sf::Time t_deltaTime) override;

		/// <summary>
		/// Renders the gameplaye Scene
		/// </summary>
		void render() override;

		/// <summary>
		/// Processes the key press event for gameplay scene
		/// </summary>
		/// <param name="t_event">Key press event</param>
		void processKeys(sf::Event t_event) override;

		/// <summary>
		/// Processes the mouse press event for gameplay scene
		/// </summary>
		/// <param name="t_event">Mouse press event</param>
		void processMousePress(sf::Event t_event) override;

		/// <summary>
		/// Processes the mouse release event for gameplay scene
		/// </summary>
		/// <param name="t_event">Mouse release event</param>
		void processMouseRelease(sf::Event t_event) override;

		/// <summary>
		/// Processes the mouse move event for gameplay scene
		/// </summary>
		/// <param name="t_event">Mouse pmove event</param>
		void processMouseMove(sf::Event t_event) override;

		/// <summary>
		/// Processes the mouse move wheel move event for gameplay scene
		/// </summary>
		/// <param name="t_event">Mouse wheel move event</param>
		void processMouseWheel(sf::Event t_event) override;
	private:

		
};

