#pragma once 
#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>
#include "PickUpStick.h"
#include "SingleTone.h"
#include "Board.h"
#include <memory>
#include "InfoBar.h"
#include "FormatException.h"


class GameController 
{
public:
	GameController();
	void setNewGame();
	void setLoadGame();
	void RunGame(sf::RenderWindow& window);
	void handleClick(sf::Vector2f, sf::RenderWindow& window);
	bool timeLeft();
	void GameDraw(sf::RenderWindow& window);
	void GameEvents(sf::RenderWindow& window, sf::Event& evnt);
private:
	
	Board m_board;
	InfoBar m_infoBar;
	sf::Clock m_Clock;
	bool m_boardUpdated;
	int m_boardStartSize;
	bool m_endGame;

};