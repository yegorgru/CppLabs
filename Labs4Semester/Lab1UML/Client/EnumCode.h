/**
\file
\brief .h file for codes
*/

#pragma once

namespace Docking::Client {
    /**
    enum class for codes that return from Run method of controllers
    */
	enum class Code {
		Exit = 0,
		PlayGame,
        Menu,
        Leaders
	};

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
        Leaders,
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