#pragma once
#include <SFML/Graphics.hpp>

class field
{
public:
    struct cell {
        int coord_x;
        int coord_y;
        int status;
    };
    const int width = 960;
    const int height = 960;
    cell coord_cell[32][32];
    void fill_cell() {
        for (int ii = 1; ii < 31; ++ii) {
            for (int jj = 1; jj < 31; ++jj) {
                coord_cell[ii][jj].coord_x = ii * 30;
                coord_cell[ii][jj].coord_y = jj * 30;
                coord_cell[ii][jj].status = -2; // -2 свободно; -1 там есть кусок змеи; -3 еда; -4 стенка
            }
        }
        for (int ii = 0; ii < 32; ++ii) {
            coord_cell[ii][0].status = -4;
        }
        for (int ii = 0; ii < 32; ++ii) {
            coord_cell[ii][31].status = -4;
        }
        for (int ii = 0; ii < 32; ++ii) {
            coord_cell[0][ii].status = -4;
        }
        for (int ii = 0; ii < 32; ++ii) {
            coord_cell[31][ii].status = -4;
        }
    }
    //void draw_field(sf::RenderWindow &window, int width, int height);
    void draw_field(sf::RenderWindow& window, field &field);
    void draw_field_border(sf::RenderWindow& window, int width, int height);
};

