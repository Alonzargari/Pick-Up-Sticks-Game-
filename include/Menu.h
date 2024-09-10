#pragma once
#include <SFML/Graphics.hpp>
#include "GameController.h"
#include "SingleTone.h"
#include "vector"
#include "Macros.h"
#include "Board.h"

class Menu 
{
public:
	Menu();
	~Menu() = default;
	void menuRun();
	void menueEvents(sf::Event& evnt);
	//handle mouse events (click on button or to make the button bigger)
	void menuHandleCLick(sf::Vector2f);
	void handleMouseMove(sf::Vector2f);
	void defaultTextBoxDefinition(std::string str,int index, sf::Color outlineColor, 
								  sf::Color fillcolor, int deviation);
	void drawMenu();

private:
	sf::RenderWindow m_window;
	GameController m_game;
	Board m_board;
	//init buttons in the menu
	void initExitButton();
	//void initPlayAgainButton();
	void initTittle(std::string str);
	void initPlayButton();
	void initLoadButton();
	sf::Text m_textBox[4];
	std::vector<sf::Sprite>m_buttons;
	bool m_endGame;
};