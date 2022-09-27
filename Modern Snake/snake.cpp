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

void Snake::grow(Food& food) {
	auto fruit_loc = food.get_location();
	switch (this->last_move) {
		case Right:
			fruit_loc.first++;
			break;
		case Left:
			fruit_loc.first--;
			break;
		case Up:
			fruit_loc.second--;
			break;
		case Down:
			fruit_loc.second++;
			break;
		default:
			break;
	}
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

bool Snake::move(std::vector<Food>* food_vec) {
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
	for (auto it = std::begin(body); it != std::end(body) - 1; ++it) {
		auto pair = *it;
		if (pair.first == body.back().first && pair.second == body.back().second) {
			return false;
		}
	}
	auto head = body.back();
	for (auto& food : *food_vec) {
		if (head.first == food.get_location().first && head.second == food.get_location().second) {
			this->grow(food);
			food_vec->erase(std::find(food_vec->begin(), food_vec->end(), food));
		}
	}
	return true;
}

void Snake::change_last_move(const Moves move) {
	this->last_move = move;
}
