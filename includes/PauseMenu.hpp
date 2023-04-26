#include "includes/UI.hpp"

using std::cout;
using std::endl;

class PauseMenu : UI_Element
{
public:
	PauseMenu(sf::RenderWindow& window);

	void update(sf::RenderWindow& window) override;

	void handleMouseClick(sf::RenderWindow &window) override;

	bool isScreenPaused(void);

	void pause(sf::RenderWindow& window);

private:
	//pause assets
	sf::CircleShape pauseButton;
	sf::RectangleShape pauseBackground;
	sf::RectangleShape resumeButton;
	sf::RectangleShape pauseBars[2];

	//Other required Functions
	bool isPaused;
	
};