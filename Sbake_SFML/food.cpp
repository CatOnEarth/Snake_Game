#include "food.h"

void food::spawn_food(field& field) {
    if (num_food_on_field == 0) {
        std::srand(std::time(nullptr));
        int num_add = std::rand() % 5 + 1;
        //int num_add = 0;
        for (int ii = 0; ii < num_add; ++ii) {
            do {
                place_of_food[num_food_on_field].coord_x = std::rand() % 29 + 1;
                place_of_food[num_food_on_field].coord_y = std::rand() % 29 + 1;
            } while (field.coord_cell[place_of_food[num_food_on_field].coord_x][place_of_food[num_food_on_field].coord_y].status == -1 || field.coord_cell[place_of_food[num_food_on_field].coord_x][place_of_food[num_food_on_field].coord_y].status == -3);
            field.coord_cell[place_of_food[num_food_on_field].coord_x][place_of_food[num_food_on_field].coord_y].status = -3;
            ++num_food_on_field;
        }
    }
}

void food::draw_food(sf::RenderWindow& window, field& field) {
    for (int ii = 0; ii < num_food_on_field; ++ii) {
        sf::Sprite food;
        sf::Texture texture_food;
        texture_food.loadFromFile("layouts/food_apple.png");
        food.setTexture(texture_food);
        food.setPosition(field.coord_cell[place_of_food[ii].coord_x][place_of_food[ii].coord_y].coord_x - 4, field.coord_cell[place_of_food[ii].coord_x][place_of_food[ii].coord_y].coord_y - 3);
        window.draw(food);
    }
}

void food::delete_food(int num, field& field) {
    if (num != num_food_on_field - 1) {
        for (int ii = num; ii < num_food_on_field - 1; ++ii) {
            place_of_food[ii] = place_of_food[ii + 1];
        }
    }
    place_of_food[num_food_on_field - 1].coord_x = -1;
    place_of_food[num_food_on_field - 1].coord_y = -1;
    
    --num_food_on_field;
}