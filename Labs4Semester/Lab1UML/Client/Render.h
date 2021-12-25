/**
\file
\brief .h file of class Render
*/

#pragma once

#include <SFML/Graphics.hpp>

namespace Docking::Client {

	/**
	\brief Render abstact class, parent of all renders
	*/
	class Render {
	public:
		/**
		\brief pure virtual method for drawing elements on window
		*/
		virtual void Draw()=0;

		/**
		\brief pure virtual method, getter of window
		*/
		virtual sf::RenderWindow& Window()=0;
	};
}