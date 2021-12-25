/**
\file
\brief .h file of class MenuController

definition of MenuController class
*/

#pragma once
#include "MenuRender.h"
#include "EnumCode.h"
#include "NetworkManager.h"
#include "Controller.h"
#include "Singleton.h"

namespace Docking::Client{

	/**
	\brief controller class responsible for menu

	Singleton<MenuController>, Controller inheritant
	*/
	class MenuController:public Controller, public Singleton<MenuController>
	{
	public:
		/**
		\brief run MenuController method

		override Controller method
		\return Code of controller to launch next or Code::Exit
		*/
		Code Run() override;
	private:
		/**
		\brief SignController constructor

		initiaize attriutes with their Get() methods
		*/
		MenuController();
		MenuRender& m_Render;				///<responsible for draw of window
		NetworkManager& m_NetworkManager;	///<responsible for communication with Server side

		friend Singleton<MenuController>;
	};
}

