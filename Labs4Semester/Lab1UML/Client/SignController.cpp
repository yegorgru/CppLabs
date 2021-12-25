/**
\file
\brief .cpp file of class SignController

implementation of SignController class
*/

#include "SignController.h"

#include <SFML/Graphics.hpp>

namespace Docking::Client {
	SignController::SignController() :
		m_Render(SignRender::Get()),
		m_NetworkManager(NetworkManager::Get()) {}

	Code SignController::Run()
	{
		return Code::Exit;
	}
	
	Code SignController::Run(Player& player)
	{
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
						if (pos.x >= 20 && pos.x <= 420 && pos.y >= 80 && pos.y <= 150) {
							m_Render.SetFocus(0);
						}
						else if (pos.x >= 20 && pos.x <= 420 && pos.y >= 280 && pos.y <= 350) {
							m_Render.SetFocus(1);
						}
						else if (pos.x >= 20 && pos.x <= 210 && pos.y >= 480 && pos.y <= 530) {
							sf::Packet login;
							login << static_cast<int>(ClientCode::Login)
								<< m_Render.GetName() << m_Render.GetPassword();
							m_NetworkManager.Send(login);
						}
						else if (pos.x >= 230 && pos.x <= 420 && pos.y >= 480 && pos.y <= 530) {
							sf::Packet logup;
							logup << static_cast<int>(ClientCode::Logup) 
								<< m_Render.GetName() << m_Render.GetPassword();
							m_NetworkManager.Send(logup);
						}
					}
				}
				else if (event.type == sf::Event::KeyPressed) {
					if (event.key.code == sf::Keyboard::Backspace)
					{
						m_Render.EraseLetter();
					}
					else if (event.key.code == sf::Keyboard::Escape) {
						return Code::Exit;
					}
				}
				else if (event.type == sf::Event::TextEntered) {
					if (event.text.unicode >= 48 && event.text.unicode <= 57 ||
						event.text.unicode >= 65 && event.text.unicode <=90 ||
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
					player.SetName(name);
					player.SetWins(wins);
					return Code::Menu;
				}
				case ServerCode::NotConfirm: {
					m_Render.IncorrectSign();
				}
				}
			}

			m_Render.Draw();
		}
	}
}