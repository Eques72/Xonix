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


class GameLogic
{
	bool gameOver = false;
	bool isMenuActive = true;
	bool isPauseActive = false;
	bool isDefeatBoxActive = false;
	bool isGameCompleted = false;


	std::shared_ptr<Map> map;
	std::shared_ptr<Player> player;
	KeyboardImput kI;
	GWindow winG;

	std::vector<std::shared_ptr<Enemy>> enemies;
	std::vector<std::shared_ptr<Enemy>> nextLevelEnemies;

	std::vector<std::string> levels;
	std::vector<int> levelInfo;
	std::vector<int> nextLevelInfo;
	std::thread nextLevelLoader;

	int hitPoints; //+1 after finished level, -1 if any game over condition met
	int nextLevelIndex = 2;
	int currentLevelIndex = 1;
	static const int maxLevels = 20;
public:
	GameLogic() { start(); };

	void start();
	void run();
	void initializeGame(bool doLoadGame);

	void setUpNextLevel();
	bool checkLevelCompletion();
	void getLevelInformation(int index);
	void prepareNextLevel(int lvlIndex);

	void calculateLogic();
	bool checkLivesLossConditions();

	void handleEvents();
	void handleGameConditions();

	void deathProc();

	void drawEntities();
	void drawPanels();

	void saveGame();
	void loadGame();

	void drop(int XY); //wype³nia plamami miejsca puste z którymi maj¹ styccznoœæ przeciwnicy
	void conquer(std::vector<int> positions);

	~GameLogic();
};

#endif //LOGIC