/**
\file
\brief .h file of class GameModel

definition of GameModel class
*/

#pragma once

#include <set>
#include <utility>
#include <array>
#include <vector>

#include "Player.h"
#include "Singleton.h"

namespace Docking::Client {

	/**
	\brief class responsible for logic of game

	Singleton<GameModel> inheritant
	*/
	class GameModel : public Singleton<GameModel>
	{
	public:
		/**
		\brief represents positions on map

		correct positions is from 0 to 7 (both x & y)
		*/
		struct Position {
			int x;
			int y;
		};

		/**
		\brief run Restores information about game

		restores m_Map and m_Winner
		*/
		void Restore();

		/**
		\brief run Set element on certain position

		\param element 0-nothing, 1 - first player, 2 - second player
		\param newPos position to set element
		\param oldPos optional parameter, element on that position will be 0
		*/
		void SetElement(int element, Position newPos, Position oldPos = {-1,-1});

		/**
		\brief setter of m_Winner

		\param winner value, m_Winner will be equal to it
		*/
		void SetWinner(int winner);

		/**
		\brief setter of m_Winner

		\param pos position on m_Map
		\return element on that position
		*/
		int GetElement(Position pos);

		/**
		\brief getter of m_Winner

		\return m_Winner copy
		*/
		int GetWinner();

		/**
		\brief adds player in game

		\param reference to added player
		*/
		void AddPlayer(const Player& player);

		/**
		\brief getter of m_Players

		\return reference to m_Players
		*/
		std::vector<Player>& GetPlayers();
	private:
		/**
		\brief GameModel constructor

		sets 0 to m_Winner
		*/
		GameModel();

		std::array<std::array<int, 8>, 8> m_Map;	///<logic map of game
		int m_Winner;								///<winner og game (0 - nobody, 1 or 2)
		std::vector<Player>m_Players;				///<players added to game. In correct game m_Players.size() == 2

		friend class Singleton<GameModel>;
	};

	/**
	Operator == for positions
	*/
	bool operator==(const GameModel::Position& left, const GameModel::Position& right);
}