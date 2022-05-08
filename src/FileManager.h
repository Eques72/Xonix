#pragma once

#include <fstream>
#include <filesystem>
#include <string>
#include <SFML/Graphics.hpp>
#include <array>

class FileManager
{
public:

	static sf::Image& openImage(std::filesystem::path path)
	{
		sf::Image i;
		i.loadFromFile(path.string());
		return i;
	}

	static void readFromFile(std::string& contener, std::filesystem::path path)
	{
		std::ifstream stream(path.string());
		if (stream.is_open())
		{
			std::string tmp;
			while (std::getline(stream, tmp))
				contener += tmp;

			stream.close();
		}
	}

	static void readFromFile(std::vector<std::string>& contener, std::filesystem::path path)
	{
		std::ifstream stream(path.string());
		if (stream.is_open())
		{
			std::string tmp;
			while (std::getline(stream, tmp))
				contener.push_back(tmp);

			stream.close();
		}
	}

	/*template <typename T>
	static void readFromFile(T& contener, std::filesystem::path path)
	{
		std::ifstream stream(path.string());
		if(stream.is_open())
		{
			std::string tmp;
			while (std::getline(stream, tmp))
				contener.push_back(tmp);

			stream.close();
		}
	}*/

	static void readMapFile(std::array<int, 1620>& a, std::filesystem::path path)
	{
		std::string tmp;
		int aIndex = 0;

		readFromFile(tmp, path);

		tmp.shrink_to_fit();
		for (int q{ 0 }; q < tmp.size(); q++)
		{
			switch (tmp[q])
			{
			case '1':
				a[aIndex] = 1;
				++aIndex;
				break;
			case '0':
				a[aIndex] = 0;
				++aIndex;
				break;
			case ',':
				break;
			default:
				a[aIndex] = 0;
				++aIndex;
				break;
			}
		}
	}

	static void readLevelsFile(std::vector<std::string>& l, std::filesystem::path path)
	{
		readFromFile(l, path);
	}


	static bool createFile(std::filesystem::path path, std::string name, std::string content)
	{
		if (!std::filesystem::exists(path.string() + "/" + name))
		{
			std::ofstream stream(path.string() + " / " + name);

			stream << content;

			stream.close();
			return true;
		}
		return false;
	}

	static bool createFile(std::filesystem::path path, std::string name, std::vector<std::string> contents)
	{
		if (!std::filesystem::exists(path.string() + "/" + name))
		{
			std::ofstream stream(path.string() + " / " + name);

			for (auto c : contents)
				stream << c << '\n';

			stream.close();
			return true;
		}
		return false;
	}


	static bool editFile(std::filesystem::path path, std::string content)
	{
		if (std::filesystem::exists(path.string()))
		{
			std::ofstream stream(path.string());

			stream << content;

			stream.close();

			return true;
		}
		return false;
	}

	static bool checkDir(std::filesystem::path path)
	{
		if (std::filesystem::exists(path.string()))
			return true;
		return false;
	}

	static bool createDir(std::filesystem::path path, std::string name)
	{
		if (!checkDir(path.string() + "/" + name))
		{
			std::filesystem::create_directory(path.string() + "/" + name);
			return true;
		}
		return false;
	}
};