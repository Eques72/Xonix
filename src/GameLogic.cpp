#include "GameLogic.h"

	void GameLogic::start()
	{
		player = new Player(6);
		map = new Map();
		kI.setPlayer(player);
		hitPoints = 3;

		FileManager::readLevelsFile(levels, "resources/gameSettings/levels.txt");
		
		setUpNextLevel();

		run();

	}

	void GameLogic::setUpNextLevel() 
	{
		getLevelInformation();

		player->revivePlayer();
		map->resetMap();

		enemies.clear();


		for (int q = 0; q < levelInfo[2]; q++)
			enemies.push_back(std::make_unique<DefaultEnemy>(500 + q * 30, 500, 3, 1));
		for (int q = 0; q < levelInfo[3]; q++)
			enemies.push_back(std::make_unique<DestroyerEnemy>(0, 0, 2, 2));
		for (int q = 0; q < levelInfo[4]; q++)
			enemies.push_back(std::make_unique<HunterEnemy>(0, 0, 2, 2, player));
		for (int q = 0; q < levelInfo[5]; q++);
		//TO DO
		for (int q = 0; q < levelInfo[6]; q++);
		//TO DO
	}

	void GameLogic::getLevelInformation() 
	{
		levelInfo.clear();
		std::string tmpNum;
		for (auto c : levels[currentLevel])
		{
			if (c != ';')
				tmpNum.push_back(c);
			else
			{
				levelInfo.push_back(std::stoi(tmpNum));
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

		kI.checkKeyboardImput();
		player->move(map);

		if (player->getConquestState())
		{
			std::vector<int> t;
			for (int q = 0; q < enemies.size(); q++)
				t.push_back(enemies[q]->getIndexOfTile());
			player->conquer(map, t);
		}
		for (int q = 0; q < enemies.size(); q++)
			enemies[q]->move(map);

	}


	void GameLogic::run()
	{
		while (winG.getWindow().isOpen()) 
		{
			sf::Event event;
			while (winG.getWindow().pollEvent(event))
				if (event.type == sf::Event::Closed)
					winG.getWindow().close();

			if (checkGameOverConditions())
				deathProc();
			if (hitPoints <= 0)
				winG.getWindow().close();

			if(checkLevelCompletion())
			{
				++currentLevel;
				if(hitPoints <= 5)
					++hitPoints;
				setUpNextLevel();
			}

			calculateLogic();

			winG.getWindow().clear();
			drawEntities();
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
	}
