/**
\file
\brief .h file of class ClientController

definition of ClientController clas
*/

#pragma once

#include "GameRender.h"
#include "GameModel.h"
#include "GameController.h"
#include "MenuController.h"
#include "Player.h"
#include "Singleton.h"

namespace Docking::Client {

	/**
	\brief main controller class on client side

	launch other controllers
	Singleton<ClientController> inheritant
	*/
	class ClientController : public Singleton<ClientController>
	{		
	public:
		/**
		\brief run application method

		launch Run() methods of other controllers
		*/
		void Run();
	private:
		/**
		\brief ClientController constructor

		\param window reference to window of application
		*/
		ClientController(sf::RenderWindow& window);

		Player m_Player;			///<information about player who launch application
		sf::RenderWindow& m_Window;	///<window of application

		friend class Singleton<ClientController>;
	};
}
