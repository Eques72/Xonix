#include "GameLogic.h"

void GameLogic::start()
{
	while (isMenuActive)
	{
		winG.setMenu();

		std::array<bool, 3> menuChoices = winG.displayMenu();
		isMenuActive = menuChoices[2];
	
		gameOver = false;
		isPauseActive = false;
		isDefeatBoxActive = false;
		nextLevelIndex = 2;
		currentLevelIndex =1;

		if (menuChoices[0])
		{
			player = std::make_shared<Player>(6);
			map = std::make_unique<Map>();
			kI.setPlayer(player);
			hitPoints = 3;
			
			std::thread readThread(FileManager::readLevelsFile, std::ref(levels), "resources/gameSettings/levels.txt");

			if (menuChoices[1])
				loadGame();
			
	//		FileManager::readLevelsFile(levels, "resources/gameSettings/levels.txt");
			readThread.join();
			prepareNextLevel(currentLevelIndex);
			setUpNextLevel();

//			++currentLevelIndex;
//			++nextLevelIndex;
			if(currentLevelIndex < 20)
				nextLevelLoader = std::thread(&GameLogic::prepareNextLevel,  this, nextLevelIndex);

			winG.setInfoPanel(0, 900, winG.width, winG.height - 900);

			run();
		}
	}
}

void GameLogic::prepareNextLevel(int lvlIndex)
{
//	getLevelInformation(nextLevelIndex);
	getLevelInformation(lvlIndex);

	for (int q = 0; q < nextLevelInfo[2]; q++)
		nextLevelEnemies.push_back(std::make_shared<DefaultEnemy>(500 + q * 30, 500, 3, 1));
	for (int q = 0; q < nextLevelInfo[3]; q++)
		nextLevelEnemies.push_back(std::make_shared<DestroyerEnemy>(0, 0, 2, 2));
	for (int q = 0; q < nextLevelInfo[4]; q++)
		nextLevelEnemies.push_back(std::make_shared<HunterEnemy>(0, 0, 2, 2, player));
	for (int q = 0; q < nextLevelInfo[5]; q++);
	//TO DO
	for (int q = 0; q < nextLevelInfo[6]; q++);
	//TO DO
}

void GameLogic::setUpNextLevel()
{
	levelInfo = nextLevelInfo;
	player->revivePlayer();
	map->resetMap();

	enemies.clear();
	enemies = nextLevelEnemies;
	nextLevelEnemies.clear();
}

void GameLogic::getLevelInformation(int index)
{
	nextLevelInfo.clear();
	std::string tmpNum;
	for (auto c : levels[index])
	{
		if (c != ';')
			tmpNum.push_back(c);
		else
		{
			nextLevelInfo.push_back(std::stoi(tmpNum));
			tmpNum = "";
		}
	}
}

bool GameLogic::checkLevelCompletion()
{
	if (map->getProggres() >= levelInfo[1])
		return true;
	return false;
}

void GameLogic::drawEntities()
{
	map->draw(winG.getWindow());
	player->draw(winG.getWindow());

	for (int q = 0; q < enemies.size(); q++)
		enemies[q]->draw(winG.getWindow());
}



void GameLogic::calculateLogic()
{


	player->move(*map);

	std::vector<std::thread> threads;

	if (player->getConquestState())
	{
		std::vector<int> t;
		for (int q = 0; q < enemies.size(); q++)
			t.push_back(enemies[q]->getIndexOfTile());
		player->conquer(*map, t);
	}
	for (int q = 0; q < enemies.size(); q++)
		threads.emplace_back(&Enemy::move, enemies[q].get(), std::ref(*map));
	for (auto& t : threads)
		t.join();
}


void GameLogic::run()
{
	while (!gameOver && winG.getWindow().isOpen())
	{


		sf::Event event;
		while (winG.getWindow().pollEvent(event))
			if (event.type == sf::Event::Closed)
			{
				saveGame();
				winG.getWindow().close();
			}
		///////////////////////////////////////////////////////////////////
		kI.checkKeyboardImput(isPauseActive);
		if (isPauseActive && winG.pasuseBoxInitialized == false)
		{
			winG.setPauseBox();
			winG.pasuseBoxInitialized = true;
		}

		if (!isDefeatBoxActive && !isPauseActive && !isGameCompleted)
		{

			if (checkGameOverConditions())
				deathProc();
			if (hitPoints <= 0)
			{
				winG.setDefeatBox();
				isDefeatBoxActive = true;
			}
			else if (checkLevelCompletion())
			{
				++currentLevelIndex;
				++nextLevelIndex;
				if (hitPoints <= 5)
					++hitPoints;

				if (currentLevelIndex <= maxLevels)
				{
					nextLevelLoader.join();
					setUpNextLevel();
					//	nextLevelLoader = std::thread(&GameLogic::prepareNextLevel, this);
					nextLevelLoader = std::thread(&GameLogic::prepareNextLevel, this, nextLevelIndex);
				}
				else
				{
					isGameCompleted = true;
					winG.setVictoryBox();
				}
			}

			calculateLogic();
		}
		///////////////////////////////////////////////////////////////////
		winG.getWindow().clear();
		{		
			winG.displayInfoPanel(currentLevelIndex, hitPoints, map->getProggres(), levelInfo[1]);
			drawEntities();
		
			if ((isDefeatBoxActive || isGameCompleted) && !winG.displayTextBox().first)
			{
				isDefeatBoxActive = false;
				isGameCompleted = false;
				gameOver = true;
				currentLevelIndex = 1;
				nextLevelIndex = 2;
				hitPoints = 3;
				saveGame();

				if(nextLevelLoader.joinable())
					nextLevelLoader.join();
				nextLevelEnemies.clear();

				winG.demandCredits = true;
			}
			if (isPauseActive)
			{
				std::pair response = winG.displayTextBox();
				if (!response.first)
				{
					if (response.second == 1)
					{
						gameOver = true;
						if (nextLevelLoader.joinable())
							nextLevelLoader.join();
						nextLevelEnemies.clear();

						saveGame();
					}
					winG.pasuseBoxInitialized = false;
					isPauseActive = false;
				}
			}
		}
		winG.getWindow().display();

	}
}

bool GameLogic::checkGameOverConditions()
{
	if (player->checkTailCollisons(*map))
		return true;

	for (int q = 0; q < enemies.size(); q++)
		if (enemies[q]->checkTailCollisons(*map))
			return true;

	for (int q = 0; q < enemies.size(); q++)
		if (enemies[q]->chcekEntityCollions(*player))
			return true;

	return false;
}

void GameLogic::deathProc()
{
	--hitPoints;
	player->revivePlayer();
	map->clearTail();
}

void GameLogic::saveGame()
{
	if (!FileManager::checkDir("resources/Saves"))
		FileManager::createDir("resources","Saves");
	if(!FileManager::createFile("resources/Saves", "gameSave.txt", std::vector<std::string>{std::to_string(currentLevelIndex), std::to_string(hitPoints)}))
		FileManager::editFile("resources/Saves/gameSave.txt", std::vector<std::string>{std::to_string(currentLevelIndex), std::to_string(hitPoints)});

}

void GameLogic::loadGame()
{
	if (FileManager::checkDir("resources/Saves/gameSave.txt"))
	{
		std::vector<std::string> sLvl{};
		FileManager::readFromFile(sLvl, "resources/Saves/gameSave.txt");

		if (sLvl.size() == 2)
		{
			currentLevelIndex = std::stoi(sLvl[0]);
			nextLevelIndex = 1 + currentLevelIndex;
			hitPoints = std::stoi(sLvl[1]);
		}
	}
}

GameLogic::~GameLogic()
{
	if (nextLevelLoader.joinable())
		nextLevelLoader.join();
}
