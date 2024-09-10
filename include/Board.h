#pragma once 
#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>
#include <set>
#include "PickUpStick.h"
#include "InfoBar.h"
#include "SingleTone.h"
#include <ctime>  
#include <cstdlib> 
#include <memory>
#include <sstream>

class Board 
{
public:
	struct sortFunctor 
	{
		bool operator()(const std::shared_ptr<PickUpStick>&stick1,const std::shared_ptr<PickUpStick>&stick2) const
		{
			return stick1->getScore() < stick2->getScore();
		}
	};
	Board();
	void forClue(sf::RenderWindow& window);
	bool doIntersect(sf::Vector2f newStickstartP, sf::Vector2f newStickendP,
		sf::Vector2f currentStickstartP, sf::Vector2f currentStickendP);
	int orientation(sf::Vector2f p, sf::Vector2f q, sf::Vector2f r);
	bool onSegment(sf::Vector2f p, sf::Vector2f q, sf::Vector2f r);
	void updateStickIntersections(const std::shared_ptr<PickUpStick>& newStick);
	bool UpdateBoard(sf::Vector2f mousePosition, sf::RenderWindow& window);
	void DrawBoard(sf::RenderWindow& window);
	void updateAvailable(const std::shared_ptr<PickUpStick>&newStick);
	void resetMarks(sf::RenderWindow& window, sf::Color color);
	void initSticks();
	int getSticksRemaining()const;
	int getAvailableSticks()const;
	int getUserScore()const;
	void saveData(std::ofstream& outFile);
	void loadGame(std::ifstream& inpFile);
	void setUserScore(int score);
private:
	void updatingContainers(std::list< std::shared_ptr < PickUpStick>>::const_iterator);
	std::list<std::shared_ptr<PickUpStick>> m_pickUpSticks;
	std::multiset< std::shared_ptr < PickUpStick>, sortFunctor> m_AvailableSticks;
	int m_UserScore;
};