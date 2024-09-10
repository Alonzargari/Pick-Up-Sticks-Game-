#include "Menu.h"


Menu::Menu() :
	m_window{ sf::VideoMode(WINDOW_LENGTH, WINDOW_HEIGHT), "PickUpSticks" },m_endGame{ false }
{
	m_window.setFramerateLimit(60);
	initPlayButton();
	initExitButton();
	initLoadButton();
	initTittle("Pick Up Sticks");
}
//---------------------------------------------------------
void Menu::menuRun()
{
	while (m_window.isOpen())
	{
		sf::Event evnt;
		while (m_window.pollEvent(evnt))
		{
			menueEvents(evnt);
		}
		drawMenu();
	}
}
//---------------------------------------------------------
void Menu::menueEvents(sf::Event& evnt)
{
	switch (evnt.type)
	{
	case sf::Event::Closed:
	{
		m_window.close();
		break;
	}
	case sf::Event::MouseButtonReleased:
	{
		auto mouseLocation = m_window.mapPixelToCoords
		({ evnt.mouseButton.x, evnt.mouseButton.y });
		menuHandleCLick(mouseLocation);
		break;
	}
	case sf::Event::MouseMoved:
		auto Location = m_window.mapPixelToCoords
		({ evnt.mouseMove.x, evnt.mouseMove.y });
		handleMouseMove(Location);
		break;
	}
}

//---------------------------------------------------------
void Menu::initTittle(std::string str)
{
	defaultTextBoxDefinition(str, 1, sf::Color::Black, sf::Color::White,600);
}
//---------------------------------------------------------
void Menu::menuHandleCLick(sf::Vector2f mousePos)
{
	for (const auto& button : m_buttons) 
	{
		if (button.getGlobalBounds().contains(mousePos)) 
		{
			if (button.getTexture() == SingleTone::GetInstance().getTexture(int(PLAY)))
			{
				m_game.setNewGame();
				m_game.RunGame(m_window);
			}
			if (button.getTexture() == SingleTone::GetInstance().getTexture(int(LOAD)))
			{
				try 
				{
					m_game.setLoadGame();
					m_game.RunGame(m_window);
					
				}
				catch (std::invalid_argument& e) 
				{
					SingleTone::GetInstance().showError(e.what(), m_window);
					sf::sleep(sf::seconds(1));
				}
				catch (std::exception& e) 
				{
					SingleTone::GetInstance().showError(e.what(), m_window);
					sf::sleep(sf::seconds(1));
				}
				
			}
			else 
			{
				m_window.close();
			}
			
		}
	}
}
//---------------------------------------------------------
void Menu::handleMouseMove(sf::Vector2f mousePos)
{
	for (auto& button : m_buttons)
	{
		if (button.getGlobalBounds().contains(mousePos)) 
		{
			button.setScale(1.3, 1.3);
			button.setOrigin(button.getLocalBounds().width / 2,
				button.getLocalBounds().height / 2);
		}
		else
		{
			button.setScale({ 1,1 });
			button.setOrigin(button.getLocalBounds().width / 2,
				button.getLocalBounds().height / 2);

		}
	}
}
//---------------------------------------------------------
void Menu::defaultTextBoxDefinition(std::string str,int index,sf::Color outlineColor,
								    sf::Color fillcolor, int deviation)
{
	float height;
	auto font = SingleTone::GetInstance().getFont();
	m_textBox[index].setFont(*font);
	m_textBox[index].setCharacterSize(60);
	m_textBox[index].getLetterSpacing();
	m_textBox[index].setString(str);
	m_textBox[index].setFillColor(fillcolor);
	m_textBox[index].setOutlineColor(outlineColor);
	m_textBox[index].setOutlineThickness(2);
	deviation > 0 ? height = WINDOW_HEIGHT - float(deviation) : height = WINDOW_HEIGHT / 2;
	m_textBox[index].setPosition({ WINDOW_LENGTH / 2,height });
	m_textBox[index].setOrigin(m_textBox[index].getLocalBounds().getSize().x / 2,
		m_textBox[index].getLocalBounds().getSize().y / 2);
}
//---------------------------------------------------------
void Menu::drawMenu()
{
	m_window.clear(sf::Color{ 20,50,100});
	std::for_each(m_buttons.begin(), m_buttons.end(), [this](auto& button) {m_window.draw(button);});
	for (int i = 0;i < 4;i++) {
		m_window.draw(m_textBox[i]);
	}
	m_window.display();
}
//---------------------------------------------------------
void Menu::initPlayButton()
{
	sf::Sprite shape;
	shape.setTexture(*SingleTone::GetInstance().getTexture((int)PLAY));
	shape.setOrigin({ shape.getLocalBounds().width / 2,shape.getLocalBounds().height / 2 });
	shape.setPosition({ WINDOW_LENGTH / 2,WINDOW_HEIGHT/2 });
	m_buttons.push_back(shape);
	auto font = SingleTone::GetInstance().getFont();
	defaultTextBoxDefinition("Play", 2,sf::Color::White, sf::Color::Black,0);

}
//---------------------------------------------------------
void Menu::initLoadButton()
{
	sf::Sprite shape;
	shape.setTexture(*SingleTone::GetInstance().getTexture((int)LOAD));
	shape.setOrigin({ shape.getLocalBounds().width / 2,shape.getLocalBounds().height / 2 });
	shape.setPosition({ WINDOW_LENGTH / 2,WINDOW_HEIGHT -475 });
	m_buttons.push_back(shape);
	defaultTextBoxDefinition("Load Game", 3, sf::Color::White, sf::Color::Black, 480);
	
}
//---------------------------------------------------------
void Menu::initExitButton()
{
	sf::Sprite shape;
	shape.setTexture(*SingleTone::GetInstance().getTexture((int)EXIT));
	shape.setOrigin({ shape.getLocalBounds().width / 2,shape.getLocalBounds().height / 2 });
	shape.setPosition({ WINDOW_LENGTH / 2,WINDOW_HEIGHT - 200 });
	m_buttons.push_back(shape);
	defaultTextBoxDefinition("Exit", 0, sf::Color::White, sf::Color::Black, 225);
}
