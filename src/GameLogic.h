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
#include <vector>

#include <random>

class GameLogic
{
	bool gameOver = false;

	Map* map;
	Player* player;
	KeyboardImput kI;
	GWindow winG;

	std::vector<std::unique_ptr<Enemy>> enemies;
	std::vector<std::string> levels;
	std::vector<int> levelInfo; 
	int hitPoints; //+1 after finished level, -1 if any game over condition met
	int currentLevel = 1;
	static const int maxLevels = 20;

public:
	GameLogic() { start(); };

	void start();
	void run();

	void setUpNextLevel();
	bool checkLevelCompletion();
	void getLevelInformation();

	void calculateLogic();
	bool checkGameOverConditions();

	void deathProc();

	void drawEntities();


	~GameLogic();
};

#endif //LOGIC