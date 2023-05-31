# A Maze Game:
### A C++ game project created using Visual Studio by Utsab Das
---------------------------------------------------------------
A Maze Game is exactly what the title says. In this top-down 2D game, the player navigates progressively larger procedurally generated mazes, finding the key to get to the next level while avoiding obstacles.


Contents
--------
- [Intro](#intro)
- [Overview](#overview)
- [Installation](#installation)
- [Features](#features)
- [Classes](#classes)
	- [main](#main)
 	- [Room](#room)
 	- [Coordinate](#coordinate)
 	- [Maze](#maze)
	- [MazeObject](#mazeobject)
		- [MazeKey](#mazekey)
		- [MazeDoor](#mazedoor)
		- [MazeTrap](#mazetrap)
		- [MazeGuard](#mazeguard)
		- [Player](#player)
- [SDL2 Libraries](#sdl2-libraries)
- [Reflection](#reflection)
- [Contact](#contact)
- [Licenses](#licenses)


### Intro
-----

A Maze Game is a simple maze-solving puzzle game in which the player must reach the end of the level. In order to do so, the player must retrieve a key that opens the lock leading to the next level. Upon reaching that lock, the next level will be randomly generated using

![Alt Text](https://media.giphy.com/media/7OWuHSh9pxhAZq9Kqw/giphy.gif)

While this begins very simple, later levels have obstacles. These obstacles have certain patterns of activation or motion. Since the obstacles only change their state when the player moves, the player must watch for the patterns to reach the destination in the shortest number of steps. If the player runs into any obstacles (traps or guards), the player will restart at the first position in that maze and lose one life.

![Alt Text](https://media.giphy.com/media/55236IJUlI0JyUal4b/giphy.gif)

If a level is particularly challenging, the player can choose to reset the level at the cost of one life. This will create a new maze of the same size. As such, it may not be any less difficult. If the player can continue to get past each level, the game will simply continue to create larger and larger mazes until the player loses all of their lives.

![Alt Text](https://media.giphy.com/media/oNUSOyjlgQxVhGzITd/giphy.gif)

When all lives have been lost, the game is over, and the only options are to quit or return to the front end menu and try to get even further.

![Alt Text](https://media.giphy.com/media/4EEV4s1rA3JH9hsGZs/giphy.gif)


### Overview
--------

Created using
- **Microsoft Visual C++**
- **Microsoft Visual Studio 2017**
- **Simple DirectMedia Layer Development Libraries (version 2.0.8)**
- Miss Ellen Font (TrueType Font) created by Samuel Marcius
	- [Font Page] (http://www.1001fonts.com/miss-ellen-font.html)
- PNG Images created by me

![Alt Text](https://i.imgur.com/RMCwJUa.png)


### Installation
----------------

#### Getting the Project

- Download the project (click the **Clone or Download** dropdown)

![AltText](https://i.imgur.com/pT80UJr.png)

- Open the Solution in Microsoft Visual Studio (double click the **.sln file**)

![AltText](https://i.imgur.com/O0Iun9d.png)

	- Download [Visual Studio 2017] (https://www.visualstudio.com/downloads/) if needed
- Change the Build Configuration to x86

![AltText](https://i.imgur.com/jU3OUEC.png)

#### To Play the Game

- Use the Local Windows Debugger to Build and Run the game

![AltText](https://i.imgur.com/XkS86d6.png)

OR

- Build the Project (in Debug or Release)

![AltText](https://i.imgur.com/RHPdj5Y.png)

- Launch the application from your file explorer (look in the proper Output Directory)

![AltText](https://i.imgur.com/goMARtL.png)

### Features
------------

- Front End Menu
	- Goes into the gameplay
	- Exits the game
- Interactive Player
 	- Movement based off arrow keys
 	- Begins with a number of lives and loses them when you:
  		- Reset the maze
  		- Hit any obstacle
 	- When the player is out of lives, the game is over and the game returns to the Front End
- Procedural Game levels
 	- Procedurally generates mazes that become increasingly larger
 	- Spawns obstacles in randomized locations in the level
 	- Must find key to get to next level


### Classes
-------

#### main

The main.cpp class initializes the game and has the gameplay loops. This class handles creating the window and renderer, rendering the objects and displaying information. The `int main` function carries out the brunt of the game. If initialization is successful, then the game goes into the main game while loop, which carries out actually playing the game. Inside this loop, there are four sub-while loops delineating different states of the game: Front End, Gameplay, Level Complete, and Game Over. If at any of these points, the player closes the window, the game quits all loops and will end.

The front end loop is very short. Only active when the `curGameState == Menu`, it uses the `FrontScreen` function to display the menu to the player. The only options the player has here is to close the window or press the ESC key to quit, or to press any other key to continue. If the player continues, the `curGameState` is set to `InGame`. Before entering the Gameplay loop, if it is the first time the game is loaded (`firstLoad == true`), then it creates a new Maze, creates a new Player, and sets `firstLoad` to false. If it is not the first time, then the `ResetToStart` function is called. After this, the objects are rendered and we move into the gameplay loop.

The gameplay loop is the most extensive. First, the game will display information to the screen (level number, steps, lives, etc.) using the `DrawInGameUI` function and the various `DrawText...` functions. After this, it shows the creation of the maze, then waits for player input to determine what to do. The player can press the ESC key to return to the Menu, the R key to reset the current maze and lose one life (if the player has more than one to begin with), or press one of &larr; &uarr; &rarr; &darr; keys to move the player (these values are passed to the `PlayerMove` function). Any other key press, mouse click, or other input will do nothing. Regardless of what input the player has chosen, at the end of the gameplay loop, everything is added to the renderer and shown on screen using `RenderAllGameObjects`, which calls on the Maze to add all its objects' textures (Rooms, Traps, Guards, Keys, Doors) to the renderer and on the Player add its texture to the renderer. It also again calls the `DrawInGameUI` function to update the information on screen.

If the player retrieves the key and reaches the end, `curGameState` is then set to `LevelComplete`, and we move to the Level Complete loop, which displays the information about how the player performed in that level. The player can then press the space key to contine. This generates the next level and returns `curGameState` to `InGame`.

If the player runs out of lives at any point, `curGameState` is set to `GameOver`, and the game goes into the game over loop. Again, the player has few options; the player can close the window or return to the front end. Returning to the front end will reset the maze back to the first size behind the scenes so that, if the player chooses to start the game again from the front end menu, the game starts anew.


#### Coordinate

The Coordinate struct is used to tell me the position of anything in the maze, including Rooms, any Maze Objects (Traps, Guards, Keys and Doors), and the Player.


#### Room

The Room class gives us a point in the grid required to build the play area. Each Room has information about its position (`roomPos`), direction of walls (`wallDirBit`), rendering area (`roomRect`), and texture (`curRoomTexture). These help to indicate where it will be rendered and what it will look like. The maze has an `bool inMaze` that is set active once the Room has been connected to the maze by the Maze script.

Additionally, the room has pointers to other rooms, including the ones that are adjacent (`adjRooms`), available to connect (`availRooms`), and already connected (`connectRooms`). These are manipulated by the Maze code to form the proper connections. Shortly after the Maze creates the Rooms, their `adjRooms` and `availRooms` variables filled with all the rooms the current one is next to. the `connectRooms` variable is filled later when actually carving out the maze.

The `wallDirBit` is used to determine both what sides the room has walls as well as load the proper textures. We know that rooms that are connected should not have walls between them, but the room does not know what direction the `connectRooms` are to itself. Thus, it has a function called `CheckAdjRoomDir` that allows it to determine what direction any adjacent room may be. This allows it to remove that direction from its list of walls. To help with this, there is the `enum directions` which represents the different directions relative to the room, and is initialized to `{down = 0b0001, left = 0b0010, up = 0b0100, right = 0b1000}`.

When a Room is created, `wallDirbit` is initialized to `0b1111` (15), which indicates that all sides have walls. As the Maze script calls the room's `ConnectRoom` script, which connects this room to another and then calls the `RemoveWallDirection` function will remove the necessary walls to ensure that the correct texture can be assigned.

The Room also has an enum called `RoomType` which has enumerations `{None, Start, Final, Key, Trap, Guard }`, referring to the different kinds of rooms that could exist. Each room has a vector of these called `roomTypes`. When a player enters a room, it will check these types to determine what must be done (i.e. picking up a key, losing a life, etc.).

#### Maze

The Maze class creates the actual maze of the game. It begins this process by using the `CreateRooms` function to create a grid of rooms, giving each a unique position, and storing them in a vector called `allRooms`. These rooms are initialized as described above, and are not yet in the maze.

The `CarveMaze` function actually goes about creating the maze. It stores one of the rooms at random in `curRoomPtr`, puts it into a `currentPath` vector, and uses a backtracking algorithm to carve out the maze. It selects one Room at random as the start point (adding 'Start' to that room's `roomTypes`) and then selects one of its `availRooms` as the next room in the maze, removing the selection from `availRooms` in the process, as well as removing itself from the newly connected room's `availRooms`.

It continues this until it encounters a room with no `availRooms`, at which point it will pop off the top element of the vector, and check if the previous room in the path had any other available rooms. It continues this until all the rooms are `inMaze`.

![AltText](https://media.giphy.com/media/2zdVncFuJoZrQoQBAK/giphy.gif)

As the rooms are placed, if the game has gone to a high enough level, the rooms where obstacles spawn will be selected and added to the `obstacleRooms` vector. These are spaced along the path a distance apart set by the `obstacleSpacing`. This number needs to be high enough so that a maze with obstacles is traversable. They are later created by the `CreateObject` function, which assigns these to the `objectsInMaze` vector. The type of obstacle created (`MazeTrap` or `MazeGuard`) is determined by the current level of the game and the number of connected rooms. Whatever type is created is added to the room's 'roomTypes' variable

The Maze also keeps track of the longest path. It uses this to find set `finalPos` as the furthest distance away, which is used to set the `finalRoom`. A `MazeDoor` object is created there as the way to the next level. After the objects and door are in place, a `MazeKey` object is created by chosing a random room that is not equal to the starting or ending position for the maze. As these objects are placed, the associated room's 'roomTypes' variable is changed accordingly.

After the maze is created, it is still used to update the game during every movement. The `NextMazeCycle` function calls the `NextCycle` function in all members of `objectsInMaze`, causing any objects to perform their behaviors. Additionally, the Maze controls the rendering of all the Rooms and Obstacles within it via its `AddMazeRoomsToRenderer` and `AddMazeObstaclesToRenderer` functions, making each room and object call its own `AddRoomToRenderer` and `AddObjToRenderer` functions, respectively.


#### MazeObject

The MazeObject class is inherited by numerous other classes (`Player`, `MazeTrap`, `MazeGuard`, `MazeDoor`, `MazeKey`). It is primarily used to store the data that would be common amongst any object that appears in the Maze, namely a position (`objPos`) a pointer to its room (`curObjRoom`), its on screen location (`objRect`), its current texture (`curObjTexture`), and a pointer to the renderer (`objRenderer).

It has `SetObjRoom` and `SetObjectRect` functions for setting the object's room and rect variables, as well as a function to `AddObjToRenderer`. Lastly, it contains a virtual function `NextCycle` that certain derived classes may use to implement what they do during each cycle of the game.


##### MazeKey

The MazeKey is the object used to represent the key in game used to open up the MazeDoor.


##### MazeDoor

The MazeDoor is the object used to represent the lock in the game that you must reach in order to get to the next level. The player needs to have the key to open the lock and reach the next level.


##### MazeTrap

The MazeTrap class defines an obstacle the player can encounter in the maze. It activates based off of its `curTrapTime` and `maxTrapTime`. The `curTrapTime` is incremented by `NextCycle` (every game cycle). After it becomes larger than the `maxTrapTime`, it resets to 0 and activates the Trap, changing its texture for rendering and making the room harmful to the player.


##### MazeGuard

The MazeGuard is another obstacle the player can encounter in the maze. The MazeGuard will only be created next to a room with three connected rooms. The MazeGuard maintains that room as its center (`guardCenterRoomPtr`) while moving between its three connected rooms (`guardCurRoomPtr). Just like an active trap, it will make the room it currently occupies harmful to the player.


##### Player

The Player class creates the controllable player to the maze. When each level starts, the player has a `startRoom` variable set, so that the player knows where to begin and where to respawn if they die in that level. Additionally, the player `bool hasKey` is set to false.

When the `PlayerMove` function is called, it returns a boolean `successfulMove` based off if the movement is possible or not. If the player moves in the direction of a wall, then the movement will fail, and the player will only change its texture to face the proper direction. If the player moves in the direction of a connectRoom relative to the player's current room, the move is successful.

If the move was successful, the main.cpp class has the player call its `CheckForObjects` function, with which the player checks if there is any object in the same position. If there is a key, `hasKey` is set to true. If there is an obstacle (Trap or Guard), its `playerLives` variable is decremented and it will restart at the `startRoom`. The player may also lose a life if the R key is pressed, causing the maze and player to reset and costing the player one life.


### SDL2 Libraries
--------

SDL2 was used to actually display the game on screen. To display images and text onto the screen, I needed to bring in other SDL2 resources. The SDL2 Libraries implemented here are

- SDL2
- SDL2_main
- SDL2_image
- SDL2_ttf


### Reflection
---------------

I was able to learn a lot in this C++ Project. I had never used the SDL Libraries before, and I feel much more comfortable with them. I want to dive further into SDL and see how to utilize it to create a simple 2D game engine. I plan to continue working on this project to make certain areas more efficient, while also implementing more obstacles with unique behaviors, creating mazes not confined to rectangular shapes, and changing the rendering method to be more realtime rather than turn based. Ultimately, this experience taught me much and I hope to take it further.


### Contact
------------

Contact me with any questions or concerns!

Email: utsabkdas@gmail.com

LinkedIn: https://www.linkedin.com/in/utsabkdas/

### Licenses
------------

This project is licensed under the [MIT License](https://github.com/ukdv12/A-Maze-Game/blob/master/LICENSE).

Other Licenses
- [Simple DirectMedia Layer Library License](https://www.libsdl.org/license.php)
- [1001Fonts General Font Usage Terms](http://www.1001fonts.com/licenses/general-font-usage-terms.html)
