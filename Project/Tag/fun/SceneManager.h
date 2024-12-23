#pragma once
//#include "MenuScene.h"
#include "GameplayScene.h"

/// <summary>
/// Scenes we can switch to
/// </summary>
enum SceneType{ Menu, Gameplay };

/// <summary>
/// Scene manager which manages which scene we are in and switched to new ones
/// </summary>
class SceneManager
{
	public:
		/// <summary>
		/// Scenemanager constuctor
		/// </summary>
		/// <param name="t_window">Window we are drawing to</param>
		SceneManager(sf::RenderWindow& t_window);

		/// <summary>
		/// Switch between scenes using enum
		/// </summary>
		/// <param name="t_newScene">Next scen</param>
		void switchScene(SceneType t_newScene);

		/// <summary>
		/// Scene we are currently int and want to update
		/// </summary>
		/// <returns></returns>
		Scene* getCurrentScene();

	private:

		/// <summary>
		/// Current scene
		/// </summary>
		Scene* m_currentScene = nullptr;

		/// <summary>
		/// reference of window we are drawing to
		/// </summary>
		sf::RenderWindow& m_window;
};

