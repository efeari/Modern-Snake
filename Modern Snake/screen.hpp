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

class Food;
class Snake;
class Screen
{
public:
	Screen();
	~Screen();
	void clear_screen();
	void print_snake(const Snake* snake);
	void refresh_screen(const std::vector<Food>& food_vec);
	void print_food(const Food& food);
private:
	WINDOW* win;
};

#endif /* screen_hpp */
