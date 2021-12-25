/**
\file
\brief .cpp file of class GameController

implementation of GameController class
*/

#include "GameController.h"

#include <SFML/Network.hpp>

namespace Docking::Client {
	GameController::GameController() :
		m_Model(GameModel::Get()),
		m_Render(GameRender::Get()),
		m_NetworkManager(NetworkManager::Get())
	{
		Restore();
	}

	Code GameController::Run()
	{
		sf::Event event;

		sf::Packet game;
		game << static_cast<int>(ClientCode::Game);
		m_NetworkManager.Send(game);

		while (m_Render.Window().isOpen())
		{
			sf::Vector2i pos = sf::Mouse::getPosition(m_Render.Window());
			int x = pos.x / m_Render.GetElementSize();
			int y = (pos.y-50) / m_Render.GetElementSize();
			while (m_Render.Window().pollEvent(event))
			{
				if (event.type == sf::Event::Closed) {
					return Code::Exit;
				}
				if (event.type == sf::Event::MouseButtonPressed) {
					if (event.key.code == sf::Mouse::Left) {
						if (m_IsEnd) {
							return Code::Menu;
						}
						sf::Packet position;
						position << static_cast<int>(ClientCode::Position) << x << y;
						m_NetworkManager.Send(position);
					}
				}
				if (event.type == sf::Event::KeyPressed)
				{
					if (m_IsEnd) {
						return Code::Menu;
					}
					if (event.key.code == sf::Keyboard::Escape) {
						sf::Packet closed;
						closed << static_cast<int>(ClientCode::ClosedGame);
						m_NetworkManager.Send(closed);
						return Code::Menu;
					}
					sf::Packet move;
					if (event.key.code == sf::Keyboard::Left) {
						move << static_cast<int>(ClientCode::Left);
						m_NetworkManager.Send(move);

					}
					if (event.key.code == sf::Keyboard::Right) {
						move << static_cast<int>(ClientCode::Right);
						m_NetworkManager.Send(move);
					}
					if (event.key.code == sf::Keyboard::Up) {
						move << static_cast<int>(ClientCode::Up);
						m_NetworkManager.Send(move);
					}
					if (event.key.code == sf::Keyboard::Down) {
						move << static_cast<int>(ClientCode::Down);
						m_NetworkManager.Send(move);
					}
				}
			}
			sf::Packet received;
			if (m_NetworkManager.Receive(received)) {
				int code;
				received >> code;

				auto serverCode = static_cast<ServerCode>(code);
				switch (serverCode) {
				case ServerCode::StartGame: {
					for (int i = 0; i < 2; i++) {
						int id, wins;
						std::string name;
						received >> id >> name >> wins;
						m_Model.AddPlayer(Player(name, wins));
					}
					m_Model.Restore();
					std::cout << "Server started game" << std::endl;
					break;
				}
				case ServerCode::EndGame: {
					m_IsEnd = true;
					int winner;
					received >> winner;
					m_Model.SetWinner(winner);
					m_Render.SetEndText(m_Model.GetPlayers()[winner - 1].GetName() + " win!");
					break;
				}
				case ServerCode::SetPosition: {
					GameModel::Position newPos, oldPos;
					int el;
					received >> el >> newPos.x >> newPos.y >> oldPos.x >> oldPos.y;
					m_Model.SetElement(el, newPos, oldPos);
					break;
				}
				}
			}
			m_Render.Draw();
		}
	}

	void GameController::Restore() {
		m_IsEnd = false;
		m_MyTurn = false;
		m_Model.GetPlayers().clear();
	}
}