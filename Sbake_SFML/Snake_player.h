#pragma once
#include "field.h"
#include "food.h"

class Snake_player
{
public:
    struct cell {
        int coord_x = -1;
        int coord_y = -1;
    };

    int length_snake = 3;
    int now_direction = 1;
    bool is_thread_start;
    cell prev_position_tail;
    cell num_cell_snake[900]; // координаты €чеек змейки

    void change_direction_player_snake(void);
    void move_player_snake(sf::RenderWindow& window, field &field, bool &Is_Player_loose);
    void draw_player_snake(sf::RenderWindow &window, field &field);
    void draw_eyes_player_snake(sf::RenderWindow& window, field& field);
    void eat_food_player_snake(food &food, field& field);
    void grow_player_snake(field& field);
};
