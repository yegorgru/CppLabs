/**
\file
\brief .h file of class GameController

definition of GameController class
*/

#pragma once

#include "GameRender.h"
#include "GameModel.h"
#include "NetworkManager.h"
#include "EnumCode.h"
#include "Controller.h"
#include "Singleton.h"

namespace Docking::Client {

	/**
	\brief controller class responsible for game

	Singleton<GameController>, Controller inheritant
	*/
	class GameController:public Controller, public Singleton<GameController>
	{
	public:
		/**
		\brief run GameController method

		override Controller method
		\return Code of controller to launch next or Code::Exit
		*/
		Code Run() override;

		/**
		\brief restores game information
		*/
		void Restore();
	private:
		/**
		\brief GameController constructor

		call Restore method,
		initiaize attriutes with their Get() methods 
		*/
		GameController();

		GameModel& m_Model;					///<logic model of game
		GameRender& m_Render;				///<responsible for draw of window

		NetworkManager& m_NetworkManager;	///<responsible for communication with Server side

		bool m_IsEnd;						///<end of game or no
		bool m_MyTurn;						///<our player's turn or no

		friend class Singleton<GameController>;
	};
}
