#ifndef F_MANAGER
#define F_MANAGER

#include <fstream>
#include <filesystem>
#include <string>
#include <SFML/Graphics.hpp>
#include <array>
#include <regex>
#include <iostream>

class FileManager
{
public:

	static void openImage(sf::Image& i, std::filesystem::path path);

	static void openTTFfile(sf::Font& f, std::filesystem::path path);

	static void readFromFile(std::string& contener, std::filesystem::path path);

	static void readFromFile(std::vector<std::string>& contener, std::filesystem::path path);

	static void readMapFile(std::array<int, 1620>& a, std::filesystem::path path);

	static void readLevelsFile(std::vector<std::string>& l, std::filesystem::path path);

	static bool validateLevels(std::vector<std::string>& l);

	static bool createFile(std::filesystem::path path, std::string name, std::string content);

	static bool createFile(std::filesystem::path path, std::string name, std::vector<std::string> contents);

	static bool validateMap(std::string mS);

	static bool editFile(std::filesystem::path path, std::vector<std::string> contents);

	static bool editFile(std::filesystem::path path, std::string content);

	static bool checkDir(std::filesystem::path path);

	static bool createDir(std::filesystem::path path, std::string name);
};

#endif //F_MANAGER