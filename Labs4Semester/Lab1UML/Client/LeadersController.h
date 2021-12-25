/**
\file
\brief .h file of class LeadersController

definition of LeadersController class
*/

#pragma once

#include "LeadersRender.h"
#include "NetworkManager.h"
#include "EnumCode.h"
#include "Controller.h"
#include "Singleton.h"

namespace Docking::Client {

	/**
	\brief controller class responsible for leaders board

	Singleton<LeadersController>, Controller inheritant
	*/
	class LeadersController:public Controller, public Singleton<LeadersController>
	{
	public:
		/**
		\brief run LeadersController method

		override Controller method
		\return Code of controller to launch next or Code::Exit
		*/
		Code Run() override;
	private:
		/**
		\brief LeadersController constructor

		initiaize attriutes with their Get() methods
		*/
		LeadersController();

		LeadersRender& m_Render;			///<responsible for draw of window
		NetworkManager& m_NetworkManager;	///<responsible for communication with Server side

		friend class Singleton<LeadersController>;
	};
}
