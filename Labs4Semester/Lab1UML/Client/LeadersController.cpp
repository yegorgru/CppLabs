/**
\file
\brief .cpp file of class LeadersController

implementation of LeadersController class
*/

#include "LeadersController.h"

#include <SFML/Graphics.hpp>

namespace Docking::Client {
	LeadersController::LeadersController():
		m_NetworkManager(NetworkManager::Get()),
		m_Render(LeadersRender::Get()) {}

	Code LeadersController::Run()
	{
		sf::Packet leadersRequest;
		leadersRequest << static_cast<int>(ClientCode::Leaders);
		m_NetworkManager.Send(leadersRequest);

		sf::Packet update;
		update << static_cast<int>(ClientCode::FindPlayer)
			<< m_Render.GetName();
		m_NetworkManager.Send(update);

		sf::Event event;

		while (m_Render.Window().isOpen()) {
			sf::Vector2i pos = sf::Mouse::getPosition(m_Render.Window());
			while (m_Render.Window().pollEvent(event))
			{
				if (event.type == sf::Event::Closed) {
					return Code::Exit;
				}
				else if (event.type == sf::Event::MouseButtonPressed) {
					if (event.key.code == sf::Mouse::Left) {
						if (pos.x >= 480 && pos.x <= 580 && pos.y >= 190 && pos.y <= 240) {
							sf::Packet find;
							find << static_cast<int>(ClientCode::FindPlayer)
								<< m_Render.GetName();
							m_NetworkManager.Send(find);
						}
					}
				}
				else if (event.type == sf::Event::KeyPressed) {
					if (event.key.code == sf::Keyboard::Backspace)
					{
						m_Render.EraseLetter();
					}
					else if (event.key.code == sf::Keyboard::Escape) {
						return Code::Menu;
					}
				}
				else if (event.type == sf::Event::TextEntered) {
					if (event.text.unicode >= 48 && event.text.unicode <= 57 ||
						event.text.unicode >= 65 && event.text.unicode <= 90 ||
						event.text.unicode >= 97 && event.text.unicode <= 122) {
						m_Render.AddLetter((char)event.text.unicode);
					}
				}
			}

			sf::Packet received;
			if (m_NetworkManager.Receive(received)) {
				int code, wins;
				std::string name;
				received >> code;

				auto serverCode = static_cast<ServerCode>(code);
				switch (serverCode) {
				case ServerCode::Confirm: {
					received >> name >> wins;
					m_Render.SetPlayer(Player(name, wins));
					break;
				}
				case ServerCode::NotConfirm: {
					m_Render.IncorrectName();
					break;
				}
				case ServerCode::Leaders: {
					std::string name;
					int wins;
					while (received >> wins >> name) {
						m_Render.AddLeader(Player(name, wins));
					}
					break;					  
				}
				}
			}

			m_Render.Draw();
		}
	}
}