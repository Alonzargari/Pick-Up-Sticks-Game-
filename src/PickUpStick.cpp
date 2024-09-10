#include "PickUpStick.h"


//---------------------------------------------------------

PickUpStick::PickUpStick(int serial)
	:m_serialStickNumber{serial}
{
	initStickData();
}
PickUpStick::PickUpStick(int serial,int score,float posX,float posY,int angle)
	:m_serialStickNumber{serial},m_StickScore{score},m_angle{angle}
{
	sf::Vector2f pos = { posX,posY };
	auto color = SingleTone::GetInstance().getColor(m_StickScore);
	m_pickUpStick.setSize(sf::Vector2f(STICK_SIZE_WIDTH, STICK_SIZE_LENGTH));
	m_pickUpStick.setPosition(pos);
	m_pickUpStick.setFillColor(color);
	m_pickUpStick.setRotation(m_angle);
	m_pickUpStick.setOrigin(m_pickUpStick.getSize().x / 2, m_pickUpStick.getSize().y / 2);
	m_pickUpStick.setOutlineColor(sf::Color::Black);
	m_pickUpStick.setOutlineThickness(4);
}

//---------------------------------------------------------
void PickUpStick::DrawPickUpStick(sf::RenderWindow& window)
{
	window.draw(m_pickUpStick);
}

//---------------------------------------------------------
sf::Vector2f PickUpStick::getEndPoint() const
{
	auto endPoint = (m_pickUpStick.getTransform().transformPoint(m_pickUpStick.getPoint(0)),
		m_pickUpStick.getTransform().transformPoint(m_pickUpStick.getPoint(1)));
	return endPoint;
}
//---------------------------------------------------------
sf::Vector2f PickUpStick::getStartPoint() const
{
	auto StartPoint = (m_pickUpStick.getTransform().transformPoint(m_pickUpStick.getPoint(2)),
		m_pickUpStick.getTransform().transformPoint(m_pickUpStick.getPoint(3)));
	return StartPoint;
}
//---------------------------------------------------------
int PickUpStick::getScore() const
{
	return m_StickScore;
}
//---------------------------------------------------------
void PickUpStick::increaseBounders(const std::shared_ptr<PickUpStick>& boundedStick)
{
	m_Bounders.emplace_back(boundedStick);
}
//---------------------------------------------------------
bool PickUpStick::BoundersIsEmpty() const
{
	return m_Bounders.empty();
}
//---------------------------------------------------------
bool PickUpStick::Pressed(sf::Vector2f mousePosition)
{
	auto transformedPoint = m_pickUpStick.getTransform().getInverse().transformPoint(mousePosition);
	return m_pickUpStick.getLocalBounds().contains(transformedPoint);
}
//---------------------------------------------------------
void PickUpStick::markBounders(sf::RenderWindow& window, sf::Color color)
{
	for (const auto& stick : m_Bounders)
	{
		stick->globalColoring(color);
		stick->DrawPickUpStick(window);
	}
}
//---------------------------------------------------------
void PickUpStick::globalColoring(const sf::Color& color)
{
	m_pickUpStick.setOutlineColor(color);
	m_pickUpStick.setOutlineThickness(4);
}
//---------------------------------------------------------
void PickUpStick::UpdateBounders(const std::shared_ptr<PickUpStick>& boundedStick)
{
	auto it = std::find_if(m_Bounders.begin(), m_Bounders.end(), 
		[boundedStick](auto stick) {return stick == boundedStick;});
	if (!(it == m_Bounders.end()))
	{
		m_Bounders.erase(it);
	}
}
//---------------------------------------------------------
void PickUpStick::writeData(std::ofstream& outFile)
{

	outFile << m_StickScore<<" ";
	outFile << m_pickUpStick.getPosition().x<<" ";
	outFile << m_pickUpStick.getPosition().y<<" ";
	outFile << m_angle;
	outFile << std::endl;

}
//---------------------------------------------------------
void PickUpStick::initStickData()
{
		int stickColor = rand() % 5;
		auto stickData = SingleTone::GetInstance().getStickData(Colors_t(stickColor));
		int minLength = 200;
		int maxLength = WINDOW_LENGTH - 500;
		int minHeight = 200;
		int maxHeight = WINDOW_HEIGHT - 200;
		int startX = minLength + std::rand() % (maxLength- minLength + 1);
		int startY = minHeight + std::rand() % (maxHeight - minHeight + 1);
		m_angle = std::rand() % 361;
		m_pickUpStick.setSize(sf::Vector2f(STICK_SIZE_WIDTH,STICK_SIZE_LENGTH));
		m_pickUpStick.setFillColor(stickData._color);
		m_pickUpStick.setRotation(m_angle);
		m_pickUpStick.setPosition(sf::Vector2f(startX,startY));
		m_pickUpStick.setOrigin(m_pickUpStick.getSize().x/ 2, m_pickUpStick.getSize().y / 2);
		m_pickUpStick.setOutlineColor(sf::Color::Black);
		m_pickUpStick.setOutlineThickness(4);
		m_StickScore = stickData._score;
}
//---------------------------------------------------------
bool operator==(const PickUpStick& obj1, const PickUpStick& obj2)
{
	return obj1.m_serialStickNumber==obj2.m_serialStickNumber;
}
