#include <iostream>
#include <fstream>
#include <filesystem>
#include "common.hpp"
#include "food.hpp"
#include "snake.hpp"
#include "screen.hpp"
#include <set>
#include <functional>

int play_game();
bool save_score(int score);
bool get_scores(std::set<int, std::greater<int>>* highScores);

int main() {
	Screen main_screen;
	bool continue_game = true;
	std::set<int, std::greater<int>> highScores;
	while(continue_game) {
		get_scores(&highScores);
		switch (main_screen.menu_selection(highScores)) {
			case 0: {
				save_score(play_game());
				break;
			}
			case 1: {
				main_screen.clear_all();
				continue_game = 0;
				break;
			}
		}
	}
	return 0;
}

int play_game() {
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
			return snake->get_score();
		}
		auto snake_ptr = snake.get();
		game_screen.refresh_screen(snake_ptr, food_vec);
		score_screen.refresh_screen(snake_ptr);
		std::this_thread::sleep_for(std::chrono::milliseconds(snake->get_speed()));
		food_cnt++;
	}
}

bool save_score(int score) {
	std::ofstream outf;
	outf.open(("Modern Snake Scores.txt"), std::ofstream::out | std::ofstream::app);
	if (!outf) {
		return false;
	}
	else
		outf << score << "\n";
	return true;
}

bool get_scores(std::set<int, std::greater<int>>* highScores) {
	std::ifstream inf;
	inf.open(("Modern Snake Scores.txt"), std::ifstream::in);
	if (!inf) {
		return false;
	}
	int tmp;
	while (inf >> tmp) {
		highScores->insert(tmp);
	}
	inf.close();
	return true;
}
