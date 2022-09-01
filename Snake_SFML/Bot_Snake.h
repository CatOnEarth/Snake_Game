#pragma once

#include "field.h"
#include "food.h"

class Bot_Snake
{
public:
    struct cell {
        int coord_x = -1;
        int coord_y = -1;
    };

    cell num_cell_bot_snake[900]; // координаты €чеек змейки
    cell final_way[900]; 
    int length_bot_snake = 3;
    cell prev_position_tail_bot_snake;
    int now_direction_bot = 3;
    cell selected_food;
    cell finish_long_way;

    void draw_bot_snake(sf::RenderWindow& window, field& field);
    void draw_eyes_bot_snake(sf::RenderWindow& window, field& field);
    void move_bot_snake(sf::RenderWindow& window, field& field, food& food, bool &Is_Bot_loose);
    void grow_bot_snake(field& field);
    bool find_way(field &field, food &food);
    bool if_no_straight_way(field& ff);
    void eat_food_bot_snake(food& food, field& field);
    void select_food(food& food);
    bool choose_food(field& field, food& food);
};
