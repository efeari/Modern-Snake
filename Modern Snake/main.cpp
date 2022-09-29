#include <iostream>
#include "common.hpp"
#include "food.hpp"
#include "snake.hpp"
#include "screen.hpp"
#include <chrono>
#include <thread>

void play_game();

int main() {
	Screen main_screen;
	switch (main_screen.menu_selection()) {
		case 0:
			play_game();
			break;
			
		case 1:
			main_screen.clear_all();
			break;
	}
	
	return 0;
}

void play_game() {
	GameScreen game_screen;
	ScoreScreen score_screen;
	auto snake = std::make_unique<Snake>();
	std::vector<Food> food_vec;
	food_vec.push_back(Food());
	int food_cnt = 0;
	while (1) {
		if (food_vec.empty()) {
			food_vec.push_back(Food());
		}
		else if (food_cnt == snake->get_speed()) {
			food_vec.pop_back();
			food_cnt = 0;
		}
		if (!snake->move(&food_vec)) {
			break;
		}
		auto snake_ptr = snake.get();
		game_screen.refresh_screen(snake_ptr, food_vec);
		score_screen.refresh_screen(snake_ptr);
		std::this_thread::sleep_for(std::chrono::milliseconds(snake->get_speed()));
		food_cnt++;
	}
}
