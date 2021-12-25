/**
\file
\brief .cpp file of class Server

implementation of Server class
*/

#include "Server.h"

#include <fstream>

namespace Docking::Server {

    Server::Server():
        m_NetworkManager(*NetworkManager<int>::Create(m_Selector)),
        m_NextIdPlayer(0),
        m_UncompletedGame(0){

        m_IsRunning = false;

        std::ifstream fin("config.txt");
        fin >> m_Port;
        fin.close();

        m_Listener.listen(m_Port);
        m_Selector.add(m_Listener);

        m_Games.emplace(0,Game());
    }

    void Server::Run() {
        m_IsRunning = true;

        while (m_IsRunning) {
            if (!m_Selector.wait())
                continue;

            if (m_Selector.isReady(m_Listener)) {
                m_Sockets.emplace_back();
                if (m_Listener.accept(m_Sockets.back()) == sf::Socket::Done) {
                    m_NetworkManager.ConnectPlayer(m_NextIdPlayer, m_Sockets.back());
                    m_Players.insert({ m_NextIdPlayer, Player(m_NextIdPlayer, m_Sockets.back()) });
                    m_NextIdPlayer++;
                    m_Selector.add(m_Sockets.back());
                }
            }
            else
            {
                for (auto player = m_Players.begin(); player!=m_Players.end();)
                {
                    if (m_NetworkManager.IsReady(player->second.GetId()))
                    {
                        sf::Packet received;
                        if (m_NetworkManager.Receive(player->second.GetId(), received))
                        {
                            int code;
                            received >> code;
                            auto clientCode = static_cast<ClientCode>(code);
                            sf::Packet answer;
                            switch (clientCode) {
                            case ClientCode::Game: {
                                m_Games.at(m_UncompletedGame).ConnectPlayer(player->second);
                                player->second.SetGame(m_UncompletedGame);
                                if (m_Games.at(m_UncompletedGame).IsCompleted()) {
                                    m_Games.at(m_UncompletedGame).StartGame();
                                    std::cout << "Game #" << m_UncompletedGame << " started!" << std::endl;
                                    m_UncompletedGame++;
                                    m_Games.emplace(m_UncompletedGame,Game());
                                }
                                break;
                            }
                            case ClientCode::Login: {
                                std::string name, password;
                                received >> name >> password;
                                bool confirm = m_PlayersStorage.SignIn(name, password);
                                sf::Packet packet;
                                if (confirm) {
                                    player->second.SetName(name);
                                    int wins = m_PlayersStorage.GetWins(name);
                                    player->second.SetWins(wins);
                                    packet << static_cast<int>(ServerCode::Confirm) <<
                                        name << wins;
                                }
                                else {
                                    packet << static_cast<int>(ServerCode::NotConfirm);
                                }
                                m_NetworkManager.Send(packet, player->second.GetId());
                                break;
                            }
                            case ClientCode::Logup: {
                                std::string name, password;
                                received >> name >> password;
                                bool confirm = m_PlayersStorage.SignUp(name, password);
                                sf::Packet packet;
                                if (confirm) {
                                    player->second.SetName(name);
                                    player->second.SetWins(0);
                                    packet << static_cast<int>(ServerCode::Confirm) <<
                                        name << 0;
                                }
                                else {
                                    packet << static_cast<int>(ServerCode::NotConfirm);
                                }
                                m_NetworkManager.Send(packet, player->second.GetId());
                                break;
                            }
                            case ClientCode::Leaders: {
                                sf::Packet leaders;
                                leaders << static_cast<int>(ServerCode::Leaders);
                                for (const auto& player : m_PlayersStorage.GetLeaders()) {
                                    leaders << player.first << player.second;
                                }
                                m_NetworkManager.Send(leaders,player->second.GetId());
                                break;
                            }
                            case ClientCode::FindPlayer:{
                                std::string name;
                                received >> name;
                                sf::Packet packet;
                                try
                                {
                                    int wins = m_PlayersStorage.GetWins(name);
                                    packet << static_cast<int>(ServerCode::Confirm) << name << wins;
                                }
                                catch (const std::exception&)
                                {
                                    packet << static_cast<int>(ServerCode::NotConfirm);
                                }
                                m_NetworkManager.Send(packet, player->second.GetId());
                                break;
                            }
                            case ClientCode::ClosedGame: {
                                int gameId = player->second.GetGame();
                                if (m_Games.at(gameId).IsActive()) {
                                    m_Games.at(gameId).RunNetwork(received, clientCode, player->second.GetId());
                                    m_PlayersStorage.Win(m_Games.at(gameId).GetWinnerName());
                                    m_Games.erase(gameId);
                                }           
                                else {
                                    m_Games.at(gameId).Clear();
                                }
                                player->second.SetGame(-1);
                                break;
                            }
                            case ClientCode::ClosedWindow: {
                                int gameId = player->second.GetGame();
                                if (gameId != -1) {
                                    if (m_Games.at(gameId).IsActive()) {
                                        m_Games.at(gameId).RunNetwork(received, clientCode, player->second.GetId());
                                        m_PlayersStorage.Win(m_Games.at(gameId).GetWinnerName());
                                        m_Games.erase(gameId);
                                    }
                                    else {
                                        m_Games.at(gameId).Clear();
                                    }
                                }
                                m_PlayersStorage.SignOut(player->second.GetName());
                                player = m_Players.erase(player);
                                continue;
                                break;
                            }
                            default: {
                                int gameId = player->second.GetGame();
                                m_Games.at(gameId).RunNetwork(received, clientCode, player->second.GetId());
                                if (!m_Games.at(gameId).IsActive()) {
                                    m_PlayersStorage.Win(m_Games.at(gameId).GetWinnerName());
                                    m_Games.erase(gameId);
                                }
                                break;
                            }
                            }
                        }
                    }
                    player++;
                }
            }
        }
    }
}