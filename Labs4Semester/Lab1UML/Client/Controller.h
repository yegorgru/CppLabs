/**
\file
\brief .h file of class Controller
*/

#pragma once

#include "EnumCode.h"

namespace Docking::Client {

	/**
	\brief Controller abstact class, parent of all controllers except ClientController
	*/
	class Controller {
	public:
		/**
		\brief pure virtual method for running controller
		*/
		virtual Code Run()=0;
	};
}