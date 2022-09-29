//
//  food.hpp
//  Modern Snake
//
//  Created by Efe Arikan on 24.09.22.
//

#ifndef food_hpp
#define food_hpp

#include <stdio.h>
#include <utility>
#include "common.hpp"

class Food
{
public:
	Food();
	Food(COORD loc);
	~Food();
	COORD get_location() const;
	static int static_food_id;
	int food_id;
	bool operator==(const Food& rhs);
private:
	COORD m_loc;
};

#endif /* food_hpp */
