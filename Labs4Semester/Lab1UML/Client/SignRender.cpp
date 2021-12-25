/**
\file
\brief .cpp file of class SignRender

implementation of SignRender class
*/

#include "SignRender.h"
#include "Assets.h"

namespace Docking::Client {
	SignRender::SignRender(sf::RenderWindow& window) :
		m_Window(window),
		m_RectangleName(sf::Vector2f(400, 70)),
		m_RectanglePassword(sf::Vector2f(400, 70)),
		m_RectangleSign(sf::Vector2f(190, 50))
	{
		m_TextName = sf::Text("", Assets::Get().GetFont(), 20);
		m_TextPassword = sf::Text("", Assets::Get().GetFont(), 20);
		m_TextSignIn = sf::Text("Sign In", Assets::Get().GetFont(), 20);
		m_TextSignUp = sf::Text("Sign Up", Assets::Get().GetFont(), 20);
		m_TextNameTitle = sf::Text("Name", Assets::Get().GetFont(), 20);
		m_TextPasswordTitle = sf::Text("Password", Assets::Get().GetFont(), 20);
		m_TextName.setPosition(30, 100);
		m_TextNameTitle.setPosition(30, 50);
		m_TextPassword.setPosition(30, 300);
		m_TextPasswordTitle.setPosition(30, 250);
		m_TextSignIn.setPosition(30, 490);
		m_TextSignUp.setPosition(240, 490);
		m_RectangleName.setFillColor(sf::Color::White);
		m_RectanglePassword.setFillColor(sf::Color::White);
		m_RectangleSign.setFillColor(sf::Color(169, 126, 109));

		m_RectangleName.setPosition(20, 80);
		m_RectanglePassword.setPosition(20, 280);
		m_RectangleName.setOutlineColor(sf::Color::Black);
		m_RectanglePassword.setOutlineColor(sf::Color::Black);

		m_TextName.setFillColor(sf::Color::Black);
		m_TextPassword.setFillColor(sf::Color::Black);
		m_TextNameTitle.setFillColor(sf::Color::Black);
		m_TextPasswordTitle.setFillColor(sf::Color::Black);
		SetFocus(0);
	}

	sf::RenderWindow& SignRender::Window() {
		return m_Window;
	}

	void SignRender::Draw() {
		m_Window.clear(sf::Color(223, 236, 157));

		m_Window.draw(m_RectangleName);
		m_Window.draw(m_RectanglePassword);

		m_RectangleSign.setPosition(20, 480);
		m_Window.draw(m_RectangleSign);
		m_RectangleSign.setPosition(230, 480);
		m_Window.draw(m_RectangleSign);

		m_Window.draw(m_TextName);
		m_Window.draw(m_TextPassword);
		m_Window.draw(m_TextSignIn);
		m_Window.draw(m_TextSignUp);
		m_Window.draw(m_TextNameTitle);
		m_Window.draw(m_TextPasswordTitle);

		m_Window.display();
	}

	void SignRender::SetFocus(bool focus) {
		if (focus) {
			m_RectanglePassword.setOutlineThickness(5);
			m_RectangleName.setOutlineThickness(0);
		}
		else {
			m_RectangleName.setOutlineThickness(5);
			m_RectanglePassword.setOutlineThickness(0);
		}
		m_Focus = focus;
	}

	void SignRender::AddLetter(char letter) {
		if (!m_Focus) {
			std::string oldName = m_TextName.getString();
			if (oldName.size() < 10) {
				m_TextName.setString(oldName + letter);
			}
		}
		else {
			if (m_Password.size() < 10) {
				m_Password.push_back(letter);
				m_TextPassword.setString(m_TextPassword.getString()+'*');
			}
		}
	}

	void SignRender::EraseLetter() {
		if (!m_Focus) {
			std::string str(m_TextName.getString());
			if (str.size() > 0) {
				str.resize(str.size() - 1);
			}
			m_TextName.setString(str);
		}
		else {
			if (m_Password.size() > 0) {
				m_Password.resize(m_Password.size() - 1);
			}
			m_TextPassword.setString(std::string(m_Password.size(),'*'));
		}
	}

	std::string SignRender::GetName() {
		return m_TextName.getString();
	}

	std::string SignRender::GetPassword() {
		return m_Password;
	}

	void SignRender::IncorrectSign() {
		m_RectangleName.setOutlineColor(sf::Color::Red);
		m_RectanglePassword.setOutlineColor(sf::Color::Red);
		m_RectangleName.setOutlineThickness(5);
		m_RectanglePassword.setOutlineThickness(5);
		m_TextName.setString("");
		m_TextPassword.setString("");
		m_Password = "";
		sf::Clock clock;
		while (true) {
			Draw();
			if (clock.getElapsedTime().asSeconds() > 3) {
				m_RectangleName.setOutlineColor(sf::Color::Black);
				m_RectanglePassword.setOutlineColor(sf::Color::Black);
				SetFocus(0);
				return;
			}
		}
	}
}