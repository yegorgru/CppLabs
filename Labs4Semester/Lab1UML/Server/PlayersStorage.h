/**
\file
\brief .h file of class PlayersStorage

definition of PlayersStorage class
*/

#pragma once

#include <map>
#include <unordered_map>
#include <string>
#include <vector>
#include <set>
#include <utility>

#include "Player.h"

namespace Docking::Server {

    /**
    \brief class for storing information about players

    names, passwords and wins stored here
    */
    class PlayersStorage
    {
    public:

        /**
        \brief Player default constructor

        reads data from file with information about players
        */
        PlayersStorage();

        /**
        \brief Player's wins getter

        \param name name of expected player
        \return his wins
        */
        int GetWins(const std::string& name);

        /**
        \brief forms leaders board

        \return 10 leaders
        */
        std::vector<std::pair<int, std::string>> GetLeaders();

        /**
        \brief confirms signing in

        \param name player's name
        \param password player's password
        \return bool true if signing in was confirmed
        */
        bool SignIn(const std::string& name, const std::string& password);

        /**
        \brief confirms signing up

        \write player in file in case of confirming
        \param name player's name
        \param password player's password
        \return bool true if signing up was confirmed
        */
        bool SignUp(const std::string& name, const std::string& password);

        /**
        \brief signs out player

        \param name player's name
        */
        void SignOut(const std::string& name);

        /**
        \brief confirms signing in

        increase wins of player on 1
        calls BackUp
        \param name player's name
        */
        void Win(const std::string& name);
    private:

        /**
        \brief write all players in file
        */
        void BackUp();

        std::unordered_map<std::string, std::string> m_PlayersPasswords;	///<connection between names and passwords
        std::unordered_map<std::string, int>m_PlayersWins;                  ///<connection between names and wins
        std::multimap<int, std::string>m_WinsPlayers;                       ///<connection between wins and names
        std::set<std::string>m_OnlinePlayers;                               ///<online players storage
    };
}
