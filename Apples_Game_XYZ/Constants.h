// ReSharper disable All
#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include "Math.h"

using namespace std;

namespace Apples_Game
{	
	constexpr const int BIT_RANDOM_APPLES_MODE = 0x01;
	//const int BIT_NO_RANDOM_APPLES_MODE = 0b00000000;
	
	constexpr const int BIT_ACCELERATION_MODE = 0x20;
	//const int BIT_NO_ACCELERATION_MODE = 0b00000000;
		
	constexpr const int BIT_ENDLESS_APPLES_MODE = 0x300;
	//const int BIT_NO_ENDLESS_APPLES_MODE = 0b00000000;

	constexpr const int SIZE_LEADERBOARD = 10;
	
	constexpr const int SCREEN_WIDTH = 800;
	constexpr const int SCREEN_HEIGHT = 600;
	
	constexpr const int NUM_TREE = 5;
	constexpr const int NUM_APPLES_MIN = 20;
	constexpr const int NUM_APPLES_MAX = 100;	

	constexpr const float TREE_SIZE = 50.f;
	constexpr const float APPLE_SIZE = 25.f;
	constexpr const float PLAYER_SIZE = 40.f;

	constexpr const float INITIAL_SPEED = 200.f;  // Pixel per seconds  // Поменять на скорость 100, после тестов
	constexpr const float ACCELERATION = 5.f;     // Pixel per seconds
	constexpr const float PAUSE_LENGTH = 0.f;

	const string RESOURCES_PATH = "Resources/";

	//constexpr int GRID_SIZE = 4;
	// constexpr unsigned APPLES_GRID_CELLS_HORIZONTAL = GRID_SIZE;    //static_cast<unsigned>(SCREEN_WIDTH / (APPLE_SIZE * GRID_SIZE));
	// constexpr unsigned APPLES_GRID_CELLS_VERTICAL = GRID_SIZE;      //static_cast<unsigned>(SCREEN_HEIGHT / (APPLE_SIZE * GRID_SIZE));
	// constexpr unsigned MAX_APPLES_IN_CELL = NUM_APPLES_MAX / GRID_SIZE;
}