/**
\file
\brief .cpp file of class ClientController

implementation of ClientController class
*/

#include <SFML/Network.hpp>

#include "ClientController.h"
#include "MenuController.h"
#include "EnumCode.h"
#include "SignController.h"
#include "LeadersController.h"
#include "LeadersRender.h"

namespace Docking::Client {
	ClientController::ClientController(sf::RenderWindow& window):
		m_Window(window) {}

	void ClientController::Run() {
		Code code = SignController::Get().Run(m_Player);
		while (true) {
			switch (code) {
			case Code::Exit: {
				sf::Packet closed;
				closed << static_cast<int>(ClientCode::ClosedWindow);
				NetworkManager::Get().Send(closed);
				m_Window.close();
				return;
			}
			case Code::Menu: {
				code = MenuController::Get().Run();
				break;
			}
			case Code::PlayGame: {
				GameController::Get().Restore();
				GameModel::Get().Restore();
				GameRender::Get().Restore();
				code = GameController::Get().Run();
				break;
			}
			case Code::Leaders: {
				LeadersRender::Get().Restore();
				LeadersRender::Get().SetPlayer(m_Player);
				code = LeadersController::Get().Run();
				break;
			}
			}
		}
	}
}