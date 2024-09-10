#pragma once 
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include "SingleTone.h"

class InfoBar
{
public:
	InfoBar();
	~InfoBar()=default;
	void DrawinfoBar(sf::RenderWindow& window);
	void DrawEndScore(sf::RenderWindow& window,int score);
	void updateSticksRemaining(int remain);
	void updateRaisedsticks(int remain);
	void updateAvailable(int available);
	void updateScore(int score);
	void updateTime();
	sf::Sprite initHintButton(float height);
	sf::Sprite initSaveButton(float height);
	bool hintPressed(sf::Vector2f mousePosition);
	bool savePressed(sf::Vector2f mousePosition);
	void handleMouseOnHint(sf::Vector2f mousePosition);
	float getGameTime()const;
	void setGameTime(float time);
	void setRaised(int raised);
	int getRaised()const;


private:
	void initTextBoxes(int index, std::string str, int height);
	void initIBStrings();
	std::vector<std::string> m_IBstrings;
	std::vector<sf::Sprite>m_IBbuttons;
	sf::Text m_IBtextBoxes[5];
	float m_GameTime;
	int m_raised;
};