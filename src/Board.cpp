#include "Board.h"


Board::Board()
	:m_UserScore{0}
{
	std::srand(static_cast<unsigned int>(std::time(NULL)));
}
//---------------------------------------------------------
void Board::forClue(sf::RenderWindow&window)
{
	
	for (const auto& stick : m_AvailableSticks) 
	{
		stick->globalColoring(sf::Color::Cyan);
		stick->DrawPickUpStick(window);
		window.display();
		sf::sleep(sf::seconds(0.5));
		stick->globalColoring(sf::Color::Black);
		stick->DrawPickUpStick(window);
		window.display();
	}
}
//---------------------------------------------------------
bool Board::doIntersect(sf::Vector2f p1, sf::Vector2f q1, sf::Vector2f p2, sf::Vector2f q2)
{
	// Find the four orientations needed for general and 
// special cases 
	int o1 = orientation(p1, q1, p2);
	int o2 = orientation(p1, q1, q2);
	int o3 = orientation(p2, q2, p1);
	int o4 = orientation(p2, q2, q1);

	// General case 
	if (o1 != o2 && o3 != o4)
		return true;

	// Special Cases 
	// p1, q1 and p2 are collinear and p2 lies on segment p1q1 
	if (o1 == 0 && onSegment(p1, p2, q1)) return true;

	// p1, q1 and q2 are collinear and q2 lies on segment p1q1 
	if (o2 == 0 && onSegment(p1, q2, q1)) return true;

	// p2, q2 and p1 are collinear and p1 lies on segment p2q2 
	if (o3 == 0 && onSegment(p2, p1, q2)) return true;

	// p2, q2 and q1 are collinear and q1 lies on segment p2q2 
	if (o4 == 0 && onSegment(p2, q1, q2)) return true;

	return false;// Doesn't fall in any of the above cases ;
}
//---------------------------------------------------------
//// To find orientation of ordered triplet (p, q, r). 
//// The function returns following values 
//// 0 --> p, q and r are collinear 
//// 1 --> Clockwise 
//// 2 --> Counterclockwise 
int Board::orientation(sf::Vector2f p, sf::Vector2f q, sf::Vector2f r)
{
	int val = (q.y - p.y) * (r.x - q.x) -
		(q.x - p.x) * (r.y - q.y);

	if (val == 0) return 0;  // collinear 

	return (val > 0) ? 1 : 2; // clock or counterclock wise ;
}
//---------------------------------------------------------
bool Board::onSegment(sf::Vector2f p, sf::Vector2f q, sf::Vector2f r)
{
	if (q.x <= std::max(p.x, r.x) && q.x >= std::min(p.x, r.x) &&
		q.y <= std::max(p.y, r.y) && q.y >= std::min(p.y, r.y))
		return true;

	return false;
}
//---------------------------------------------------------
void Board::updateStickIntersections(const std::shared_ptr<PickUpStick>& newStick)
{
	for (const auto& stick : m_pickUpSticks)
	{
		if (doIntersect(stick->getStartPoint(), stick->getEndPoint(), newStick->getStartPoint(), newStick->getEndPoint()))
		{
			stick->increaseBounders(newStick);
		}
	}
}
//---------------------------------------------------------
bool Board::UpdateBoard(sf::Vector2f mousePosition, sf::RenderWindow& window)
{

	auto itToErase = std::find_if(m_pickUpSticks.rbegin(), m_pickUpSticks.rend(),
		[&mousePosition](auto& stick) {return stick->Pressed(mousePosition);});
	if (itToErase == m_pickUpSticks.rend()) {
		return false;
	}
	else {
		if ((*itToErase)->BoundersIsEmpty())
		{ 
			m_UserScore += (*itToErase)->getScore();

			auto baseIt = std::next(itToErase).base();
			updatingContainers(baseIt);
			return true;
		}
		else {
			(*itToErase)->markBounders(window,sf::Color::Cyan);
			return true;
		}
	}

}
//---------------------------------------------------------
void Board::DrawBoard(sf::RenderWindow& window)
{
	std::for_each(m_pickUpSticks.begin(), m_pickUpSticks.end(), [&window](auto& stick) {stick->DrawPickUpStick(window);});
}
//---------------------------------------------------------
void Board::updateAvailable(const std::shared_ptr<PickUpStick>& newStick)
{	
	if (newStick->BoundersIsEmpty()) {
		m_AvailableSticks.insert(newStick);
	}
	
}

//---------------------------------------------------------
/*after bounders sticks were marked the board reset them*/
void Board::resetMarks(sf::RenderWindow& window,sf::Color color)
{
	std::for_each(m_pickUpSticks.begin(), m_pickUpSticks.end(),
		[&window, color](auto& stick) {stick->markBounders(window, sf::Color::Black);});
}
//---------------------------------------------------------
void Board::initSticks()
{
	for (int i = 0; i < 20;i++)
	{
		auto stick = std::make_shared<PickUpStick>(i);
		updateStickIntersections(stick);
		m_pickUpSticks.emplace_back(stick);
	}
	for (const auto& stick : m_pickUpSticks)
	{
		if (stick->BoundersIsEmpty())
		{
			m_AvailableSticks.insert(stick);
		}
	}
}
//---------------------------------------------------------
int Board::getSticksRemaining() const
{
	return m_pickUpSticks.size();
}
//---------------------------------------------------------
int Board::getAvailableSticks() const
{
	return m_AvailableSticks.size();
}
//---------------------------------------------------------
int Board::getUserScore() const
{
	return m_UserScore;
}
//---------------------------------------------------------
void Board::saveData(std::ofstream& outFile)
{
	std::for_each(m_pickUpSticks.begin(),
		m_pickUpSticks.end(), [&outFile](auto& stick) {stick->writeData(outFile);});
}
//---------------------------------------------------------
void Board::loadGame(std::ifstream& inpFile)
{
	int score, angle;
	float posX, posY;
	std::string line;
	int index = 0;
	while (std::getline(inpFile, line)) {
		auto iss = std::istringstream(line);
		iss >> score >> posX >> posY >> angle;
		if (iss.fail() || score > 500 || posX<200 || posX>WINDOW_LENGTH - 500 
			|| posY < 200||posY>WINDOW_HEIGHT - 200||angle<0||angle>361) 
		{
			throw std::invalid_argument("Invalid input format");
		}
		auto stick = std::make_shared<PickUpStick>(index, score, posX, posY, angle);
		updateStickIntersections(stick);
		m_pickUpSticks.emplace_back(stick);
	}
	for (const auto& stick : m_pickUpSticks)
	{
		if (stick->BoundersIsEmpty())
		{
			m_AvailableSticks.insert(stick);
		}
	}
}
//---------------------------------------------------------
/*after loading a game the score need to continue from the last point */
void Board::setUserScore(int score)
{
	m_UserScore = score;
}
//---------------------------------------------------------
void Board::updatingContainers(std::list<std::shared_ptr < PickUpStick>>::const_iterator toErase)
{
	
	for (const auto& stick : m_pickUpSticks) {
		stick->UpdateBounders(*toErase);
	}
	
	m_pickUpSticks.erase(toErase);
	m_AvailableSticks.clear();
	for (const auto& stick : m_pickUpSticks) 
	{
		updateAvailable(stick);
		
	}	
}
//---------------------------------------------------------
