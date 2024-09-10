#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>
#include <map>
#include "Macros.h"

class SingleTone 
{
public:
	static SingleTone& GetInstance();
	void loadTextures();
	void loadFont();
	sf::Font* getFont();
	sf::Texture* getTexture(int);
	void mapColors();
	const StickData& getStickData(Colors_t stick_color);
	int getMinuts(int time);
	int getSecondes(int time);
	sf::Time getTime();
	int getGameTime();
	void startTimer();
	void mapScore();
	const sf::Color& getColor(int score);
	void showError(std::string str, sf::RenderWindow& window);
	void showEndScore(int score, sf::RenderWindow& window);

private:
	SingleTone();
	~SingleTone() = default;
	SingleTone(const SingleTone&) = default;
	SingleTone& operator=(const SingleTone&) = default;
	std::map <Colors_t, StickData> m_color;
	std::map <int,sf::Color> m_scoreMap;// this usefull for the reading from file 
	std::vector<std::string> m_IBStrings;
	std::vector<sf::Texture*>m_Texturs;
	sf::Font* m_font;
	sf::Clock m_timer;
	int m_gameTime;
};