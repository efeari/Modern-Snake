//
//  food.cpp
//  Modern Snake
//
//  Created by Efe Arikan on 24.09.22.
//

#include "food.hpp"
#include <iostream>

std::mt19937 rng;

int Food::food_id = 0;

Food::Food() {
	std::cout << "Food constructed" << std::endl;
	food_id++;
	std::uniform_int_distribution<int> distr(2, 28);
	m_loc.first = distr(rng);
	m_loc.second = distr(rng);
}

Food::~Food() {
	std::cout << "Food destructed" << std::endl;
}

COORD Food::get_location() const {
	return this->m_loc;
}

bool Food::operator==(const Food& rhs) {
  return this->food_id == rhs.food_id;
}
