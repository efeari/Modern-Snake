#include <iostream>
#include "common.hpp"
#include "food.hpp"
#include "snake.hpp"
#include "screen.hpp"

int main() {
	Screen screen;
	auto snake = std::make_unique<Snake>(COORD {24,17});
	std::vector<Food> food_vec;
	food_vec.push_back(Food());
	while (1) {
		if (food_vec.empty()) {
			food_vec.push_back(Food());
		}
		screen.clear_screen();
		snake->move(&food_vec);
		screen.print_snake(snake.get());
		screen.refresh_screen(food_vec);
	}
	endwin();
	return 0;
}
