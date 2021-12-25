/**
\file
\brief .h file of class MenuRender

definition of MenuRender clas
*/

#pragma once

#include <SFML/Graphics.hpp>

#include "Render.h"
#include "Singleton.h"

namespace Docking::Client {

	/**
	\brief render class responsible for menu

	Singleton<MenuRender>, Render inheritant
	*/
	class MenuRender:public Render, public Singleton<MenuRender>
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
		*/
		void Draw() override;
	private:

		/**
		\brief MenuRender constructor

		\param window reference to window of application
		*/
		MenuRender(sf::RenderWindow& window);

		sf::RenderWindow& m_Window;			///<reference to window of application
		sf::RectangleShape m_Rectangle;		///<rectangle for buttons

		sf::Text m_TextPlay;				///<text for play button
		sf::Text m_TextLeaders;				///<text for leaders button
		sf::Text m_TextExit;				///<text for exit button

		friend  Singleton<MenuRender>;
	};
}
