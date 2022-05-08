#ifndef LOGIC
#define LOGIC

#include "Enemy.h"
#include "DefaultEnemy.h"
#include "DestroyerEnemy.h"
#include "HunterEnemy.h"

#include "Map.h"
#include "Player.h"

#include "KeyboardImput.h"
#include "GWindow.h"
#include "FileManager.h"

#include <memory>
#include <thread>
#include <vector>

#include <random> //is it needed?




class GameLogic
{
	bool gameOver = false;

	Map* map;
	Player* player;
	KeyboardImput kI;
	GWindow winG;

	std::vector<std::shared_ptr<Enemy>> enemies;
	std::vector<std::shared_ptr<Enemy>> nextLevelEnemies;

	std::vector<std::string> levels;
	std::vector<int> levelInfo;
	std::vector<int> nextLevelInfo;
	std::thread nextLevelLoader;

	int hitPoints; //+1 after finished level, -1 if any game over condition met
	int nextLevelIndex = 1;
	int currentLevelIndex = 0;
	static const int maxLevels = 20;
public:
	GameLogic() { start(); };

	void start();
	void run();

	void setUpNextLevel();
	bool checkLevelCompletion();
	void getLevelInformation(int index);
	void prepareNextLevel();

	void calculateLogic();
	bool checkGameOverConditions();

	void deathProc();

	void drawEntities();


	~GameLogic();
};

#endif //LOGIC