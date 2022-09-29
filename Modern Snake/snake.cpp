//
//  snake.cpp
//  Modern Snake
//
//  Created by Efe Arikan on 24.09.22.
//

#include "snake.hpp"

Snake::Snake() {
	COORD start_coord;
	static std::uniform_int_distribution<int> uid_x(1,field_width - 2);
	static std::uniform_int_distribution<int> uid_y(1,field_heigth - 2);
	start_coord.first = uid_x(rd);
	start_coord.second = uid_y(rd);
	this->body.push_back(start_coord);
	static std::uniform_int_distribution<int> uid(0,3);
	this->last_move = Moves(uid(rd));
}
Snake::Snake(COORD start_coord, Moves move) {
	this->body.push_back(start_coord);
	this->last_move = move;
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
	this->score++;
	this->set_speed(this->get_speed() - 5);
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

void check_limits(COORD* loc) {
	if (loc->first < 1) {
		loc->first = field_width - 1;
	}
	else if (loc->first >= field_width - 1) {
		loc->first = 1;
	}
	if (loc->second < 1) {
		loc->second = field_heigth - 1;
	}
	else if (loc->second >= field_heigth - 1) {
		loc->second = 1;
	}
	
}

void Snake::set_speed(int new_speed) {
	if (new_speed > 1)
		this->speed = new_speed;
}

int Snake::get_speed() const {
	return this->speed;
}

bool Snake::move(std::vector<Food>* food_vec) {
	int ch = getch();
	flushinp();
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
	
	check_limits(&body.back());
	for (auto it = std::begin(body); it != std::end(body) - 1; ++it) {
		auto pair = *it;
		if (pair.first == body.back().first && pair.second == body.back().second) {
			return false;
		}
		check_limits(&pair);
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

int Snake::get_score() const{
	return this->score;
}
