//
//  screen.cpp
//  Modern Snake
//
//  Created by Efe Arikan on 26.09.22.
//

#include "screen.hpp"

Screen::Screen() {
	initscr();
	keypad(stdscr, TRUE);
	noecho();
	cbreak();
	curs_set(0);
	timeout(500);
	win = newwin(24, 80, 0, 0);
	refresh();
	box(this->win, 0, 0);
	wrefresh(this->win);
}

Screen::~Screen() {
	
}

void Screen::clear_screen() {
	wclear(this->win);
}

void Screen::print_snake(const Snake* snake) {
	for (auto&& [first,second] : snake->get_body()) {
		mvwprintw(this->win, second, first, "o");
	}
}

void Screen::refresh_screen(const std::vector<Food>& food_vec) {
	box(this->win, 0, 0);
	for (const auto& food : food_vec) {
		this->print_food(food);
	}
	wrefresh(this->win);
}

void Screen::print_food(const Food& food) {
	mvwprintw(this->win, food.get_location().second, food.get_location().first, "x");
}
