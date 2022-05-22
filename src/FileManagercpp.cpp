#include "FileManager.h"

void FileManager::openImage(sf::Image& i, std::filesystem::path path)
{
	try
	{
		if (!checkDir(path))
			throw(std::string("Unable to find image under path: " + path.string() + " \n"));

		i.loadFromFile(path.string());
	}
	catch (std::string& e)
	{
		std::cout << e;
	}
}

void FileManager::openTTFfile(sf::Font& f, std::filesystem::path path)
{
	try
	{
		if (!checkDir(path))
			throw(std::string("Unable to find TTF file under path: " + path.string() + " \n"));

		f.loadFromFile(path.string());
	}
	catch (std::string& e)
	{
		std::cout << e;
	}
}

void FileManager::readFromFile(std::string& contener, std::filesystem::path path)
{
	std::ifstream stream(path.string());
	try
	{
		if (!stream.is_open())
			throw(std::string("Unable to read file from path: " + path.string() + "\n"));

		std::string tmp;
		while (std::getline(stream, tmp))
			contener += tmp;

		stream.close();
	}
	catch (std::string& e)
	{
		std::cout << e;
	}
}

void FileManager::readFromFile(std::vector<std::string>& contener, std::filesystem::path path)
{
	std::ifstream stream(path.string());
	try
	{
		if (!stream.is_open())
			throw(std::string("Unable to read file from path: " + path.string() + "\n"));


		std::string tmp;
		while (std::getline(stream, tmp))
			contener.push_back(tmp);

		stream.close();
	}
	catch (std::string& e)
	{
		std::cout << e;
	}
}

void FileManager::readMapFile(std::array<int, 1620>& a, std::filesystem::path path)
{
	std::string tmp;
	int aIndex = 0;

	readFromFile(tmp, path);
	tmp.shrink_to_fit();

	if (!validateMap(tmp))
		for (int q{ 0 }; q < tmp.size(); q++)
			if (tmp[q] != '0' && tmp[q] != '1' && tmp[q] != ',')
				tmp[q] = '0';

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
			break;
		}
	}
}

void FileManager::readLevelsFile(std::vector<std::string>& l, std::filesystem::path path)
{
	readFromFile(l, path);

	try
	{
		if (!validateLevels(l))
		{
			std::string s{ "Can not read game settings properly, reinstall game \n" };
			throw(s);
		}
	}
	catch (std::string& e)
	{
		std::cout << e;
	}
}

bool FileManager::validateLevels(std::vector<std::string>& l)
{
	std::regex r1("[0-9][0-9];");
	std::regex r2("[0-9]{1,2};[(0-9]{2};[0-5];[0-5];[0-5];[0-5];[0-5];");
	std::smatch mS;

	if (std::regex_match(l[0], r1))
	{
		for (int q{ 0 }; q < std::stoi(l[0]); q++)
			if (!std::regex_match(l[q + 1], r2))
				return false;

		return true;
	}
	return false;
}

bool FileManager::createFile(std::filesystem::path path, std::string name, std::string content)
{
	if (!std::filesystem::exists(path.string() + "/" + name))
	{
		std::ofstream stream(path.string() + "/" + name);

		stream << content;

		stream.close();
		return true;
	}
	return false;
}

bool FileManager::createFile(std::filesystem::path path, std::string name, std::vector<std::string> contents)
{
	if (!std::filesystem::exists(path.string() + "/" + name))
	{
		std::ofstream stream(path.string() + "/" + name);

		for (auto c : contents)
			stream << c << '\n';

		stream.close();
		return true;
	}
	return false;
}

bool FileManager::validateMap(std::string mS)
{
	std::regex r("[01,]+");

	if (std::regex_match(mS, r))
		return true;
	return false;
}

bool FileManager::editFile(std::filesystem::path path, std::vector<std::string> contents)
{
	if (std::filesystem::exists(path.string()))
	{
		std::ofstream stream(path.string());

		for (auto c : contents)
			stream << c << '\n';

		stream.close();
		return true;
	}
	return false;
}

bool FileManager::editFile(std::filesystem::path path, std::string content)
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

bool FileManager::checkDir(std::filesystem::path path)
{
	if (std::filesystem::exists(path.string()))
		return true;
	return false;
}

bool FileManager::createDir(std::filesystem::path path, std::string name)
{
	if (!checkDir(path.string() + "/" + name))
	{
		std::filesystem::create_directory(path.string() + "/" + name);
		return true;
	}
	return false;
}