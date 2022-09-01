#pragma once

#include <SFML/Graphics.hpp>
#include "field.h"

class food
{
public:
    struct cell {
        int coord_x;
        int coord_y;
    };

    int num_food_on_field = 0;
    cell place_of_food[10];

    void spawn_food(field& field);
    void delete_food(int num, field& field);
    void draw_food(sf::RenderWindow& window, field& field);
};

