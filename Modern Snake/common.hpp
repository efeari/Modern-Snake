//
//  common.hpp
//  Modern Snake
//
//  Created by Efe Arikan on 24.09.22.
//

#ifndef common_h
#define common_h

#include <random>

static std::random_device rd;
static std::mt19937 rng{rd()};

typedef std::pair<int, int> COORD;

typedef enum : int {
	Right = 0,
	Left = 1,
	Up = 2,
	Down = 3,
	Still = 4,
} Moves;

#endif /* common_h */
