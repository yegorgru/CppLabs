/**
\file
\brief .h file of class Assets

definition of Assets class
*/

#pragma once

#include <SFML/Graphics.hpp>
#include "Singleton.h"

namespace Docking::Client {

	/**
	\brief class for storing assets

	Singleton<Assets> inheritant
	has information about font
	*/
	class Assets : public Singleton<Assets>
	{
	public:
		/**
		\brief font getter

		\return reference to m_Font
		*/
		sf::Font& GetFont();

	private:
		/**
		\brief loads font from .ttf file

		\throw exception if failed to load font
		*/
		Assets();
		
		sf::Font m_Font;	///<font

		friend class Singleton<Assets>;
	};
}

