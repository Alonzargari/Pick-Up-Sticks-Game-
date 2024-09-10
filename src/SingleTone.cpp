#pragma once

#include "SingleTone.h"
//---------------------------------------------------------
SingleTone& SingleTone::GetInstance()
{
	static SingleTone instance;
	return instance;
}
//---------------------------------------------------------
void SingleTone::loadTextures()
{
	std::string strings[5] = {"exitButton.png","startButton.png","hintButton.png",
		"saveButton.png","loadGameButton.png"};
	try
	{
		for (int i = 0;i < 5;i++)
		{
			auto texture = new sf::Texture();;
			if (!texture->loadFromFile(strings[i])) {
				throw std::runtime_error("Could not load picture: " + strings[i]);
			}
			m_Texturs.emplace_back(texture);

		}
	}
	
	catch (const std::runtime_error& e) {
		std::cout << e.what() << std::endl;
		exit(EXIT_FAILURE);
	}
	catch (const std::exception& e) {
		std::cout << "An unexpected error occurred: " << e.what() << std::endl;
		exit(EXIT_FAILURE);
	}
}
//---------------------------------------------------------
void SingleTone::loadFont()
{
	m_font = new sf::Font();
	try {
		if (!m_font->loadFromFile("FORTE.TTF")) {
			throw std::runtime_error("Could not load picture:FORTE.TTF");
		}
	}
	catch (const std::runtime_error& e) {
		std::cout << e.what() << std::endl;
		exit(EXIT_FAILURE);
	}
	catch (const std::exception& e) {
		// Catch any other std::exception types
		std::cout << "An unexpected error occurred: " << e.what() << std::endl;
		exit(EXIT_FAILURE);
	}
}
//---------------------------------------------------------
sf::Font* SingleTone::getFont()
{
	return m_font;
}
//---------------------------------------------------------
sf::Texture* SingleTone::getTexture(int index)
{
	return m_Texturs[index];
}
//---------------------------------------------------------
void SingleTone::mapColors()
{
	m_color[GREEN] = StickData(sf::Color::Green,5);
	m_color[YELLOW] = StickData(sf::Color::Yellow,10);
	m_color[RED] = StickData(sf::Color::Red, 15);
	m_color[BLUE] = StickData(sf::Color::Blue, 20);
	m_color[BROWN] = StickData(sf::Color{140,83,0},25);
}
//---------------------------------------------------------
void SingleTone::mapScore()
{
	m_scoreMap[GREEN_SCORE] = sf::Color::Green;
	m_scoreMap[YELLOW_SCORE] = sf::Color::Yellow;
	m_scoreMap[RED_SCORE] = sf::Color::Red;
	m_scoreMap[BLUE_SCORE] = sf::Color::Blue;
	m_scoreMap[BROWN_SCORE] = sf::Color{ 140,83,0 };
}
//---------------------------------------------------------
const StickData& SingleTone::getStickData(Colors_t stick_color)
{
	
	return m_color[stick_color];
}
//---------------------------------------------------------
int SingleTone::getMinuts(int time)
{
	return time / 60;
}
//---------------------------------------------------------
int SingleTone::getSecondes(int time)
{
	return time % 60;
}
//---------------------------------------------------------
sf::Time SingleTone::getTime()
{
	return m_timer.restart();
}
//---------------------------------------------------------
int SingleTone::getGameTime()
{
	return m_gameTime;
}
//---------------------------------------------------------
void SingleTone::startTimer()
{
	m_timer.restart();
}
//---------------------------------------------------------

//---------------------------------------------------------
SingleTone::SingleTone()
{
	mapColors();
	mapScore();
	loadTextures();
	loadFont();
	m_gameTime =1;
}
//---------------------------------------------------------
void SingleTone::showError(std::string str, sf::RenderWindow& window)
{
	sf::Text errorMessege;
	errorMessege.setFont(*getFont());
	errorMessege.setString(str);
	errorMessege.setCharacterSize(40);
	errorMessege.setFillColor(sf::Color::White);
	errorMessege.setOutlineColor(sf::Color::Black);
	errorMessege.setOutlineThickness(2);
	window.draw(errorMessege);
	window.display();
}
//---------------------------------------------------------
void SingleTone::showEndScore(int score, sf::RenderWindow& window)
{
	sf::Text EndScore;
	EndScore.setFont(*getFont());
	EndScore.setString("Game Is Ended \n Your Score is: "+std::to_string(score));
	EndScore.setPosition(WINDOW_LENGTH / 2, WINDOW_HEIGHT / 2);
	EndScore.setCharacterSize(80);
	EndScore.setOrigin(EndScore.getLocalBounds().width / 2, EndScore.getLocalBounds().height / 2);
	EndScore.setFillColor(sf::Color::Cyan);
	EndScore.setOutlineColor(sf::Color::Black);
	EndScore.setOutlineThickness(2);
	window.draw(EndScore);
	window.display();
}
//---------------------------------------------------------
const sf::Color& SingleTone::getColor(int score)
{
	return m_scoreMap[score];
}
//---------------------------------------------------------