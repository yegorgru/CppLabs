/**
\file
\brief .h file of class GameRender

definition of GameRender clas
*/


#pragma once

#include <SFML/Graphics.hpp>

#include "GameModel.h"
#include "Render.h"
#include "Singleton.h"

namespace Docking::Client {

	/**
	\brief render class responsible for game

	Singleton<GameRender>, Render inheritant
	*/
	class GameRender:public Render, public Singleton<GameRender>
	{
	public:
		/**
		\brief m_Window getter

		override Render method
		\return m_Window, application window
		*/
		sf::RenderWindow& Window() override;

		/**
		\brief draw elements on m_Window

		override Render method
		3 variants: waiting for opponent, somebody won or game proccess
		*/
		void Draw() override;

		/**
		\brief m_ElementSize getter

		\return m_ElementSize
		*/
		int GetElementSize();

		/**
		\brief set text when some player wins

		\param text string to set
		*/
		void SetEndText(const std::string& text);

		/**
		\brief restores all attributes for waiting variant
		*/
		void Restore();
	private:
		/**
		\brief GameRender constructor
		 
		call Restore method
		\param window reference to window of application
		*/
		GameRender(sf::RenderWindow& window);

		GameModel& m_GameModel;			///<logic model of game

		sf::RenderWindow& m_Window;		///<reference to window of application

		sf::RectangleShape m_Square;	///<square responsible for player's blocks

		sf::Text m_TextPlayers;			///<text in the top of window, names and wins of players

		sf::Text m_TextEnd;				///<text in the end of game, when somebody wins
		sf::Text m_TextWaiting;			///<text in the beginning of game, when player is waiting for opponent
		int m_ElementSize;				///<size of m_Square

		friend class Singleton<GameRender>;
	};
}
