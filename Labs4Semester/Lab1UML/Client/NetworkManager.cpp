/**
\file
\brief .cpp file of class NetworkManager

implementation of NetworkManager class
*/

#include "NetworkManager.h"

namespace Docking::Client {
    NetworkManager::NetworkManager(const sf::IpAddress& ip, unsigned port) {
        if (m_Connection.connect(ip, port, sf::seconds(5)) != sf::Socket::Done) {
            std::cout << "Error connecting to server" << std::endl;
        }
        else {
            m_Connection.setBlocking(false);
            std::cout << "Connected to server";
        }
    }

    bool NetworkManager::Receive(sf::Packet& packet) {
        if (m_Connection.getRemoteAddress() != sf::IpAddress::None &&
            m_Connection.receive(packet) == sf::Socket::Done) {  
            return true;
        }

        return false;
    }

    void NetworkManager::Send(sf::Packet& packet) {
        if (m_Connection.send(packet) != sf::Socket::Done) {
            std::cout << "Error sending data to server!";
        }
    }

    void NetworkManager::SetBlocking(bool value) {
        m_Connection.setBlocking(value);
    }
}
