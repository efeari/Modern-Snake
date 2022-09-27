//
//  snake.cpp
//  Modern Snake
//
//  Created by Efe Arikan on 24.09.22.
//

#include "snake.hpp"

Snake::Snake(COORD start_coord) {
	this->body.push_back(start_coord);
	start_coord.second++;
	this->body.push_back(start_coord);
}

Snake::~Snake() {
}

std::vector<COORD> Snake::get_body() const{
	return this->body;
}

int Snake::get_length() const{
	return this->m_length;
}

void Snake::grow(const COORD& fruit_loc) {
	this->body.push_back(fruit_loc);
}

void Snake::set_head(const COORD* new_head) {
	this->body.back() = *new_head;
}

void Snake::move_up() {
	auto tmp_coord = std::make_unique<COORD>(this->body.back());
	tmp_coord->second--;
	this->set_head(tmp_coord.get());
}

void Snake::move_down() {
	auto tmp_coord = std::make_unique<COORD>(this->body.back());
	tmp_coord->second++;
	this->set_head(tmp_coord.get());
}

void Snake::move_right() {
	auto tmp_coord = std::make_unique<COORD>(this->body.back());
	tmp_coord->first++;
	this->set_head(tmp_coord.get());
}

void Snake::move_left() {
	auto tmp_coord = std::make_unique<COORD>(this->body.back());
	tmp_coord->first--;
	this->set_head(tmp_coord.get());
}

void Snake::move(std::vector<Food>* food_vec) {
	int ch = getch();
	switch(ch) {
		case KEY_LEFT:
			if (this->last_move != Right)
				this->change_last_move(Left);
			break;
		case KEY_RIGHT:
			if (this->last_move != Left)
				this->change_last_move(Right);
			break;
		case KEY_UP:
			if (this->last_move != Down)
				this->change_last_move(Up);
			break;
		case KEY_DOWN:
			if (this->last_move != Up)
				this->change_last_move(Down);
			break;
		default:
			break;
	}
	std::shift_left(this->body.begin(), this->body.end(), 1);
	switch (this->last_move) {
		case Right:
			this->move_right();
			break;
		case Left:
			this->move_left();
			break;
		case Up:
			this->move_up();
			break;
		case Down:
			this->move_down();
			break;
		default:
			break;
	}
	
	for (auto&& [first,second] : body) {
		for (auto& food : *food_vec) {
			if (first == food.get_location().first && second == food.get_location().second) {
				food.get_location();
				this->eat_food(&food);
				food_vec->erase(std::find(food_vec->begin(), food_vec->end(), food));
			}
		}
	}
}

void Snake::change_last_move(const Moves move) {
	this->last_move = move;
}

void Snake::eat_food(Food* food) {
	this->grow(food->get_location());
}


