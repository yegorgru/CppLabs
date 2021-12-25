/**
\file
\brief .h file of class LeadersRender

definition of LeadersRender clas
*/

#pragma once

#include <SFML/Graphics.hpp>

#include <string>

#include "Player.h"
#include "Render.h"
#include "Singleton.h"

namespace Docking::Client {

	/**
	\brief render class responsible for leaders board

	Singleton<LeadersRender>, Render inheritant
	*/
	class LeadersRender : public Render, public Singleton<LeadersRender>
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

		/**
		\brief restores all attributes
		*/
		void Restore();

		/**
		\brief adds letter to name of player

		size of text can't be bigger than 10 letters
		\param letter added letter
		*/
		void AddLetter(char letter);

		/**
		\brief erases letter from name of player
		*/
		void EraseLetter();

		/**
		\brief m_TextName text getter

		\return copy to m_TextName text
		*/
		std::string GetName() const;

		/**
		\brief called when player want to find non-existent player

		clears m_TextName and draw borders of m_RectangleName in red
		*/
		void IncorrectName();

		/**
		\brief sets current player

		\param player reference to Player to set
		*/
		void SetPlayer(const Player& player);

		/**
		\brief adds leader to leaders board

		\param player reference to add
		*/
		void AddLeader(const Player& player);
	private:

		/**
		\brief LeadersRender constructor

		\param window reference to window of application
		*/
		LeadersRender(sf::RenderWindow& window);

		sf::RenderWindow& m_Window;			///<reference to window of application
		sf::RectangleShape m_RectangleName;	///<rectangle of input name
		sf::RectangleShape m_RectangleFind;	///<rectangle of find button

		sf::Text m_TextName;				///<text of player's name
		sf::Text m_TextFind;				///<text of find button
		sf::Text m_TextWins;				///<text "Wins"
		sf::Text m_TextWinsNumber;			///<text of player's name
		sf::Text m_TextLeaders;				///<text of leaders board

		Player m_Player;					///<current player

		friend class Singleton<LeadersRender>;
	};
}

