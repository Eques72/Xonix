#ifndef F_MANAGER
#define F_MANAGER

#include <fstream>
#include <filesystem>
#include <string>
#include <SFML/Graphics.hpp>
#include <array>
#include <regex>
#include <iostream>
#include <memory>

/// <summary>
/// Manages file writing/reading operations and distributes resources
/// </summary>
class FileManager
{
private:
	static std::unique_ptr<sf::Texture> player_tx;
	static std::unique_ptr<sf::Texture> blue_enemy_tx;
	static std::unique_ptr<sf::Texture> green_enemy_tx;
	static std::unique_ptr<sf::Texture> background_tx;
	static std::unique_ptr<sf::Texture> wall_tx;
	static std::unique_ptr<sf::Texture> button_tx;
	static std::unique_ptr<sf::Font> font_ttl;

	static int chosedBackground;//1 for menu bck, 0 for game bck

	//class object can not be created
	FileManager() {};
public:

	const static int PLAYER_TX = 0;
	const static int BLUE_ENEMY_TX = 1;
	const static int GREEN_ENEMY_TX = 2;
	const static int BACKGROUND_TX = 3;
	const static int WALL_TX = 4;
	const static int BUTTON_TX = 5;
	const static int FONT_TTL = 6;

	/// <summary>
	/// Get reference to choosen texture
	/// </summary>
	static sf::Texture& get_tx(int type);

	/// <summary>
	/// Get reference to choosen font
	/// </summary>
	static sf::Font& get_ttl(int type);

	/// <summary>
	/// Reads resources needed for game graphics form files
	/// </summary>
	static void setUpResources();

	/// <summary>
	/// Releases dymiamicly allocated resources
	/// </summary>
	static void resetResources();

	/// <summary>
	/// Swaps contents of background_tx variable with difrent image
	/// </summary>
	/// <param name="swap">If set to 1 - swaps to menu background, if set to 0 - swaps to game screen background</param>
	static void swapBackgroundImage(int swap);

	/// <summary>
	/// Reads a png/img/bmp file
	/// </summary>
	static sf::Image openImage(std::filesystem::path path);

	/// <summary>
	/// Reads a .TTF file
	/// </summary>
	static void openTTFfile(sf::Font& f, std::filesystem::path path);

	/// <summary>
	/// Reads form file
	/// </summary>
	static void readFromFile(std::string& contener, std::filesystem::path path);

	/// <summary>
	/// Reads form file
	/// </summary>
	static void readFromFile(std::vector<std::string>& contener, std::filesystem::path path);

	/// <summary>
	/// Reads specific map config file and invokes validation method, fixes contents if needed
	/// </summary>
	static void readMapFile(std::array<int, 1620>& a, std::filesystem::path path);

	/// <summary>
	/// Reads specific levels config file and invokes validation method
	/// </summary>
	static void readLevelsFile(std::vector<std::string>& l, std::filesystem::path path);

	/// <summary>
	/// Method checks if contents of levels configuration file matches the format using regex
	/// </summary>
	static bool validateLevels(std::vector<std::string>& l);

	/// <summary>
	/// Creates a new file
	/// </summary>
	static bool createFile(std::filesystem::path path, std::string name, std::string content);

	/// <summary>
	/// Creates a new file
	/// </summary>
	static bool createFile(std::filesystem::path path, std::string name, std::vector<std::string> contents);

	/// <summary>
	/// Method checks if contents of map configuration file matches the format using regex
	/// </summary>
	static bool validateMap(std::string mS);

	/// <summary>
	/// Method checks if contents of save file matches the format using regex
	/// </summary>
	static bool validateSaves(std::vector<std::string> sav);

	/// <summary>
	/// Edits existing file, filles it with new content
	/// </summary>
	static bool editFile(std::filesystem::path path, std::vector<std::string> contents);

	/// <summary>
	/// Edits existing file, filles it with new content
	/// </summary>
	static bool editFile(std::filesystem::path path, std::string content);

	/// <summary>
	/// Check if directory or file exists
	/// </summary>
	static bool checkDir(std::filesystem::path path);

	/// <summary>
	/// Creates directory of a given name under given path
	/// </summary>
	static bool createDir(std::filesystem::path path, std::string name);
};

#endif //F_MANAGER