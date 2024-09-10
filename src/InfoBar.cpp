#include "InfoBar.h"


InfoBar::InfoBar()
	:m_raised{0}
{
	m_GameTime= SingleTone::GetInstance().getGameTime() * 60;
	initIBStrings();
	for (int i = 0;i < m_IBstrings.size();i++)
	{
		auto height = i * 100;
		initTextBoxes(i, m_IBstrings[i], height);
	}
	float hintButtonYheight = m_IBtextBoxes[4].getPosition().y + 100;
	m_IBbuttons.emplace_back(initHintButton(hintButtonYheight));
	m_IBbuttons.emplace_back(initSaveButton(hintButtonYheight+100));

}
//---------------------------------------------------------
void InfoBar::initIBStrings()
{
	m_IBstrings.emplace_back("Time Left: ");
	m_IBstrings.emplace_back("Score: ");
	m_IBstrings.emplace_back("Raised sticks: ");
	m_IBstrings.emplace_back("Remaining sticks: ");
	m_IBstrings.emplace_back("Available Sticks: ");
};
//---------------------------------------------------------
void InfoBar::DrawinfoBar(sf::RenderWindow& window)
{
	sf::RectangleShape shape;
	shape.setPosition(WINDOW_LENGTH - INFOBAR_LENGTH, 0);
	shape.setSize({ INFOBAR_LENGTH, INFOBAR_HEIGHT });
	shape.setFillColor(sf::Color{ 255, 255, 255, 128 });
	window.draw(shape);
	for (int i = 0;i < m_IBstrings.size();i++)
	{
		window.draw(m_IBtextBoxes[i]);
	}
	for (int i = 0;i < m_IBbuttons.size();i++)
	{
		window.draw(m_IBbuttons[i]);
	}
	
}
//---------------------------------------------------------
void InfoBar::DrawEndScore(sf::RenderWindow& window,int score)
{
	m_IBtextBoxes[1].setString("GAME ENDED YOURE SCORE IS: \n" + std::to_string(score));
}
//---------------------------------------------------------
void InfoBar::updateSticksRemaining(int remain)
{
	m_IBtextBoxes[3].setString(m_IBstrings[3] + std::to_string(remain));
}
//---------------------------------------------------------
void InfoBar::updateRaisedsticks(int raised)
{
	m_raised += raised;
	m_IBtextBoxes[2].setString(m_IBstrings[2] + std::to_string(m_raised));
}
//---------------------------------------------------------
void InfoBar::updateAvailable(int available)
{
	m_IBtextBoxes[4].setString(m_IBstrings[4] + std::to_string(available));
}
//---------------------------------------------------------
void InfoBar::updateScore(int score)
{
	m_IBtextBoxes[1].setString(m_IBstrings[1] + std::to_string(score));
}
//---------------------------------------------------------
void InfoBar::updateTime()
{
	auto elapsed = SingleTone::GetInstance().getTime().asSeconds();
	m_GameTime -= elapsed;
	auto seconds = SingleTone::GetInstance().getSecondes(m_GameTime);
	auto minutes = SingleTone::GetInstance().getMinuts(m_GameTime);
	m_IBtextBoxes[0].setString("Time Left: 0" + std::to_string(minutes) + ":" + std::to_string(seconds));
	if (seconds < 10)
	{
		m_IBtextBoxes[0].setString("Time Left: 0" + std::to_string(minutes) + ":" + "0" + std::to_string(seconds));

	}
	if (seconds < 20 && minutes == 0)
	{
		m_IBtextBoxes[0].setFillColor(sf::Color::Red);
	}
}
//---------------------------------------------------------
sf::Sprite InfoBar::initHintButton(float height)
{
	sf::Sprite hintButton;
	sf::Vector2f pos{ WINDOW_LENGTH - INFOBAR_LENGTH + 200 ,height };
	hintButton.setTexture(*SingleTone::GetInstance().getTexture(HINT));
	hintButton.setPosition(pos);
	hintButton.setOrigin(hintButton.getLocalBounds().width / 2,
		hintButton.getLocalBounds().height / 2);
	return hintButton;
}
//---------------------------------------------------------
sf::Sprite InfoBar::initSaveButton(float height)
{
	sf::Sprite SaveButton;
	sf::Vector2f pos{ WINDOW_LENGTH - INFOBAR_LENGTH + 200 ,height };
	SaveButton.setTexture(*SingleTone::GetInstance().getTexture(SAVE));
	SaveButton.setPosition(pos);
	SaveButton.setOrigin(SaveButton.getLocalBounds().width / 2,
		SaveButton.getLocalBounds().height / 2);
	return SaveButton;
}
//---------------------------------------------------------
bool InfoBar::hintPressed(sf::Vector2f mousePosition)
{
	return m_IBbuttons[0].getGlobalBounds().contains(mousePosition);
}
//---------------------------------------------------------
bool InfoBar::savePressed(sf::Vector2f mousePosition)
{
	return m_IBbuttons[1].getGlobalBounds().contains(mousePosition);
}
//---------------------------------------------------------
void InfoBar::handleMouseOnHint(sf::Vector2f mousePosition)
{
	for (int i = 0;i < m_IBbuttons.size();i++) 
{
		if (m_IBbuttons[i].getGlobalBounds().contains(mousePosition))
		{
			m_IBbuttons[i].setScale(1.1, 1.1);
			m_IBbuttons[i].setOrigin(m_IBbuttons[i].getLocalBounds().width / 2,
				m_IBbuttons[i].getLocalBounds().height / 2);
		}
		else
		{
			m_IBbuttons[i].setScale({ 1,1 });
			m_IBbuttons[i].setOrigin(m_IBbuttons[i].getLocalBounds().width / 2,
				m_IBbuttons[i].getLocalBounds().height / 2);

		}
	}
}
//---------------------------------------------------------
float InfoBar::getGameTime() const
{
	return m_GameTime;
}
//---------------------------------------------------------
void InfoBar::setGameTime(float time)
{
	m_GameTime = time;
}
//---------------------------------------------------------
void InfoBar::setRaised(int raised)
{
	m_raised = raised;
}
//---------------------------------------------------------
int InfoBar::getRaised() const
{
	return m_raised;
}
//---------------------------------------------------------
void InfoBar::initTextBoxes(int index, std::string str, int height)
{
	auto font = SingleTone::GetInstance().getFont();
	sf::Vector2f position = { WINDOW_LENGTH - INFOBAR_LENGTH + 200, float(50 + height) };
	m_IBtextBoxes[index].setFont(*font);
	m_IBtextBoxes[index].setCharacterSize(30);
	m_IBtextBoxes[index].getLetterSpacing();
	m_IBtextBoxes[index].setString(str+"0");
	m_IBtextBoxes[index].setFillColor(sf::Color::Black);
	m_IBtextBoxes[index].setOutlineColor(sf::Color::Yellow);
	m_IBtextBoxes[index].setOutlineThickness(1);
	m_IBtextBoxes[index].setPosition(position);
	m_IBtextBoxes[index].setOrigin(m_IBtextBoxes[index].getLocalBounds().width / 2,
		m_IBtextBoxes[index].getLocalBounds().height / 2);;
}


