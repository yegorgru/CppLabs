/**
\file
\brief .h file of class Server

definition of Server class
*/

#pragma once

#include <string>
#include <unordered_map>
#include <map>

#include <SFML/Network.hpp>

#include "Game.h"
#include "Player.h"
#include "PlayersStorage.h"
#include "Singleton.h"

namespace Docking::Server {

    /**
    \brief main class that controls everything on Server side
    */
    class Server : public Singleton<Server> {
    public:

        /**
        \brief run Server method

        launch main loop of server
        */
        void Run();
    private:
        /**
        \brief default server constructor

        creates NetworkManager, TcpSelector, TcpListener, first Game
        m_IsRunning == false
        */
        Server();

        /**
        \brief default destructor
        */
        virtual ~Server() noexcept = default;

        bool m_IsRunning;                           ///<is server running bool

        PlayersStorage m_PlayersStorage;            ///<players storage
        std::unordered_map<int, Player>m_Players;   ///<connected players
        std::unordered_map<int, Game>m_Games;       ///<active games
       
        size_t m_UncompletedGame;                   ///<current uncompleted game

        NetworkManager<int>& m_NetworkManager;      ///<reference to NetworkManager<int>

        unsigned short m_Port;                      ///<server's port
        sf::TcpListener m_Listener;                 ///<server's tcp listener
        sf::SocketSelector m_Selector;              ///<server's tcp selector
        std::list<sf::TcpSocket> m_Sockets;         ///<connected to server sockets
        int m_NextIdPlayer;                         ///<id of next connected player

        friend Singleton<Server>;
    };
}