# sdl2-pong
A SDL2 implementation of the classic Pong game.

Contains a single mode where two human players can play against each other.

Development blog entry: https://toivjon.wordpress.com/2017/06/20/sdl2-pong/

## Scenes
Game is split into following scenes:
1. A welcome scene, which contains the main menu.
2. A court scene, which contains the actual gameplay.
3. An end game scene, which contains the results from the court scene.

The list of scene transitions:
* 1 to 2, when a player starts the game by pressing the enter key.
* 2 to 3, when either player receives the 10th point (i.e. game is over).
* 3 to 1, when the enter key is being pressed.

## Features
This Pong implementation contains the following features.
* Each game lasts until either player receives the 10th point.
* Both paddles are controlled by human players.
* Ball velocity is increased on each hit with a paddle.
* Ball velocity does not exceed the pre-defined maximum velocity.
* Ball movement is being stopped for 30 ticks after each reset.
* Ball direction is randomized from four different directions after each reset.
* Paddles are returned to their default position after each reset.

## External Dependencies
This implementation has external dependencies on the following libraries:
* SDL2
* SDL2_ttf
* libfreetype-6.dll
* zlib1.dll

## Compilation
Easiest way to compile the code is to use the [CMake](https://cmake.org/) utility.

Required tools and libraries for the compilation:
1. [CMake](https://cmake.org/) (ver. >=3.7.2)
2. [SDL2](https://www.libsdl.org/download-2.0.php) (ver. >=2.0.5)
3. [SDL2_ttf](https://www.libsdl.org/projects/SDL_ttf/) (ver. >=2.0.14)
4. A compilation toolkit supported by the CMake utility (e.g. Visual Studio).

CMake compilation uses Find*-modules from the /cmake folder which specify where CMake looks for the required libraries.

Without any modifications, CMake will make use the following environment variable paths.
* SDL2DIR, which should point to the root directory of the SDL2 library.
* SDL2TTFDIR, which should point to the root directory of the SDL2_ttf library.

## Screenshots
![alt text](screenshots/welcome-scene.png "WelcomeScene")
![alt text](screenshots/court-scene.png "CourtScene")
![alt text](screenshots/endgame-scene.png "EndGameScene")
