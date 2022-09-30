#include <iostream>
#include <fstream>
#include <filesystem>
#include "common.hpp"
#include "food.hpp"
#include "snake.hpp"
#include "screen.hpp"
#include "whereami.h"

int play_game();
void save_score(std::vector<int> scores);

int main() {
	Screen main_screen;
	bool continue_game = true;
	while(continue_game)
	switch (main_screen.menu_selection()) {
		case 0: {
			std::vector<int> tmp;
			tmp.push_back(play_game());
			save_score(tmp);
			break;
		}
		case 1: {
			main_screen.clear_all();
			continue_game = 0;
			break;
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

void save_score(std::vector<int> scores) {
	char *path = NULL;
	int length, dirname_length;
	length = wai_getExecutablePath(NULL, 0, NULL);
	path = (char*)malloc(length + 1);
	wai_getExecutablePath(path, length, &dirname_length);
	std::ofstream outf;
	outf.open(std::string(path) + std::string("_Scores.txt"), std::ofstream::out | std::ofstream::app);
	if (!outf) {
		std::cerr << "Error writing\n";
	}
	for (const auto &_s : scores) {
		outf << _s << "\n";
	}
	outf.close();
	free(path);
}

void get_scores() {
	char *path = NULL;
	int length, dirname_length;
	length = wai_getExecutablePath(NULL, 0, NULL);
	path = (char*)malloc(length + 1);
	wai_getExecutablePath(path, length, &dirname_length);
	std::ifstream inf;
	inf.open(std::string(path) + std::string("_Scores.txt"), std::ifstream::in | std::ofstream::app);
	if (!inf) {
		std::cerr << "Error reading\n";
	}
	std::vector<int> scores;
	while (inf) {
		int _score;
		inf >> _score;
		scores.push_back(_score);
	}
	std::sort(scores.begin(), scores.end());
	inf.close();
	std::filesystem::remove(std::string(path) + std::string("_Scores.txt"));
	save_score(scores);
	free(path);
}
