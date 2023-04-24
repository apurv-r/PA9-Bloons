# ChangeLog
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