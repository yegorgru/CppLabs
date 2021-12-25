/**
\file
\brief .cpp file of class Player

implementation of Player class
*/

#include "Player.h"


namespace Docking::Client {
	Player::Player():
		m_Wins(0),m_Name("") {}

	Player::Player(const std::string& name, int wins):
		m_Name(name),
		m_Wins(wins) {}

	std::string Player::GetName() const
	{
		return m_Name;
	}

	void Player::SetName(const std::string& name)
	{
		m_Name = name;
	}

	void Player::SetWins(int wins)
	{
		m_Wins = wins;
	}

	int Player::GetWins() const
	{
		return m_Wins;
	}
}