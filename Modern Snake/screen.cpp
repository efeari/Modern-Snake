//
//  screen.cpp
//  Modern Snake
//
//  Created by Efe Arikan on 26.09.22.
//

#include "screen.hpp"

Screen::Screen() {
	auto src = initscr();
	keypad(stdscr, TRUE);
	cbreak();
	curs_set(0);
	this->win = newwin(field_heigth, field_width, 0, 0);
	nodelay(src, true);
	noecho();
	wrefresh(this->win);
}

Screen::~Screen() {
}

void Screen::clear_screen() {
	wclear(this->win);
}

void Screen::close_screen() {
	wrefresh(this->win);
	delwin(this->win);
}

void Screen::clear_all() {
	clear();
	refresh();
}

void Screen::draw_menu(int item) {
	int c;
	const char mainmenu[] = "Main Menu";
	std::array<std::string,3> menu = { "Play",
		"Exit",
		"Credits"
	};
	clear();
	mvaddstr(0, 31, mainmenu);
	for( c = 0; c < MAX_MENU; c++)
	{
		if( c == item)
			attron(A_REVERSE);
		mvaddstr(3 + (c * 2), 20, menu[c].c_str());
		attroff(A_REVERSE);
	}
	mvaddstr(17, 20, "Use arrow keys to move; Enter to select:");
	refresh();
}

int Screen::menu_selection() {
	draw_menu(0);
	int key;
	int menuitem = 0;
	do
	{
		key = getch();
		switch(key)
		{
				case KEY_DOWN:
					menuitem++;
					if(menuitem > MAX_MENU - 1) menuitem = 0;
					break;
				case KEY_UP:
					menuitem--;
					if(menuitem < 0) menuitem = MAX_MENU - 1;
					break;
				default:
					break;
		}
		this->draw_menu(menuitem);
	} while(key != '\n');
	clear();
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	return menuitem;
}


ScoreScreen::ScoreScreen() {
	this->win = newwin(score_heigth, score_width, field_heigth - score_heigth*1.75, field_width+5);
	box(this->win, 1, 1);
	wrefresh(this->win);
}

ScoreScreen::~ScoreScreen() {
}

void ScoreScreen::refresh_screen(const Snake* snake) {
	wclear(this->win);
	box(this->win, 1, 2);
	int score = snake->get_score();
	mvwprintw(this->win, 1, 2, (std::string("Current Score: ") + std::to_string(score)).c_str());
	wrefresh(this->win);
}

GameScreen::GameScreen() {
	noecho();
	this->win = newwin(field_heigth, field_width, 0, 0);
	box(this->win, 0, 0);
	wrefresh(this->win);
}

GameScreen::~GameScreen() {
}

void GameScreen::print_snake(const Snake* snake) {
	for (auto&& [first,second] : snake->get_body()) {
		mvwprintw(this->win, second, first, "o");
	}
}

void GameScreen::refresh_screen(const Snake* snake, const std::vector<Food>& food_vec) {
	wclear(this->win);
	this->print_snake(snake);
	box(this->win, 0, 0);
	for (const auto& food : food_vec) {
		this->print_food(food);
	}
	wrefresh(this->win);
}

void GameScreen::print_food(const Food& food) {
	mvwprintw(this->win, food.get_location().second, food.get_location().first, "x");
}
