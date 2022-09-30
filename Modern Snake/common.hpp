//
//  common.hpp
//  Modern Snake
//
//  Created by Efe Arikan on 24.09.22.
//

#ifndef common_h
#define common_h

#include <random>
#include <chrono>
#include <thread>

static std::random_device rd;
static std::mt19937 rng{rd()};

constexpr int field_heigth = 24;
constexpr int field_width = 48;
constexpr int score_heigth = 10;
constexpr int score_width = 20;

constexpr int MAX_MENU = 2;

typedef std::pair<int, int> COORD;

typedef enum : int {
	Right = 0,
	Left = 1,
	Up = 2,
	Down = 3,
	Still = 4,
} Moves;

#endif /* common_h */
