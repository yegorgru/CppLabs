/**
\file
\brief .h file of class Player

definition of Player clas
*/

#pragma once

#include <string>

namespace Docking::Client {

	/**
	\brief class for storing information about player
	*/
	class Player
	{
	public:
		/**
		\brief Player default constructor

		wins will be 0, name will be empty
		*/
		Player();

		/**
		\brief Player constructor

		\param name const reference to name, m_Name will be equal to it
		\param wins number, m_Wins will be equal to it
		*/
		Player(const std::string& name, int wins);

		/**
		\brief m_Name getter

		\return string equal to m_Name
		*/
		std::string GetName() const;

		/**
		\brief m_Name setter

		\param name, m_Name will be equal to it
		*/
		void SetName(const std::string& name);

		/**
		\brief m_Wins setter

		\param wins, m_Wins will be equal to it
		*/
		void SetWins(int wins);

		/**
		\brief m_Wins getter

		\return string equal to m_Wins
		*/
		int GetWins() const;
	private:
		std::string m_Name;	///<name of player
		int m_Wins;			///<wins of player
	};
}

