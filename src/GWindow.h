#ifndef G_WINDOW
#define G_WINDOW

#include <memory>
#include <SFML/Graphics.hpp>
#include "InfoPanel.h"
#include "Menu.h"
#include "TextBox.h"
#include "FileManager.h"

/// <summary>
/// Class manages main game window with usage of SFML
/// </summary>
class GWindow
{
	sf::RenderWindow window;

	std::unique_ptr<Menu> menu;
	std::unique_ptr<InfoPanel> iP;
	std::unique_ptr<TextBox> tB;

	/// <summary>
	/// Method sets basic window parameters, fixed number of frames per second is equeal to 60
	/// </summary>
	void config();

	/// <summary>
	/// Methos sets a icon of an app, takes needed png form file
	/// </summary>
	void setGameIcon();

public:
	bool pasuseBoxInitialized = false;
	bool demandCredits = false;

	const static int width{ 1620 };
	const static int height{ 1100 }; 

	GWindow();

	/// <summary>
	/// Method initializes a Menu object
	/// </summary>
	void setMenu();

	/// <summary>
	/// Releases memory taken by memory instance
	/// </summary>
	void deleteMenu();

	/// <summary>
	/// Methot invokes a menus metod to draw, check buttons statement
	/// </summary>
	/// <returns>Passes menu choices, see menu documentation</returns>
	std::array<bool, 3> displayMenu();

	/// <summary>
	/// Returns a reference to window variable
	/// </summary>
	sf::RenderWindow& getWindow();

	/// <summary>
	/// Sets up a text box configured as: defeat information box
	/// </summary>
	void setDefeatBox();

	/// <summary>
	/// Sets up a text box configured as: pause box
	/// </summary>
	void setPauseBox();
	
	/// <summary>
	/// Sets up a text box configured as: victory information box
	/// </summary>
	void setVictoryBox();
	
	/// <summary>
	/// displays active text box, invokes drawing method of the box 
	/// </summary>
	void displayTextBox();

	/// <summary>
	/// Asks for active text box's buttons state
	/// </summary>
	/// <returns></returns>
	std::pair<bool, int> getTextBoxResponse();

	/// <summary>
	/// Sets up info panel
	/// </summary>
	/// <param name="_x">Upper left corner x coordinate</param>
	/// <param name="_y">Upper left corner y coordinate</param>
	/// <param name="_w">panel width</param>
	/// <param name="_h">panel height</param>
	void setInfoPanel(int _x, int _y, int _w, int _h);
	
	/// <summary>
	/// Displays info panel and actualises its data
	/// </summary>
	void displayInfoPanel(int level, int hp, double percent, double percent_needed);
};

#endif //G_WINDOW

