// ReSharper disable All
#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include "Math.h"

using namespace std;

namespace Apples_Game
{	
	constexpr int BIT_RANDOM_APPLES_MODE = 0x01;	
	constexpr int BIT_ACCELERATION_MODE = 0x20;		
	constexpr int BIT_ENDLESS_APPLES_MODE = 0x300;
	
	constexpr int SIZE_LEADERBOARD = 10;
	
	constexpr int SCREEN_WIDTH = 800;
	constexpr int SCREEN_HEIGHT = 600;
	
	constexpr int NUM_TREE = 5;
	constexpr int NUM_APPLES_MIN = 20;
	constexpr int NUM_APPLES_MAX = 100;	

	constexpr float TREE_SIZE = 50.f;
	constexpr float APPLE_SIZE = 25.f;
	constexpr float PLAYER_SIZE = 40.f;

	constexpr float INITIAL_SPEED = 200.f;  // Pixel per seconds  // Поменять на скорость 100, после тестов
	constexpr float ACCELERATION = 5.f;     // Pixel per seconds
	constexpr float PAUSE_LENGTH = 0.f;

	const string RESOURCES_PATH = "Resources/";
}