/**
\file
\brief .cpp file of class PlayersStorage

implementation of PlayersStorage class
*/

#include "PlayersStorage.h"

#include <fstream>

Docking::Server::PlayersStorage::PlayersStorage() {
    std::ifstream fin("players.txt");
    std::string name, password;
    int wins;
    while (fin >> name >> password >> wins) {
        m_PlayersPasswords.insert({ name,password });
        m_PlayersWins.insert({ name,wins });
        m_WinsPlayers.insert({ wins,name });
    }
}

int Docking::Server::PlayersStorage::GetWins(const std::string& name)
{
    return m_PlayersWins.at(name);
}

std::vector<std::pair<int, std::string>> Docking::Server::PlayersStorage::GetLeaders()
{
    std::vector<std::pair<int,std::string>>leaders;
    int counter = 0;
    for (auto it = m_WinsPlayers.rbegin(); counter < 10 && it != m_WinsPlayers.rend(); it++) {
        leaders.push_back({ it->first,it->second });
    }
    return leaders;
}

bool Docking::Server::PlayersStorage::SignIn(const std::string& name, const std::string& password)
{
    auto it = m_PlayersPasswords.find(name);
    if (it != m_PlayersPasswords.end() && it->second == password && m_OnlinePlayers.count(name)==0) {
        m_OnlinePlayers.insert(name);
        return true;
    }
    return false;
}

bool Docking::Server::PlayersStorage::SignUp(const std::string& name, const std::string& password)
{
    if (m_PlayersPasswords.find(name) == m_PlayersPasswords.end()) {
        m_PlayersPasswords[name] = password;
        m_PlayersWins[name] = 0;
        m_WinsPlayers.insert({ 0,name });
        m_OnlinePlayers.insert(name);
        std::ofstream fout("players.txt", std::ios_base::app);
        fout << name <<" "<< password<<" " << 0<<" ";
        return true;
    }
    return false;
}

void Docking::Server::PlayersStorage::SignOut(const std::string& name)
{
    m_OnlinePlayers.erase(name);
}

void Docking::Server::PlayersStorage::Win(const std::string& name) {
    int wins = m_PlayersWins.at(name);
    m_PlayersWins[name] = wins+1;
    auto it = m_WinsPlayers.find(wins);
    while (it->second != name) {
        it++;
    }
    m_WinsPlayers.erase(it);
    m_WinsPlayers.insert({ wins + 1, name });
    BackUp();
}

void Docking::Server::PlayersStorage::BackUp() {
    std::ofstream fout("players.txt");
    for (auto& item:m_PlayersPasswords) {
        fout << item.first << " " << item.second << " " << m_PlayersWins.at(item.first)<<" ";
    }
}
