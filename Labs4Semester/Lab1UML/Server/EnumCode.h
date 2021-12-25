/**
\file
\brief .h file for codes
*/

#pragma once

namespace Docking::Server {

    /**
    enum class for codes that is begin of sf::Packet sent from Client to Server
    */
    enum class ClientCode : int {
        ClosedWindow = 0,
        ClosedGame,
        Position,
        Up,
        Down,
        Left,
        Right,
        Login,
        Logup,
        Game,
        FindPlayer,
        Leaders
    };

    /**
    enum class for codes that is begin of sf::Packet sent from Server to Client
    */
    enum class ServerCode : int {
        StartGame = 0,
        EndGame,
        SetPosition,
        Confirm,
        NotConfirm,
        Leaders
    };
}