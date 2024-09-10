#pragma once
#include "Macros.h"
#include "SingleTone.h"
#include <SFML/Graphics.hpp>
#include <random>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <fstream>
#include <iostream>
#include <string>



class Board;
class PickUpStick 
{
public:
	PickUpStick(int serial);
	PickUpStick(int serial, int score, float posX, float posY, int angle);
	friend bool operator == (const PickUpStick & obj1, const PickUpStick& obj2);
	void DrawPickUpStick(sf::RenderWindow& window);
	sf::Vector2f getEndPoint()const;
	sf::Vector2f getStartPoint()const;
	int getScore()const;
	void increaseBounders(const std::shared_ptr<PickUpStick>&);
	bool BoundersIsEmpty()const;
	bool Pressed(sf::Vector2f mousePosition);
	void markBounders(sf::RenderWindow& window, sf::Color);
	void globalColoring(const sf::Color&);
	void UpdateBounders(const std::shared_ptr<PickUpStick>& boundedStick);
	void writeData(std::ofstream& outFile);
	void readData(std::string);
private:
	sf::RectangleShape m_pickUpStick;
	void initStickData();
	std::list<std::shared_ptr<PickUpStick>>m_Bounders;
	int m_StickScore;
	int m_angle;
	int m_serialStickNumber;
};
