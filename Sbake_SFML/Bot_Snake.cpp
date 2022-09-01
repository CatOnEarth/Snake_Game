#include "Bot_Snake.h"
#include "field.h"
#include <iostream>

void Bot_Snake::draw_bot_snake(sf::RenderWindow& window, field& field) {
    for (int ii = 0; ii < length_bot_snake; ++ii) {
        sf::RectangleShape cell(sf::Vector2f(26, 26));
        cell.setPosition(field.coord_cell[num_cell_bot_snake[ii].coord_x][num_cell_bot_snake[ii].coord_y].coord_x + 2, field.coord_cell[num_cell_bot_snake[ii].coord_x][num_cell_bot_snake[ii].coord_y].coord_y + 2);
        cell.setFillColor(sf::Color(151, 85, 255));
        window.draw(cell);
    }
}


void Bot_Snake::draw_eyes_bot_snake(sf::RenderWindow& window, field& field) {
    sf::CircleShape eye_2;
    eye_2.setFillColor(sf::Color::Black);
    eye_2.setRadius(3);

    sf::CircleShape eye_1;
    eye_1.setFillColor(sf::Color::Black);
    eye_1.setRadius(3);

    if (now_direction_bot == 1) {
        eye_1.setPosition(field.coord_cell[num_cell_bot_snake[0].coord_x][num_cell_bot_snake[0].coord_y].coord_x + 20, field.coord_cell[num_cell_bot_snake[0].coord_x][num_cell_bot_snake[0].coord_y].coord_y + 5);
        eye_2.setPosition(field.coord_cell[num_cell_bot_snake[0].coord_x][num_cell_bot_snake[0].coord_y].coord_x + 20, field.coord_cell[num_cell_bot_snake[0].coord_x][num_cell_bot_snake[0].coord_y].coord_y + 20);
    }
    else if (now_direction_bot == 0) {
        eye_1.setPosition(field.coord_cell[num_cell_bot_snake[0].coord_x][num_cell_bot_snake[0].coord_y].coord_x + 5, field.coord_cell[num_cell_bot_snake[0].coord_x][num_cell_bot_snake[0].coord_y].coord_y + 5);
        eye_2.setPosition(field.coord_cell[num_cell_bot_snake[0].coord_x][num_cell_bot_snake[0].coord_y].coord_x + 20, field.coord_cell[num_cell_bot_snake[0].coord_x][num_cell_bot_snake[0].coord_y].coord_y + 5);
    }
    else if (now_direction_bot == 2) {
        eye_1.setPosition(field.coord_cell[num_cell_bot_snake[0].coord_x][num_cell_bot_snake[0].coord_y].coord_x + 5, field.coord_cell[num_cell_bot_snake[0].coord_x][num_cell_bot_snake[0].coord_y].coord_y + 20);
        eye_2.setPosition(field.coord_cell[num_cell_bot_snake[0].coord_x][num_cell_bot_snake[0].coord_y].coord_x + 20, field.coord_cell[num_cell_bot_snake[0].coord_x][num_cell_bot_snake[0].coord_y].coord_y + 20);
    }
    else if (now_direction_bot == 3) {
        eye_1.setPosition(field.coord_cell[num_cell_bot_snake[0].coord_x][num_cell_bot_snake[0].coord_y].coord_x + 5, field.coord_cell[num_cell_bot_snake[0].coord_x][num_cell_bot_snake[0].coord_y].coord_y + 5);
        eye_2.setPosition(field.coord_cell[num_cell_bot_snake[0].coord_x][num_cell_bot_snake[0].coord_y].coord_x + 5, field.coord_cell[num_cell_bot_snake[0].coord_x][num_cell_bot_snake[0].coord_y].coord_y + 20);
    }
    window.draw(eye_1);
    window.draw(eye_2);
}


bool Bot_Snake::choose_food(field& ff, food& food) {
    int dj[4] = { 1, 0, -1, 0 };
    int di[4] = { 0, 1, 0, -1 };
    int d, jj, ii, k, d2;
    d2 = 1000;
    bool stop;
    cell finish;
    for (int mm = 0; mm < food.num_food_on_field; ++mm) {
        field temp_field = ff;
        finish.coord_x = food.place_of_food[mm].coord_x;
        finish.coord_y = food.place_of_food[mm].coord_y;
        d = 0;
        temp_field.coord_cell[num_cell_bot_snake[0].coord_x][num_cell_bot_snake[0].coord_y].status = 0;
        do {
            stop = true;
            for (ii = 1; ii < 31; ++ii) {
                for (jj = 1; jj < 31; ++jj) {
                    if (temp_field.coord_cell[ii][jj].status == d) {
                        for (k = 0; k < 4; ++k) {
                            int i = ii + di[k];
                            int j = jj + dj[k];
                            if (i >= 1 && i < 31 && j >= 1 && j < 31 && (temp_field.coord_cell[i][j].status == -2 || temp_field.coord_cell[i][j].status == -3) && temp_field.coord_cell[i][j].status != -1) {
                                stop = false;
                                temp_field.coord_cell[i][j].status = d + 1;
                            }
                        }
                    }
                }
            }
            ++d;
        } while (!stop && temp_field.coord_cell[finish.coord_x][finish.coord_y].status == -3);
        if (d < d2 && temp_field.coord_cell[finish.coord_x][finish.coord_y].status != -3) {
            d2 = d;
            selected_food = finish;
        }
    }
    if (d2 == 1000) {
        return false;
    }
    else {
        return true;
    }
}



bool Bot_Snake::if_no_straight_way(field& ff) {
    field temp_field = ff;
    bool stop;
    int dj[4] = { 1, 0, -1, 0 };
    int di[4] = { 0, 1, 0, -1 };
    int d = 0;
    temp_field.coord_cell[num_cell_bot_snake[0].coord_x][num_cell_bot_snake[0].coord_y].status = 0;

    do {
        stop = true;
        for (int ii = 1; ii < 31; ++ii) {
            for (int jj = 1; jj < 31; ++jj) {
                if (temp_field.coord_cell[ii][jj].status == d) {
                    for (int k = 0; k < 4; ++k) {
                        int i = ii + di[k];
                        int j = jj + dj[k];
                        if (i >= 1 && i < 31 && j >= 1 && j < 31 && temp_field.coord_cell[i][j].status == -2 && temp_field.coord_cell[i][j].status != -1) {
                            stop = false;
                            temp_field.coord_cell[i][j].status = d + 1;
                            finish_long_way.coord_x = i;
                            finish_long_way.coord_y = j;
                        }
                    }
                }
            }
        }
        ++d;
    } while (!stop);
    if (d == 1) {
        return false;
    }
    else {
        return true;
    }
}


bool Bot_Snake::find_way(field &ff, food & food) {
    field temp_field = ff;
    int dj[4] = { 1, 0, -1, 0 };
    int di[4] = {0, 1, 0, -1};
    int d, jj, ii, k;
    int length_way = -1;
    bool stop;

    cell finish;
    if (choose_food(temp_field, food)) {
        finish.coord_x = selected_food.coord_x;
        finish.coord_y = selected_food.coord_y;
    }
    else if (if_no_straight_way(ff)){
        finish.coord_x = finish_long_way.coord_x;
        finish.coord_y = finish_long_way.coord_y;
        temp_field.coord_cell[finish.coord_x][finish.coord_y].status = -3;
        
    }
    else {
        return false;
    }

    if (temp_field.coord_cell[num_cell_bot_snake[0].coord_x][num_cell_bot_snake[0].coord_y].status == -4 || temp_field.coord_cell[finish.coord_x][finish.coord_y].status == -4) {
        return false;
    }

    d = 0;
    temp_field.coord_cell[num_cell_bot_snake[0].coord_x][num_cell_bot_snake[0].coord_y].status = 0;
    do {
        stop = true;
        for (ii = 1; ii < 31; ++ii) {
            for (jj = 1; jj < 31; ++jj) {
                if (temp_field.coord_cell[ii][jj].status == d) {
                    for (k = 0; k < 4; ++k) {
                        int i = ii + di[k];
                        int j = jj + dj[k];
                        if (i >= 1 && i < 31 && j >= 1 && j < 31 && (temp_field.coord_cell[i][j].status == -2 || temp_field.coord_cell[i][j].status == -3) && temp_field.coord_cell[i][j].status != -1) {
                            stop = false;
                            temp_field.coord_cell[i][j].status = d + 1;
                        }
                    }
                }
            }
        }
        ++d;
    } while (!stop && temp_field.coord_cell[finish.coord_x][finish.coord_y].status == -3);

    if (temp_field.coord_cell[finish.coord_x][finish.coord_y].status == -3) {
        return false;
    }

    length_way = temp_field.coord_cell[finish.coord_x][finish.coord_y].status;

    ii = finish.coord_x;
    jj = finish.coord_y;

    d = length_way;
    while (d > 0) {
        final_way[d].coord_y = jj;
        final_way[d].coord_x = ii;
        --d;
        for (k = 0; k < 4; ++k) {
            int i = ii + di[k];
            int j = jj + dj[k];
            if (i >= 1 && i < 31 && j >= 1 && j < 31 && temp_field.coord_cell[i][j].status == d) {
                jj += dj[k];
                ii += di[k];
                break;
            }
        }
    }
    final_way[0].coord_x = num_cell_bot_snake[0].coord_x;
    final_way[0].coord_y = num_cell_bot_snake[0].coord_y;
    return true;
}



void Bot_Snake::move_bot_snake(sf::RenderWindow& window, field& field, food &food, bool &Is_Bot_loose) {
    

    cell tp, tp2_;
    tp = num_cell_bot_snake[0];
    prev_position_tail_bot_snake = num_cell_bot_snake[length_bot_snake - 1];
    for (int ii = 1; ii < length_bot_snake; ++ii) {
        tp2_ = num_cell_bot_snake[ii];
        num_cell_bot_snake[ii] = tp;
        tp = tp2_;
    }

    if (find_way(field, food) == true) {
        if (final_way[1].coord_x > num_cell_bot_snake[0].coord_x) {
            now_direction_bot = 1;
        }
        else if (final_way[1].coord_x < num_cell_bot_snake[0].coord_x) {
            now_direction_bot = 3;
        }
        else if (final_way[1].coord_y > num_cell_bot_snake[0].coord_y) {
            now_direction_bot = 2;
        }
        else if (final_way[1].coord_y < num_cell_bot_snake[0].coord_y) {
            now_direction_bot = 0;
        }
    }
    else {
        Is_Bot_loose = true;
        return;
    }

    for (int ii = 0; ii < length_bot_snake; ++ii) {
        field.coord_cell[num_cell_bot_snake[ii].coord_x][num_cell_bot_snake[ii].coord_y].status = -2;
    }
    field.coord_cell[prev_position_tail_bot_snake.coord_x][prev_position_tail_bot_snake.coord_y].status = -2;

    if (now_direction_bot == 0) {
        --num_cell_bot_snake[0].coord_y;
    }
    else if (now_direction_bot == 1) {
        ++num_cell_bot_snake[0].coord_x;
    }
    else if (now_direction_bot == 2) {
        ++num_cell_bot_snake[0].coord_y;
    }
    else if (now_direction_bot == 3) {
        --num_cell_bot_snake[0].coord_x;
    }

    for (int ii = 0; ii < length_bot_snake; ++ii) {
        field.coord_cell[num_cell_bot_snake[ii].coord_x][num_cell_bot_snake[ii].coord_y].status = -1;
    }
    int tt = 0;
}


void Bot_Snake::eat_food_bot_snake(food& food, field& field) {
    for (int ii = 0; ii < food.num_food_on_field; ++ii) {
        for (int jj = 0; jj < length_bot_snake; ++jj) {
            if (num_cell_bot_snake[jj].coord_x == food.place_of_food[ii].coord_x &&
                num_cell_bot_snake[jj].coord_y == food.place_of_food[ii].coord_y) {
                food.delete_food(ii, field);
                grow_bot_snake(field);
            }
        }
    }
}


void Bot_Snake::grow_bot_snake(field& field) {
    ++length_bot_snake;
    num_cell_bot_snake[length_bot_snake - 1] = prev_position_tail_bot_snake;
    field.coord_cell[num_cell_bot_snake[length_bot_snake - 1].coord_x][num_cell_bot_snake[length_bot_snake - 1].coord_y].status = -1;
}
