//
//  food.cpp
//  Modern Snake
//
//  Created by Efe Arikan on 24.09.22.
//

#include "food.hpp"
#include <iostream>

int Food::static_food_id = 0;

Food::Food() {
	static std::uniform_int_distribution<int> uid_x(1,field_width - 2);
	static std::uniform_int_distribution<int> uid_y(1,field_heigth - 2);
	this->food_id = food_id++;
	m_loc.first = uid_x(rd);
	m_loc.second = uid_y(rd);
}

Food::Food(COORD loc) {
	m_loc = loc;
	this->food_id = food_id++;
}


Food::~Food() {
//	std::cout << "Food destructed" << std::endl;
}

COORD Food::get_location() const {
	return this->m_loc;
}

bool Food::operator==(const Food& rhs) {
  return this->food_id == rhs.food_id;
}
