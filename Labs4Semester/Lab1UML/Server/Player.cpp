/**
\file
\brief .cpp file of class Player

implementation of Player class
*/

#include "Player.h"

namespace Docking::Server {
    Player::Player(int id, sf::TcpSocket& socket) :
        m_Id(id),
        m_Socket(socket),
        m_Game(-1),
		m_Wins(0){}

    int Player::GetId() const {
        return m_Id;
    }
    int Player::GetGame() const {
        return m_Game;
    }
    void Player::SetGame(int value) {
        m_Game = value;
    }

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