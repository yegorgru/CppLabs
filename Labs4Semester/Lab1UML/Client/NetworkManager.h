/**
\file
\brief .h file of class NetworkManager

definition of NetworkManager class
*/

#pragma once

#include <SFML/Network.hpp>
#include <iostream>

#include "Singleton.h"

namespace Docking::Client {

    /**
    \brief manager class responsible for communication with Server

    connecting to Server side, sending/receiving packets
    Singleton<NetworkManager> inheritant
    */
    class NetworkManager : public Singleton<NetworkManager> {
    public:
        /**
        \brief Sets blocking type on socket

        \param value if value == true, application will wait packet from server while it come, else it will not wait
        */
        void SetBlocking(bool value);

        /**
        \brief receiving of packet from server

        \param packet reference to packet. Information will be written in this packet
        \return true if packet was received
        */
        bool Receive(sf::Packet& packet);

        /**
        \brief sending packet to server

        \param packet reference to packet. This packet will be sent to server
        */
        void Send(sf::Packet& packet);
    private:
        /**
        \brief NetworkManager constructor

        \param ip reference to ip address of server
        \param port number of server port
        */
        NetworkManager(const sf::IpAddress& ip, unsigned port);

        sf::TcpSocket m_Connection; ///<socket that will be connected to server
        
        friend class Singleton<NetworkManager>;
    };
}
