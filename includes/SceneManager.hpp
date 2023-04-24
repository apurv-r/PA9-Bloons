#define RUNMENUCONTROL 1
#define RUNGAMECONTROL 2
#define RUNLOSECONTROL 3
#define RUNWINCONTROL 4


#include<SFML/Graphics.hpp>
#include<vector>


class SceneManager
{
public:
	SceneManager() :currentScene(0) {};
	~SceneManager() {};

	void loadScene(int sceneNumber) {};

	template<typename T>
	void RenderScene(std::vector<T>& obj, sf::Window& windows) {};

private:

	void gameControl() {};
	void menuControl(){};
	void loseControl(){};
	void winControl() {};
	
	int currentScene;
};