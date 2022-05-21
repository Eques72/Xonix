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
		nextLevelIndex = 1;
		currentLevelIndex = 0;

		if (menuChoices[0])
		{
			player = new Player(6);
			map = new Map();
			kI.setPlayer(player);

			if (menuChoices[1]);
			//LOAD GAME

			hitPoints = 3;
			FileManager::readLevelsFile(levels, "resources/gameSettings/levels.txt");
			prepareNextLevel();
			setUpNextLevel();

			++currentLevelIndex;
			++nextLevelIndex;
			nextLevelLoader = std::thread(&GameLogic::prepareNextLevel, this);

			winG.setInfoPanel(0, 900, winG.width, winG.height - 900);

			run();
		}
	}
}

void GameLogic::prepareNextLevel()
{
	getLevelInformation(nextLevelIndex);

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


	player->move(map);

	std::vector<std::thread> threads;

	if (player->getConquestState())
	{
		std::vector<int> t;
		for (int q = 0; q < enemies.size(); q++)
			t.push_back(enemies[q]->getIndexOfTile());
		player->conquer(map, t);
	}
	for (int q = 0; q < enemies.size(); q++)
		threads.emplace_back(&Enemy::move, enemies[q].get(), std::ref(map));
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
				winG.getWindow().close();

		///////////////////////////////////////////////////////////////////
		kI.checkKeyboardImput(isPauseActive);
		if (isPauseActive && winG.pasuseBoxInitialized == false)
		{
			winG.setPauseBox();
			winG.pasuseBoxInitialized = true;
		}

		if (!isDefeatBoxActive && !isPauseActive)
		{

			if (checkGameOverConditions())
				deathProc();
			if (hitPoints <= 0)
			{
				winG.setDefeatBox();
				isDefeatBoxActive = true;
				//winG.displayDefeatBox();
				//TO BE REPLACED TO DO
				//winG.getWindow().close();
			}
			else if (checkLevelCompletion())
			{
				++currentLevelIndex;
				++nextLevelIndex;
				if (hitPoints <= 5)
					++hitPoints;

				nextLevelLoader.join();
				setUpNextLevel();
				nextLevelLoader = std::thread(&GameLogic::prepareNextLevel, this);
			}

			calculateLogic();
		}
		///////////////////////////////////////////////////////////////////
		winG.getWindow().clear();
		{		
			winG.displayInfoPanel(currentLevelIndex, hitPoints, map->getProggres(), levelInfo[1]);
			drawEntities();
		
			if (isDefeatBoxActive && !winG.displayTextBox())
			{
				isDefeatBoxActive = false;
				gameOver = true;
				if(nextLevelLoader.joinable())
					nextLevelLoader.join();
				nextLevelEnemies.clear();
			}
			if (isPauseActive && !winG.displayTextBox())
			{
				winG.pasuseBoxInitialized = false;
				isPauseActive = false;
			}
		}
		winG.getWindow().display();

	}
}

bool GameLogic::checkGameOverConditions()
{
	if (player->checkTailCollisons(map))
		return true;

	for (int q = 0; q < enemies.size(); q++)
		if (enemies[q]->checkTailCollisons(map))
			return true;

	for (int q = 0; q < enemies.size(); q++)
		if (enemies[q]->chcekEntityCollions(player))
			return true;

	return false;
}

void GameLogic::deathProc()
{
	--hitPoints;
	player->revivePlayer();
	map->clearTail();
}

GameLogic::~GameLogic()
{
	delete player;
	delete map;

	if (nextLevelLoader.joinable())
		nextLevelLoader.join();
}
