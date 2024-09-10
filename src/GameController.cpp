#include "GameController.h"


GameController::GameController()
	:m_boardUpdated{false},m_endGame{false}
{
	
}
//---------------------------------------------------------
void GameController::setNewGame()
{
	SingleTone::GetInstance().startTimer();
	m_board.initSticks();
	
	m_infoBar.updateAvailable(m_board.getAvailableSticks());
}
//---------------------------------------------------------
void GameController::setLoadGame()
{
	std::ifstream inpFile;
	inpFile.open(FILE_NAME);
	if (!inpFile.is_open()) {
		throw FormatException("Could Not Open File: 'Data Saved File' ");
	}
	SingleTone::GetInstance().startTimer();
	int totalScore, raised, remain;
	float time;
	std::string line;
	std::getline(inpFile, line);
	auto iss = std::istringstream(line);
	iss >> time >> totalScore >> raised;
	m_board.loadGame(inpFile);
	if (iss.fail() || time > 60 || time < 0 || totalScore>500 || totalScore < 0
		|| raised<0 || raised>20) {
		throw std::invalid_argument("Invalid input format");
	}
	m_board.setUserScore(totalScore);
	m_infoBar.updateAvailable(m_board.getAvailableSticks());
	m_infoBar.setRaised(raised);
	m_infoBar.setGameTime(time);
	m_infoBar.updateRaisedsticks(raised);
	m_infoBar.updateScore(m_board.getUserScore());
	m_infoBar.updateSticksRemaining(m_board.getSticksRemaining());
}
//---------------------------------------------------------

void GameController::RunGame(sf::RenderWindow& window)
{
	sf::Event evnt;
	
	while (window.isOpen()) 
	{
		if (m_boardUpdated)
		{
			sf::sleep(sf::seconds(0.3));
			m_board.resetMarks(window, sf::Color::Black);
			m_boardUpdated = false;
		}
		m_infoBar.updateTime();
		
		
		while (window.pollEvent(evnt))
		{
			GameEvents(window, evnt);
		}
			
		if (timeLeft() || m_board.getSticksRemaining() == 0)
		{
			m_endGame = true;
		}
		GameDraw(window);
		
	}
}
//---------------------------------------------------------
void GameController::handleClick(sf::Vector2f mousePostition, sf::RenderWindow& window)
{
	m_boardStartSize = m_board.getSticksRemaining();
	m_boardUpdated =m_board.UpdateBoard(mousePostition, window);
	auto raised = m_boardStartSize - m_board.getSticksRemaining();
	if (m_boardUpdated) {
		m_infoBar.updateSticksRemaining(m_board.getSticksRemaining());
		m_infoBar.updateRaisedsticks(raised);
		m_infoBar.updateAvailable(m_board.getAvailableSticks());
		m_infoBar.updateScore(m_board.getUserScore());
	}
	if (m_infoBar.hintPressed(mousePostition)) 
	{
		m_board.forClue(window);
	}
	if (m_infoBar.savePressed(mousePostition)) 
	{
		try
		{
			std::ofstream outFile;
			outFile.open(FILE_NAME);
			if (!outFile.is_open()) {
				throw FormatException("Could Not Open File: Data Saved File");
			}
			outFile << m_infoBar.getGameTime()<<" ";
			outFile << m_board.getUserScore()<<" ";
			outFile << m_infoBar.getRaised()<<std::endl;
			m_board.saveData(outFile);
		}
		catch (FormatException& e) 
		{
			SingleTone::GetInstance().showError(e.what(), window);
			sf::sleep(sf::seconds(1));
		}
		catch (const std::exception& e) {
			SingleTone::GetInstance().showError(e.what(), window);
			sf::sleep(sf::seconds(1));
		}
	}
	
}
//---------------------------------------------------------
bool GameController::timeLeft()
{
	auto gameTime = m_infoBar.getGameTime();
	if (gameTime<=0.0)
	{
		return true;
	}
	return false;
}
//----------------------------------------------------------
void GameController::GameDraw(sf::RenderWindow& window)
{
	if (!m_endGame)
	{
		window.clear(sf::Color{ 100,20,30 });
		m_infoBar.DrawinfoBar(window);
		m_board.DrawBoard(window);
		window.display();
	}
	else {
		window.clear(sf::Color{ 100,20,30 });
		SingleTone::GetInstance().showEndScore(m_board.getUserScore(), window);
		sf::sleep(sf::seconds(3));
		window.close();
	}
}
//---------------------------------------------------------
void GameController::GameEvents(sf::RenderWindow& window, sf::Event& evnt)
{
	switch (evnt.type)
	{
	case sf::Event::Closed:
	{
		window.close();
		break;
	}
	case sf::Event::MouseButtonReleased:
	{
		auto mouseLocation = window.mapPixelToCoords
		({ evnt.mouseButton.x, evnt.mouseButton.y });
		handleClick(mouseLocation, window);
		break;
	}
	case sf::Event::MouseMoved:
		auto Location = window.mapPixelToCoords
		({ evnt.mouseMove.x, evnt.mouseMove.y });
		m_infoBar.handleMouseOnHint(Location);
		break;
	}
}


