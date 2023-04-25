## 4/24/2023 
### Window:
Expanded the size of the window to 2000x2000 subject to change.
(See TODO)
### Game:
Created SpawnTower Function. Used to create a tower object at a position. Used in the Shop class. Name of Function is subject to change. Fixed m_levelInstance so that now it wont crash when your level/10 is greator than the m_levels.size(). Money is now handled in the game class
### Balloon: 
Added a delta time multiplication for the moveTowards function call addition along with some other minor fixes to data values to better compensate to the changes in window size and to the delta time multiplication
### Shop
This is the big change. Shop takes in a Game reference and stores it in its own pointer. RenderShop only renders the item you want to purchase if the activeItem is set to true. Thus normally it will only render the UI.
giveBackValue gives back the value that you purchased the tower for to you and gets rid of the tower being instantiated. 
HandleMouseInput handles the mouse input using sf::Event::MouseButtonRelease[^1] The function works by first checking if enough time has passed between purchases(Not required anymore because of MouseButtonRelease see for more information[^1]).  Then checks if the object is in the global bounds of the button object 
```c++
if (monkeyButton.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))))
```
If the object can be purchased then activeItem is set to true. This allows for it to be draw later. Sets the texture to be used, and will follow the mouse around. Also takes the money away through the Game pointer that it holds. Giving back the money is also possible through the function giveBackValue which is written as such
```c++
if (this->activeItem)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			this->m_game->addMoney(100);
			this->activeItem = false;
		}
	}
```

### Text and Money
Text now works except for in the game class where it breaks down and throws a .dll error. Fixing it seems like it will take forever so I'm not going to. So the outputting text relating to the game class is handled in main.cpp
### Frame rate and other quality of Life
setFramerateLimit allows you to set a limit to the frame rate. This caps it and helps run smoother overall.
## TODO
Allow for things to be dependent on the size of the window. Things from the previous TODO that were not addressed with this.

[^1]:Reason behind using isMouseButtonReleased is that while only one frame of mouse button being released is possible many frames can be taken up for isMouseButtonPressed. So in basically any video game setting or any application setting you should use isMouseButtonReleased. 
## 4/24/2023 
### Balloon:
Balloon inherits the properties of the SpriteManager Class. Also now holds a speed and health, aswell as the coordinates that it needs to go to.
Update Function just checks first if the health is greater than zero. Hopefully the else never happens but it is possible if an error occurs. 
### Tower:
Tower inherits the properties of the sf::RectangleShape. Constructor creates the shape, and sets its radius for attack range. Needs to be changed for polymorphism implementation(See TODO)
Holds all the darts thrown. Dart delay was implemented through std::chrono. I.e just takes in the time since epoch, and shoots after a set amount of time has passed in milliseconds. Also now holds a vector of balloons in range.(See TODO).
### GameObject:
Not Finished. Potentially may be deleted (See TODO)
### SceneManager:
Not finished. Manages which scene you are in and displays the right screen.(See TODO)
### Game:
Has its own pointer to the window object. Holds when the last balloon was spawned. Same thing as with the Dart delay in Tower. Created vectors for Tower objects and BalloonObjects. Level struct that holds the maxBalloons, maxLevel of Balloon and the delay for each balloon spawn. runGame spawns in balloons and runs through a loop of all ballooons and first checks if they are still above on health and the updates and then loops through the tower list and checks if they are in the radius of any tower. If the balloon's health is below 0 then it is erased from the vector and deleted.
```c++
Balloon* pTemp = m_BalloonObjects.at(l_balloonLoc);
m_BalloonObjects.erase(m_BalloonObjects.begin() +l_balloonLoc);
delete pTemp;
```
Towers are again ran through a for loop and updated. This is because they should not depended on there being balloons. Balloon file is as follows: maxLevel, maxBalloons, delay(mS)
Timing function for delays is as follows:
``` c++
std::chrono::milliseconds t_CurTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now().time_since_epoch());
```
### Main:
Updated to use the game class and run off of the runGame function. Still holds the window generation.

## TODO:
### Tower:
needs to eventually become a abstract base class so polymorphism can take effect. Balloon vector is a posibility where it may be used to judge what object to shoot. But is very subject to change because it may have been solved by my loops inside of the runGame function.
### Gameobject:
idea is not final but may be a template class that can use both Tower and Balloon so that they can be held there and render functions can be handled by gameObject class.
### SceneManager
Allows to check what scene to render by taking the integer defined for the scene and calls the correct function call maybe a std::function to store the function location idk.