# Function Log
## Balloon
<details>
<summary> Update</summary>
Checks if the health of the balloon is above 0 using an if statement.
If it isnt then the objects position is set to a value outside of the windows constraints, the else statement should never be called however better safe than sorry. If the if statement evaluates to true then it uses moveTowards function and then checks if it is around the checkpoint coordinate. Then proceeds to call Render which is declared is sprite manager
</details>
<details>
<summary> moveTowards</summary>
Gets the direction of the vector to move in. Calls the normalize function which is in MathHelp. Then has to be multiplied by -1 because of how the math is handled in the back end. I'm not sure why it needs the -1 but it does. Then calls the move function multiplying speed by direction. Where speed already has the delta time applied to it.
</details>
<details>
<summary> getHealth</summary>
Returns the current health of the balloon
</details>
<details>
<summary> getInitHealth</summary>
Returns the initial health of the balloon. Used in calculation for how much to pay to the player for destroying the balloon.
</details>
<details>
<summary> changeHealth</summary>
Subtracts the current health by some change value
</details>

### Private values:
##### floats
m_speed
##### ints
m_health, m_InitialHealth, coordIndex
##### Misc: 
std::vector<sf::Vector2f> coords

## Dart
<details>
<summary> changeSpeed</summary>
Changes the speed of the dart.
</details>
<details>
<summary> getSpeed</summary>
Returns the speed of the dart.
</details>
<details>
<summary> moveTowards</summary>
Same direction calculation as used in the Balloon. Same speed design aswell
</details>
<details>
<summary> isCollided</summary>
Checks if the GolbalBounds of the Dart intersect with the GlobalBounds of the m_target object. Returns a boolean value
</details>
<details>
<summary> getTarget</summary>
Returns a Balloon pointer to the m_target value
</details>

### Private values:
##### floats
m_speed
##### Misc:
m_target a Balloon pointer

## Game
### Constructor
Sets the seed of the rand functionality. Then runs through some macro if and elif to deterimer whether or not I can use the \<filesystem> library and more specifically the directory_iterator function. Then it loads Invisible markers used for tower placement detection. Then some other helper items but nothing two important.
<details>
<summary> getLives</summary>
Returns the m_lives varible. Integer value
</details>
##### whatLevel
Returns what is issues as the level instance for the std::vector of Levels. I.e uses the equation defined as: $(mLevel)\over 10$
### runGame
First revaluates the m_levelInstance through $(mLevel)\over 10$ Then it checks whether the amount of balloons spawned is equal to the max Balloons. It its true the m_balloonsSpawned to zero and m_totalMoney is added by the number of maxBalloons. Then includes a time check using 
```c++
std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now().time_since_epoch());
```
I.e. gets the time since the epoch is milliseconds. Then if the time pass which is subtracted by the time since the last balloon spawns m_LastBalloonSpwan is greater than the delay, it then spawns a balloon with a random level using
``` c++
rand()%m_Levels[m_levelInstance]->maxLevel+1
```
So max level is modulating between 1 and the maxLevel indicated in the maxLevel varible. It then loops through the Towers held in the m_TowerObjects and runs their update function. Then loops through the m_BalloonObjects vector. First checking the health to make sure its alive still. then runs the balloon update and then runs through the tower objects again to find balloons inside of the radius of any given tower. This will result in the first balloon to be in the vector(should be the first spawned balloon) to be the first evaulated and the first target that the tower could potentially shoot. Otherwise if the m_BalloonObjects object does not have a qualified health then it will be deleted from the vector using these lines.
```c++
Balloon* pTemp = m_BalloonObjects.at(l_balloonLoc);
m_BalloonObjects.erase(m_BalloonObjects.begin() + l_balloonLoc);
delete pTemp;
```
Then a reptitive m_Level check just in case
<details>
<summary> spawnTower</summary>
Creates a Tower object using new. Pushes the object back to the m_TowerObjects vector.
</details>
<details>
<summary> runThroughTowers</summary>
Runs through the Towers in the m_TowerObjectsVector. Only called when mouse clicked. Used to display the shooting radius
</details>
<details>
<summary> getMoney</summary>
Returns the m_totalMoney varible. Integer value
</details>
<details>
<summary> subtractMoney</summary>
Subtracts from the m_totalMoney varible by the input amount
</details>
<details>
<summary> addMoney</summary>
Adds to the m_totalMoney varible using the inputed value
</details>
<details>
<summary> getLevel</summary>
Returns the m_level varible. Integer value
</details>
##### readBalloonFile
Reads the balloon file in. The File is built like
| Max Level of Balloon |Max Balloons | delay|
| ---------- | --------- | --------- |
| 5 | 25 | 1000 | 
| 6 | 25 | 1000 |
|7|30|1000|
Level of Balloon is also directly related to its health.
Max Balloons in the number of Balloons to spawn for a given level
Delay is the time between each Balloon spawn
### Private values:
##### struct Level
holds integer values for maxBalloons and maxLevel, along with a float for the delay. Is where the data from the balloon file is read into.
##### ints:
m_lives, m_level, m_levelInstance, m_balloonsSpawned, m_totalMoney
##### sf namespace Objects:
Vector2f m_BalloonSpawnLoc
RenderWindow pointer m_Window
##### Standard Objects
vector of Level pointers (m_Levels)
vector of Tower pointers (m_TowerObjects)
vector of balloonObjects (m_Balloonobjects)
chrono::milliseconds m_LastBalloonSpawn (Used to tell how much time has passed between balloon spawing)
#### Deprecated
void RenderText
sf::Text m_LevelDisplay

## Shop
<details>
<summary> whatToBuy</summary>
No implementation yet.
</details>
<details>
<summary> update</summary>
Creates the message for the Total money which is what the m_MoneyText is set to. Calls giveBackValue() just incase it is needed. If there is an activeItem then it sets the position of the m_TowerToPlace shape to the mousePosition. Not the most elegent solution but it works. Then it calls RenderShop
</details>
<details>
<summary> handleMouseInput</summary>
First checks if activeItem is true. If so it calls spawnTower(game Function). It also gets the pos from the function sf::Mouse::getPosition. then sets the activeItem to false. Otherwise it sees if the monkeyButton(needs to be changed to a for loop of all buttons) contains the mouse. If this is true then it checks how much time has passed.(Should be able to be removed). Then checks if the game has enough money to purchase. Sets the activeItem to true and sets up a texture to follow the mouse. Resets the m_lastPurchase to the current time varible. Then subtracts the money. The next else if should be able to be removed but does the same thing. Other wise it prints that there are insuficient funds, should become a Text instead of a cout.
</details>
<details>
<summary> RenderShop</summary>
First checks if activeItem is set to true. If it is it drasws the m_TowerToPlace object. Then it draws the m_MoneyText object, the menuBase object and the monkeyButton object.
</details>
<details>
<summary>giveBackValue</summary>
if activeItem is true the if the escape key is pressed then it add 100 back to the money varible and then sets activeItem to false.
</details>
### Private values:
##### sf namespace Objects
<details>
<summary> Rectangle Shapes</summary>
m_TowerToPlace, menuBase, monkeyButton
</details>
sf::Font pointer m_font: linkes a font already declared.
sf::Text m_MoneyText: Text object for displaying the text
sf::Texture m_texture: default texture object (Will be changed)
##### Misc:
chrono::milliseconds m_lastPurchase: used for timing purposes
##### Boolean
activeItem
##### Game
m_game pointer to the game class that runs most things

## Tower
### Subject to Change because of it becoming a base class
#### isInRadius
Uses the distance formula which come out to be $\sqrt{((v1.x - {mRadius\over2}) - (b1.x  - b1.radius +25))^2 + ((v1.y - {mRadius\over2}) - (b1.y  - b1.radius +25))^2}$This is a modified implimentation of the distance formula $\sqrt{(v1.x-v2.x)^2 +(v1.y-v2.y)^2}$  here v1.x is being generated by finding the midpoint of the object by subtracting the radius from the original position, because the position is set to the top left corner of the object in sfml. Thus that creates this equation. The random +25 is meant to make it look more natural but really what it ends up doing is negative the effectiveness of b1.radius (Subject To Change).
If the distance formula returns a value that is smaller than m_Radius it adds the balloon to the list and calls throwDart.
<details>
<summary> visualizeRadius</summary>
Creates a sf::CircleShape to visualize the radius. Sets the position to the middle of the object using a similar calculation.
</details>
<details>
<summary> update</summary>
First checks if m_Display is true, if it is it calls visualizeRadius. then it loops through the Darts vector checking if any collided. If one did then it changes the targets health by what will become dartPower. Then it erases the dart.(May cause memory leak not totally sure). Then it loops through the darts again and calls moveTowards and then draws the dart(extremly inefficient should be moved up a loop). This it draws the Tower object
</details>
<details>
<summary> addBalloonToList</summary>
Adds a balloon to the m_BalloonsInRange vector. (Vector not actually used in any capacity)
</details>
<details>
<summary>getDisplayBool</summary>
Returns the m_display boolean.
</details>
<details>
<summary>setDisplayBool</summary>
Sets the m_display boolean to an inputed value
</details>
### Private values:
##### ints:
default_Delay, delay, default_DartPower, dartPower, default_Radius, m_radius
##### floats:
default_Radius, radius
##### bools:
m_display
##### Misc:
std::vector<Dart*> darts
std::chrono::milliseconds m_lastThrownDart
std::vector<Balloon*> m_BalloonsInRange
##### sf namespace:
Vector2f m_pos

## MathHelper
### Function:
##### normalize:
I.e. create a unit vector. 
First finds the magnitude of the vector using $length = \sqrt{v.x^2 + v.y^2}$. It then takes that and divides the original v.x and v.y by that magnitude to get the unit vector so $\begin{bmatrix}v.x\over Length & v.y\over Length\end{bmatrix}$  is the normalized 2x1 vector
##### abs
Returns the absolute value of a vector. I.e if a vector entry is less than 0 it is multiplied by -1
##### isAround 
Takes in an offest a current Position and a targetPosition. So if the currentPositon - offset if smaller than the targetPositon then true is returned otherwise it is false.
## MapGen
### Constructor 
initializes the texture to use and the font to use
### Run
Sets up some helper text. Generates the grid of square which is a nxn grid with a set size. The it opens up the window in a while loop and runs its own while loop that exits when you each the finish of generating the map. Arrow Key to handle input and movement of the path generation. Renders the grid and the associated textures if a path has been set their.

