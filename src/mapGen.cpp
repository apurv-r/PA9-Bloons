#define _CRT_SECURE_NO_WARNINGS

#include <SFML/Graphics.hpp>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <ctime>
#include <chrono>

std::string generateRandomString(int length) {
    std::string result = "";
    const char charset[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    const int charsetSize = sizeof(charset) - 1;
    srand(time(NULL)); // seed the random number generator

    for (int i = 0; i < length; i++) {
        int randomIndex = rand() % charsetSize;
        char randomChar = charset[randomIndex];
        result += randomChar;
    }

    return result;
}

typedef enum dir {
    NONE, LEFT, RIGHT, UP, DOWN
} Direction;

/*
std::ifstream infile("CustomMaps/map-PDQH0.txt");
    // Read the map name and discard it
    std::string line;
    std::getline(infile, line);
    std::getline(infile, line);
    std::getline(infile, line);


    // Read each line of coordinates and extract them into a vector
    while (std::getline(infile, line)) {
        // split the line by commas
        std::istringstream s(line);
        std::string field;
        getline(s, field, ',');
        int x = std::stoi(field);
        getline(s, field, ',');
        int y = std::stoi(field);
        coords.push_back(sf::Vector2f(x, y));
    }
*/

// change this function's name whenever you wanna run it
int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 1100), "Map creator", sf::Style::Close);

    sf::Texture upArrow, downArrow, rightArrow, leftArrow;

    if (!upArrow.loadFromFile("Resources/arrow-up.png")) {
        std::cout << "Cannot load arrow-up.png\n";
    }
    if (!downArrow.loadFromFile("Resources/arrow-down.png")) {
        std::cout << "Cannot load arrow-down.png\n";
    }
    if (!leftArrow.loadFromFile("Resources/arrow-left.png")) {
        std::cout << "Cannot load arrow-left.png\n";
    }
    if (!rightArrow.loadFromFile("Resources/arrow-right.png")) {
        std::cout << "Cannot load arrow-right.png\n";
    }

    sf::Font font;
    font.loadFromFile("Dependencies/Dosis/static/Dosis-Regular.ttf"); // load font file

    sf::Text helperText;
    helperText.setFont(font);
    helperText.setString("Select a starting point on the boundary"); // set helperText string
    helperText.setCharacterSize(40); // set character size
    helperText.setFillColor(sf::Color::White); // set helperText color
    helperText.setPosition(500, 950); // set helperText position

    // 10x10 grid of squares
    const int gridSize = 10;
    const int squareSize = 100;
    sf::RectangleShape squares[gridSize][gridSize];
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            squares[i][j].setSize(sf::Vector2f(squareSize, squareSize));
            squares[i][j].setPosition(i * squareSize, j * squareSize);
            squares[i][j].setFillColor(sf::Color::Black);
            squares[i][j].setOutlineColor(sf::Color::White);
            squares[i][j].setOutlineThickness(1.f);
        }
    }

    bool startPlaced = false,
        placingPath = false,
        pathDone = false;
    int startX, startY;

    std::vector<sf::Vector2i> path;
    std::vector<sf::Vector2f> filteredPath;

    while (window.isOpen())
    {
        // Check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // If the event is a mouse button press and the square is on the boundary, change its color
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                int x = event.mouseButton.x / squareSize;
                int y = event.mouseButton.y / squareSize;
                sf::Vector2f squareCenter = sf::Vector2f((x + 0.5f) * squareSize, (y + 0.5f) * squareSize);
                // placing the start point
                if (!startPlaced && (x == 0 || y == 0 || x == gridSize - 1 || y == gridSize - 1) && (x != 0 || y != 0) && (x != gridSize - 1 || y != gridSize - 1) && (x != 0 || y != gridSize - 1) && (x != gridSize - 1 || y != 0)) {

                    std::cout << "started " << x << ", " << y << "to path" << std::endl;

                    squares[x][y].setFillColor(sf::Color::Green);
                    startPlaced = placingPath = true;
                    startX = x; // Store the starting point's coordinates
                    startY = y;
                    path.push_back(sf::Vector2i(x, y));
                    helperText.setString("Use the arrow keys to define the path");
                }
            }

            // If the event is a key press event, check for arrow key presses
            if (placingPath && event.type == sf::Event::KeyPressed) {
                int x = startX;
                int y = startY;
                Direction rotateTo = NONE;
                // If the left arrow key is pressed, move the starting point one square to the left
                if (event.key.code == sf::Keyboard::Left) {
                    x--;
                    rotateTo = LEFT;
                }
                // If the right arrow key is pressed, move the starting point one square to the right
                else if (event.key.code == sf::Keyboard::Right) {
                    x++;
                    rotateTo = RIGHT;
                }
                // If the up arrow key is pressed, move the starting point one square up
                else if (event.key.code == sf::Keyboard::Up) {
                    y--;
                    rotateTo = UP;
                }
                // If the down arrow key is pressed, move the starting point one square down
                else if (event.key.code == sf::Keyboard::Down) {
                    y++;
                    rotateTo = DOWN;
                }
                else {
                    break;
                }
                // If the new position is within the boundaries of the grid, update the starting point
                if ((x >= 0 && x < gridSize && y >= 0 && y < gridSize) && !(squares[x][y].getFillColor() == sf::Color::Blue)) {
                    // Checking if player is stuck (no where to go)
                    if (std::find(path.begin(), path.end(), sf::Vector2i(x + 1, y)) != path.end() && // right
                        std::find(path.begin(), path.end(), sf::Vector2i(x - 1, y)) != path.end() && // left
                        std::find(path.begin(), path.end(), sf::Vector2i(x, y + 1)) != path.end() && // up
                        std::find(path.begin(), path.end(), sf::Vector2i(x, y - 1)) != path.end()
                        ) {

                        window.clear(sf::Color::Black);
                        startPlaced = false;
                        for (int i = 0; i < gridSize; i++) {
                            for (int j = 0; j < gridSize; j++) {
                                squares[i][j].setTexture(nullptr);
                                squares[i][j].setFillColor(sf::Color::Black);
                            }
                        }
                        path.clear();
                    }
                    else {
                        if (x == 0 || y == 0 || x == gridSize - 1 || y == gridSize - 1) {
                            // Checking if the path just started, shouldn't start and end immediately
                            if (path.size() == 1) {
                                break;
                            }
                            switch (rotateTo) {
                            case UP:
                                squares[startX][startY].setTexture(&upArrow);
                                break;
                            case DOWN:
                                squares[startX][startY].setTexture(&downArrow);
                                break;
                            case LEFT:
                                squares[startX][startY].setTexture(&leftArrow);
                                break;
                            case RIGHT:
                                squares[startX][startY].setTexture(&rightArrow);
                                break;
                            }
                            squares[startX][startY].setFillColor(sf::Color::Cyan);
                            squares[x][y].setFillColor(sf::Color::Red);
                            std::cout << "ended " << x << ", " << y << "to path" << std::endl;
                            placingPath = false;
                            path.push_back(sf::Vector2i(x, y));

                            // Clear the window with black color
                            window.clear(sf::Color::Black);

                            // Draw all the squares to the window
                            for (int i = 0; i < gridSize; i++) {
                                for (int j = 0; j < gridSize; j++) {
                                    window.draw(squares[i][j]);
                                }
                            }

                            for (int i = 0; i < path.size(); i++) {
                                if (i == 0 || i == path.size() - 1 || path[i].x != path[i - 1].x || path[i].x != path[i + 1].x || path[i].y != path[i - 1].y || path[i].y != path[i + 1].y) {
                                    sf::Vector2f point(path[i].x * squareSize + squareSize / 2.f, path[i].y * squareSize + squareSize / 2.f);

                                    // putting the start/end point off screen
                                    if (i == 0 || i == path.size() - 1) {
                                        if (point.x == 50) {
                                            point.x = -50;
                                        }
                                        else if (point.x == 950) {
                                            point.x = 1050;
                                        }
                                        else if (point.y == 50) {
                                            point.y = -50;
                                        }
                                        else if (point.y == 950) {
                                            point.y = 1050;
                                        }

                                    }
                                    filteredPath.push_back(point);
                                }
                            }

                            pathDone = true;

                            std::string mapName = "map-" + generateRandomString(5);
                            std::ofstream mapStream("CustomMaps/" + mapName + ".txt");
                            if (mapStream.is_open()) {
                                helperText.setString("Path done! Saving to file...");
                                mapStream << "Map Name: " << mapName << std::endl;
                                std::time_t current_time_t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
                                std::string cur_time_epoch = std::ctime(&current_time_t);
                                mapStream << "Created: " << cur_time_epoch << std::endl;
                                for (int i = 0; i < gridSize; i++) {
                                    for (int j = 0; j < gridSize; j++) {
                                        if (squares[j][i].getFillColor() == sf::Color::Black) {
                                            mapStream << "-";
                                        }
                                        else {
                                            mapStream << "x";
                                        }
                                    }
                                    mapStream << "\n";
                                }
                                mapStream << "\n";
                                for (auto& element : filteredPath) {
                                    mapStream << element.x << "," << element.y << "\n";
                                }

                            }

                            mapStream.close();
                        }
                        else {
                            switch (rotateTo) {
                            case UP:
                                squares[startX][startY].setTexture(&upArrow);
                                break;
                            case DOWN:
                                squares[startX][startY].setTexture(&downArrow);
                                break;
                            case LEFT:
                                squares[startX][startY].setTexture(&leftArrow);
                                break;
                            case RIGHT:
                                squares[startX][startY].setTexture(&rightArrow);
                                break;
                            }
                            squares[startX][startY].setFillColor(sf::Color::Cyan); // Reset the old starting point
                            squares[x][y].setFillColor(sf::Color::Green); // Set the new starting point

                            std::cout << "added " << x << ", " << y << "to path" << std::endl;
                            path.push_back(sf::Vector2i(x, y));
                            startX = x;
                            startY = y;
                        }
                    }
                }
            }

            // If the event is "close window", close the window
            if (event.type == sf::Event::Closed) {
                window.close();
            }

        }

        window.clear(sf::Color::Black);

        // Draw all the squares to the window
        for (int i = 0; i < gridSize; i++) {
            for (int j = 0; j < gridSize; j++) {
                window.draw(squares[i][j]);
            }
        }

        // Centering text
        sf::FloatRect textRect = helperText.getLocalBounds();
        helperText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
        helperText.setPosition(window.getSize().x / 2.0f, 1055);
        window.draw(helperText);


        window.display();
    }



    return 0;
}
 