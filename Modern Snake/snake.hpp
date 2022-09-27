//
//  snake.hpp
//  Modern Snake
//
//  Created by Efe Arikan on 24.09.22.
//

#ifndef snake_hpp
#define snake_hpp

#include "food.hpp"
#include "common.hpp"
#include "screen.hpp"

class Snake
{
public:
	Snake(COORD start_coord);
	~Snake();
	int get_length() const;
	std::vector<COORD> get_body() const;
	void grow(Food& food);
	bool move(std::vector<Food>* food_vec);
	void set_head(const COORD* new_head);
	void move_right();
	void move_left();
	void move_up();
	void move_down();
	void change_last_move(const Moves move);
	
private:
	int m_length = 1;
	std::vector<COORD> body; // Has to be reversed for efficiency. Head = last item, tail = first item.
	Moves last_move = Up;
};

#endif /* snake_hpp */
