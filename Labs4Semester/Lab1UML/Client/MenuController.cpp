/**
\file
\brief .cpp file of class MenuController

implementation of MenuController class
*/

#include "MenuController.h"

namespace Docking::Client {
	MenuController::MenuController():
		m_Render(MenuRender::Get()),
		m_NetworkManager(NetworkManager::Get()) {}

	Code MenuController::Run()
	{
		sf::Event event;

		while (m_Render.Window().isOpen()) {
			sf::Vector2i pos = sf::Mouse::getPosition(m_Render.Window());
			while (m_Render.Window().pollEvent(event))
			{
				if (event.type == sf::Event::Closed) {
					return Code::Exit;
				}
				if (event.type == sf::Event::MouseButtonPressed) {
					if (event.key.code == sf::Mouse::Left) {
						if (pos.x >= 20 && pos.x <= 220 && pos.y >= 80 && pos.y <= 150) {
							return Code::PlayGame;
						}
						else if (pos.x >= 20 && pos.x <= 220 && pos.y >= 280 && pos.y <= 350) {
							return Code::Leaders;
						}
						else if (pos.x >= 20 && pos.x <= 220 && pos.y >= 480 && pos.y <= 550) {
							return Code::Exit;
						}
					}
				}
				else if (event.type == sf::Event::KeyPressed) {
					if (event.key.code == sf::Keyboard::Escape) {
						return Code::Exit;
					}
				}
			}
			m_Render.Draw();
		}
	}
}