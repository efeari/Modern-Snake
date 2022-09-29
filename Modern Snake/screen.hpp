//
//  screen.hpp
//  Modern Snake
//
//  Created by Efe Arikan on 26.09.22.
//

#ifndef screen_hpp
#define screen_hpp

#include <stdio.h>
#include <ncurses.h>
#include "snake.hpp"
#include <vector>
#include "common.hpp"

class Food;
class Snake;
class Screen
{
public:
	Screen();
	~Screen();
	void clear_screen();
	void close_screen();
	int menu_selection();
	void clear_all();
	
private:
	WINDOW* win;
	void draw_menu(int item);
	
};

class ScoreScreen: public Screen
{
public:
	ScoreScreen();
	~ScoreScreen();
	void refresh_screen(const Snake* snake);
	
private:
	WINDOW* win;
};

class GameScreen: public Screen
{
public:
	GameScreen();
	~GameScreen();
	void print_snake(const Snake* snake);
	void refresh_screen(const Snake* snake, const std::vector<Food>& food_vec);
	void print_food(const Food& food);
	
private:
	WINDOW* win;
};
#endif /* screen_hpp */
