/**
\file
\brief .cpp file of class GameModel

implementation of GameModel class
*/

#include "GameModel.h"

namespace Docking::Client {
	GameModel::GameModel():
		m_Map(),
		m_Winner(0) {}

	void GameModel::Restore()
	{
		for (size_t i = 0; i < 8; i++) {
			for (size_t j = 0; j < 8; j++)
			{
				if ((i == 0 || i == 7) && j > 1 && j < 6) {
					m_Map[i][j] = 1;
				}
				else if ((j == 0 || j == 7) && i > 1 && i < 6) {
					m_Map[i][j] = 2;
				}
				else {
					m_Map[i][j] = 0;
				}
			}
		}
		m_Winner = 0;
	}

	void GameModel::SetElement(int element, Position newPos, Position oldPos) {
		if (!(oldPos == Position{-1, -1})) {
			m_Map[oldPos.x][oldPos.y] = 0;
		}
		m_Map[newPos.x][newPos.y] = element;
	}

	void GameModel::SetWinner(int winner){
		m_Winner = winner;
	}

	int GameModel::GetElement(Position pos) {
		return m_Map[pos.x][pos.y];
	}

	int GameModel::GetWinner() {
		return m_Winner;
	}

	void GameModel::AddPlayer(const Player& player) {
		m_Players.push_back(player);
	}

	std::vector<Player>& GameModel::GetPlayers()
	{
		return m_Players;
	}

	bool operator==(const GameModel::Position& left, const GameModel::Position& right) {
		return left.x == right.x && left.y == right.y;
	}
}