/**
\file
\brief .h file of class Game

definition of Game class
*/

#pragma once

#include <array>
#include <unordered_map>
#include <set>
#include <stdexcept>

#include "NetworkManager.h"
#include "Player.h"
#include "EnumCode.h"

namespace Docking::Server {

    /**
    \brief class for running game

    Connects players, sends messages to them, makes logic calculations
    */
    class Game {
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
        \brief default constructor of game

        m_NetworkManager initialized by its Get() method,
        m_CurrentPlayer equal 0, m_Winner equal 0, m_Position equal {-1,-1}
        */
        Game();

        /**
        \brief default game destructor
        */
        virtual ~Game() = default;

        /**
        \brief connects player

        saves pointer to player, fills m_IdElement and m_ElementId
        \param player reference to connected player
        */
        void ConnectPlayer(Player& player);

        /**
        \brief iteration of game

        makes logic calculations and sends result packets to players 
        \param received reference to received packet
        \param clientCode ClientCode from received packet
        \param playerId id of player who sent packet
        */
        void RunNetwork(sf::Packet& received, ClientCode clientCode, int playerId);

        /**
        \brief m_CurrentPlayer getter

        \return m_CurrentPlayer
        */
        int CurrentPlayer() const;

        /**
        \brief elements getter

        0, 1 or 2 value
        \return element with that position
        */
        int GetElement(int x, int y) const;

        /**
        \brief m_Position setter

        \param x x coordinate on m_Map
        \param y y coordinate on m_Map
        */
        void SetPosition(int x, int y);

        /**
        \brief m_Position setter

        \param element element to set (0, 1 or 2)
        \param pos y coordinate on m_Map
        */
        void SetElement(int element, Position pos);

        /**
        \brief m_Winner getter

        \return m_Winner
        */
        int GetWinnerId() const;

        /**
        \brief m_Winner name getter

        \throw std::invalid_argument("There isn't winner") if m_Winner == 0
        \return copy of name of winner
        */
        std::string GetWinnerName() const;

        /**
        \brief m_Position getter

        \return copy of m_Position
        */
        Position GetPosition() const;

        /**
        \brief sets next m_Current player

        if was 1 then will be 2
        if was 2 then will be 1
        */
        void NextTurn();

        /**
        \brief sets next m_Current player

        calls IsCorrectMove, IsEnd, CheckClosed in case of correct move
        send set position and end game packets
        \throw std::invalid_argument("Incorrect move code") in case of incorrect client code
        \param direction left - 0, right - 1, top - 2, down - 3
        */
        void MakeMove(int direction);

        /**
        \brief checks if one of players connected his blocks

        sets m_Winner
        \return bool true if there is winner
        */
        bool IsEnd();

        /**
        \brief checks if one of players is blocked by another player

        sets m_Winner
        \return bool true if there is winner
        */
        bool CheckClosed(Position pos);
        
        /**
        \brief checks if game is active

        \return bool true if game is active
        */
        bool IsActive() const;

        /**
        \brief checks if game is completed

        \return bool true if game is completed (2 players connected)
        */
        bool IsCompleted() const;

        /**
        \brief starts game

        sends start packet
        */
        void StartGame();

        /**
        \brief sets winner

        \param winner m_Winner will be equal to it
        */
        void EndGame(int winner);

        /**
        \brief gets id of another player

        \param id id of player
        \return id of another player to id
        */
        int AnotherPlayerId(int id);

        /**
        \brief clears players information

        clears m_Players, m_IdElement and m_ElementId
        */
        void Clear();
    private:
        /**
        \brief method that help IsEnd method

        \param position to check
        \param el element to check
        \param elements found elements positions
        */
        void CheckElements(Position pos, int el, std::set<std::pair<int, int>>& elements);

        /**
        \brief checks if it's correct move

        works with m_Position
        \param direction left - 0, right - 1, top - 2, down - 3
        \return bool true if it's correct move
        */
        bool IsCorrectMove(int direction);

        std::vector<Player*> m_Players;             ///<pointers to connected players
        int m_CurrentPlayer;                        ///<current player's element, game starts with 1
        int m_Winner;                               ///<winner's element

        std::array<std::array<int, 8>, 8> m_Map;    ///<map that contains elements
        Position m_Position;                        ///<position that current player clicked last

        NetworkManager<int>& m_NetworkManager;      ///<responsible for receiving and sending packets

        std::unordered_map<int, int>m_IdElement;    ///<contact between id and element
        std::unordered_map<int, int>m_ElementId;    ///<contact between element and id
    };
}