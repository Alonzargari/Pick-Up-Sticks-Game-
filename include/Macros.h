#pragma once 

#include <SFML/Graphics.hpp>

const int WINDOW_LENGTH = 1400;
const int WINDOW_HEIGHT = 700;
const int STICK_SIZE_WIDTH = 10;
const int STICK_SIZE_LENGTH = 200;
const int INFOBAR_LENGTH = 400;
const int INFOBAR_HEIGHT = 700;

const int GREEN_SCORE = 5;
const int YELLOW_SCORE = 10;
const int RED_SCORE = 15;
const int BLUE_SCORE = 20;
const int BROWN_SCORE = 25;
const std::string FILE_NAME= "OUT FILE";


enum Colors_t
{
	YELLOW, GREEN, RED, BLUE, BROWN
};
enum Textures_t {
	EXIT, PLAY,HINT,SAVE,LOAD
};
struct StickData
{
	sf::Color _color;
	int _score;
};