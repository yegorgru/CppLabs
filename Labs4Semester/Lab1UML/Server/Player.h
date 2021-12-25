/**
\file
\brief .h file of class Player

definition of Player class
*/

#pragma once

#include <list>

#include <SFML/Network.hpp>

namespace Docking::Server {

    /**
    \brief class to store information about player
    */
    class Player {
    public:
        /**
        \brief Player constructor

        \param id m_Id will be equal to it
        \param socket reference to tcp socket, m_Socket will be equal to it
        */
        Player(int id, sf::TcpSocket& socket);

        /**
        \brief default destructor
        */
        virtual ~Player() noexcept = default;

        /**
        \brief m_Id getter

        \return m_Id copy
        */
        int GetId() const;

        /**
        \brief m_Game getter

        \return m_Game copy
        */
        int GetGame() const;

        /**
        \brief m_Game setter

        \param game, m_Game will be equal to it
        */
        void SetGame(int game);

        /**
        \brief m_Name getter

        \return m_Game copy
        */
        std::string GetName() const;

        /**
        \brief m_Name setter

        \param name const reference to string, m_Name will be equal to it
        */
        void SetName(const std::string& name);

        /**
        \brief m_Wins setter

        \param wins, m_Wins will be equal to it
        */
        void SetWins(int wins);

        /**
        \brief m_Wins getter

        \return m_Wins copy
        */
        int GetWins() const;
    private:
        int m_Id;                   ///<player's id
        sf::TcpSocket& m_Socket;    ///<reference to player's socket
        int m_Game;                 ///<current player's game. If there isn't game, == -1
        std::string m_Name;         ///<player's name
        int m_Wins;                 ///<number of player's wins
    };
}