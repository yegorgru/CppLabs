/**
\file
\brief .cpp file of class LeadersRender

implementation of LeadersRender class
*/

#include "LeadersRender.h"
#include "Assets.h"

namespace Docking::Client {
	LeadersRender::LeadersRender(sf::RenderWindow& window) :
		m_Window(window),
		m_RectangleName(sf::Vector2f(250, 70)),
		m_RectangleFind(sf::Vector2f(100, 50))
	{
		m_TextName = sf::Text("", Assets::Get().GetFont(), 20);
		m_TextFind = sf::Text("Find", Assets::Get().GetFont(), 20);
		m_TextWins = sf::Text("Wins", Assets::Get().GetFont(), 20);
		m_TextWinsNumber = sf::Text("", Assets::Get().GetFont(), 20);
		m_TextLeaders = sf::Text("Leaders:\n\n", Assets::Get().GetFont(), 20);
		m_TextName.setPosition(330, 100);
		m_TextFind.setPosition(480, 190);
		m_TextWins.setPosition(590, 50);
		m_TextWinsNumber.setPosition(590, 100);
		m_TextLeaders.setPosition(30, 50);
		
		m_RectangleName.setFillColor(sf::Color::White);
		m_RectangleFind.setFillColor(sf::Color(169, 126, 109));

		m_RectangleName.setPosition(320, 80);
		m_RectangleName.setOutlineColor(sf::Color::Black);
		m_RectangleName.setOutlineThickness(5);

		m_RectangleFind.setPosition(470, 180);

		m_TextName.setFillColor(sf::Color::Black);
		m_TextWins.setFillColor(sf::Color::Black);
		m_TextWinsNumber.setFillColor(sf::Color::Black);
		m_TextLeaders.setFillColor(sf::Color::Black);
	}

	sf::RenderWindow& LeadersRender::Window()
	{
		return m_Window;
	}

	void LeadersRender::Draw()
	{
		m_Window.clear(sf::Color(223, 236, 157));

		m_Window.draw(m_RectangleName);
		m_Window.draw(m_RectangleFind);

		m_Window.draw(m_TextName);
		m_Window.draw(m_TextFind);
		m_Window.draw(m_TextWins);
		m_Window.draw(m_TextWinsNumber);
		m_Window.draw(m_TextLeaders);

		m_Window.display();
	}

	void LeadersRender::Restore() {
		m_TextLeaders = sf::Text("Leaders:\n\n", Assets::Get().GetFont(), 20);
		m_TextLeaders.setPosition(30, 50);
		m_TextLeaders.setFillColor(sf::Color::Black);
	}

	void LeadersRender::SetPlayer(const Player& player)
	{
		m_Player = player;
		m_TextName.setString(player.GetName());
		m_TextWinsNumber.setString(std::to_string(player.GetWins()));
	}

	void LeadersRender::AddLeader(const Player& player)
	{
		m_TextLeaders.setString(m_TextLeaders.getString() + '\n' + player.GetName() +
			"....." + std::to_string(player.GetWins()));
	}

	void LeadersRender::AddLetter(char letter) {
		std::string oldName = m_TextName.getString();
		if (oldName.size() < 10) {
			m_TextName.setString(oldName + letter);
		}
	}

	void LeadersRender::EraseLetter() {
		std::string str(m_TextName.getString());
		if (str.size() > 0) {
			str.resize(str.size() - 1);
		}
		m_TextName.setString(str);
	}

	std::string LeadersRender::GetName() const
	{
		return m_TextName.getString();
	}

	void LeadersRender::IncorrectName() {
		m_RectangleName.setOutlineColor(sf::Color::Red);
		m_TextName.setString("");
		sf::Clock clock;
		while (true) {
			Draw();
			if (clock.getElapsedTime().asSeconds() > 3) {
				m_RectangleName.setOutlineColor(sf::Color::Black);
				return;
			}
		}
	}
}