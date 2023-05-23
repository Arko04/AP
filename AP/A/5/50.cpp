#include <SFML/Graphics.hpp>
#include "Entity.h" 

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Player Movement");

    // Load in your wall texture
    sf::Texture wall_texture;
    if (!wall_texture.loadFromFile("wall_texture.png"))
    {
        return -1;
    }
    
    // Create the wall sprite
    sf::Sprite wall;
    wall.setTexture(wall_texture);
    wall.setPosition(400.f, 550.f);

    // Create the player entity
    Entity player(sf::Vector2f(50.f, 50.f), sf::Color::Green);
    player.setPosition(sf::Vector2f(50.f, 500.f));
    player.setVelocity(sf::Vector2f(5.f, 0.f));

    // Main game loop
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Update player position and direction
        player.update();

        // Check for intersection with wall
        if (player.getGlobalBounds().intersects(wall.getGlobalBounds()))
        {
            // Change direction of player
            player.setVelocity(-player.getVelocity());
        }

        window.clear();

        // Draw wall and player entities
        window.draw(wall);
        window.draw(player);

        window.display();
    }

    return 0;
}
const int MAP_WIDTH = 10;
const int MAP_HEIGHT = 5;

int map[MAP_HEIGHT][MAP_WIDTH] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 1, 0, 1, 1, 0, 0, 1},
    {1, 0, 1, 1, 0, 1, 1, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};
for (int y = 0; y < MAP_HEIGHT; y++)
{
    for (int x = 0; x < MAP_WIDTH; x++)
    {
        switch (map[y][x])
        {
            case 1: // Wall
                // Create a Wall object at position (x, y)
                break;
            case 2: // Enemy
                // Create an Enemy object at position (x, y)
                break;
            case 3: // Player
                // Create a Player object at position (x, y)
                break;
            default: // Empty space
                break;
        }
    }
}
sf::Vector2i playerPosition = {0, 0}; // current player position
const int tileSize = 32; // size of each tile in pixels

while (window.isOpen())
{
    // Handle user input
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        // Check if the next tile to the left is empty
        if (map[playerPosition.y][playerPosition.x - 1] == 0)
        {
            // Update player position
            playerPosition.x--;
        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        // Check if the next tile to the right is empty
        if (map[playerPosition.y][playerPosition.x + 1] == 0)
        {
            // Update player position
            playerPosition.x++;
        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        // Check if the next tile above is empty
        if (map[playerPosition.y - 1][playerPosition.x] == 0)
        {
            // Update player position
            playerPosition.y--;
        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        // Check if the next tile below is empty
        if (map[playerPosition.y + 1][playerPosition.x] == 0)
        {
            // Update player position
            playerPosition.y++;
        }
    }

    // Draw the game world
    for (int y = 0; y < MAP_HEIGHT; y++)
    {
        for (int x = 0; x < MAP_WIDTH; x++)
        {
            switch (map[y][x])
            {
                case 1: // Wall
                    // Draw a wall tile at position (x, y)
                    break;
                case 2: // Enemy
                    // Draw an enemy sprite at position (x, y)
                    break;
                case 3: // Player
                    // Draw the player sprite at their current position
                    playerSprite.setPosition(playerPosition.x * tileSize, playerPosition.y * tileSize);
                    window.draw(playerSprite);
                    break;
                default: // Empty space
                    // Draw an empty tile at position (x, y)
                    break;
            }
        }
    }

    // Display the game world
    window.display();
}
/*In this example code, we have defined a variable playerPosition to keep track of the current position of the player on the map. We also define tileSize to specify the size of each tile in pixels.

In the main game loop, we check for user input using the isKeyPressed function of the sf::Keyboard class. If the user presses a key that corresponds to a valid move, we update the playerPosition variable accordingly.

To prevent the player from moving off the edge of the map or into a wall, we check if the next tile in the desired direction is empty before updating the player position.

When drawing the game world, we use playerPosition to set the position of the player sprite based on their current position on the map. We then draw all game objects to the screen as appropriate.

Note that you should add additional checks and logic to handle collisions with walls and other objects on the map, as well as handle situations where the player moves outside the bounds of the map*/