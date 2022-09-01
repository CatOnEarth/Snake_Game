#include "Snake_player.h"
#include <SFML/Graphics.hpp>
#include "food.h"
#include <iostream>

using namespace sf;

void Snake_player::draw_player_snake(RenderWindow& window, field &field) {
    for (int ii = 0; ii < length_snake; ++ii) {
        RectangleShape cell(sf::Vector2f(26, 26));
        cell.setPosition(field.coord_cell[num_cell_snake[ii].coord_x][num_cell_snake[ii].coord_y].coord_x + 2, field.coord_cell[num_cell_snake[ii].coord_x][num_cell_snake[ii].coord_y].coord_y + 2);
        cell.setFillColor(Color::Red);
        window.draw(cell);
    }
}


void Snake_player::draw_eyes_player_snake(RenderWindow& window, field& field) {
    sf::CircleShape eye_2;
    eye_2.setFillColor(sf::Color::Black);
    eye_2.setRadius(3);

    sf::CircleShape eye_1;
    eye_1.setFillColor(sf::Color::Black);
    eye_1.setRadius(3);

    if (now_direction == 1) {
        eye_1.setPosition(field.coord_cell[num_cell_snake[0].coord_x][num_cell_snake[0].coord_y].coord_x + 20, field.coord_cell[num_cell_snake[0].coord_x][num_cell_snake[0].coord_y].coord_y + 5);
        eye_2.setPosition(field.coord_cell[num_cell_snake[0].coord_x][num_cell_snake[0].coord_y].coord_x + 20, field.coord_cell[num_cell_snake[0].coord_x][num_cell_snake[0].coord_y].coord_y + 20);
    }
    else if (now_direction == 0) {
        eye_1.setPosition(field.coord_cell[num_cell_snake[0].coord_x][num_cell_snake[0].coord_y].coord_x + 5, field.coord_cell[num_cell_snake[0].coord_x][num_cell_snake[0].coord_y].coord_y + 5);
        eye_2.setPosition(field.coord_cell[num_cell_snake[0].coord_x][num_cell_snake[0].coord_y].coord_x + 20, field.coord_cell[num_cell_snake[0].coord_x][num_cell_snake[0].coord_y].coord_y + 5);
    }
    else if (now_direction == 2) {
        eye_1.setPosition(field.coord_cell[num_cell_snake[0].coord_x][num_cell_snake[0].coord_y].coord_x + 5, field.coord_cell[num_cell_snake[0].coord_x][num_cell_snake[0].coord_y].coord_y + 20);
        eye_2.setPosition(field.coord_cell[num_cell_snake[0].coord_x][num_cell_snake[0].coord_y].coord_x + 20, field.coord_cell[num_cell_snake[0].coord_x][num_cell_snake[0].coord_y].coord_y + 20);
    }
    else if (now_direction == 3) {
        eye_1.setPosition(field.coord_cell[num_cell_snake[0].coord_x][num_cell_snake[0].coord_y].coord_x + 5, field.coord_cell[num_cell_snake[0].coord_x][num_cell_snake[0].coord_y].coord_y + 5);
        eye_2.setPosition(field.coord_cell[num_cell_snake[0].coord_x][num_cell_snake[0].coord_y].coord_x + 5, field.coord_cell[num_cell_snake[0].coord_x][num_cell_snake[0].coord_y].coord_y + 20);
    }
    window.draw(eye_1);
    window.draw(eye_2);
}


void Snake_player::change_direction_player_snake() {
    is_thread_start = true;
    while (true) {
        if (Keyboard::isKeyPressed(Keyboard::Up)) {
            if (now_direction != 2) {
                now_direction = 0;
                break;
            }
        }
        else if (Keyboard::isKeyPressed(Keyboard::Left)) {
            if (now_direction != 1) {
                now_direction = 3;
                break;
            }
        }
        else if (Keyboard::isKeyPressed(Keyboard::Down)) {
            if (now_direction != 0) {
                now_direction = 2;
                break;
            }
        }
        else if (Keyboard::isKeyPressed(Keyboard::Right)) {
            if (now_direction != 3) {
                now_direction = 1;
                break;
            }
        }
    }
    is_thread_start = false;
}


void Snake_player::move_player_snake(sf::RenderWindow& window, field &field, bool &Is_Player_loose) {

    cell tp, tp2_;
    tp = num_cell_snake[0];
    prev_position_tail = num_cell_snake[length_snake - 1];
    for (int ii = 1; ii < length_snake; ++ii) {
        tp2_ = num_cell_snake[ii];
        num_cell_snake[ii] = tp;
        tp = tp2_;
    }


    if (now_direction == 0) {
        if (num_cell_snake[0].coord_y > 1 && field.coord_cell[num_cell_snake[0].coord_x][num_cell_snake[0].coord_y - 1].status != -1) {
            --num_cell_snake[0].coord_y;
        }
        else {
            Is_Player_loose = true;
            return;
        }
    }
    else if (now_direction == 1) {
        if (num_cell_snake[0].coord_x < 30 && field.coord_cell[num_cell_snake[0].coord_x + 1][num_cell_snake[0].coord_y].status != -1) {
            ++num_cell_snake[0].coord_x;
        }
        else {
            Is_Player_loose = true;
            return;
        }
    }
    else if (now_direction == 2) {
        if (num_cell_snake[0].coord_y < 30 && field.coord_cell[num_cell_snake[0].coord_x][num_cell_snake[0].coord_y + 1].status != -1) {
            ++num_cell_snake[0].coord_y;
        }
        else {
            Is_Player_loose = true;
            return;
        }

    }
    else if (now_direction == 3) {
        if (num_cell_snake[0].coord_x > 1 && field.coord_cell[num_cell_snake[0].coord_x - 1][num_cell_snake[0].coord_y].status != -1) {
            --num_cell_snake[0].coord_x;
        }
        else {
            Is_Player_loose = true;
            return;
        }
    }

    field.coord_cell[prev_position_tail.coord_x][prev_position_tail.coord_y].status = -2;
    field.coord_cell[num_cell_snake[0].coord_x][num_cell_snake[0].coord_y].status = -1;
    int tt = 0;
}



void Snake_player::eat_food_player_snake(food &food, field& field) {
    for (int ii = 0; ii < food.num_food_on_field; ++ii) {
        for (int jj = 0; jj < length_snake; ++jj) {
            if (num_cell_snake[jj].coord_x == food.place_of_food[ii].coord_x && 
                num_cell_snake[jj].coord_y == food.place_of_food[ii].coord_y) {
                food.delete_food(ii, field);
                grow_player_snake(field);
            }
        }
    }
}

void Snake_player::grow_player_snake(field& field) {
    ++length_snake;
    num_cell_snake[length_snake - 1] = prev_position_tail;
    field.coord_cell[num_cell_snake[length_snake - 1].coord_x][num_cell_snake[length_snake - 1].coord_y].status = -1;
}



