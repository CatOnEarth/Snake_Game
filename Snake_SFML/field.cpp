#include "field.h"
#include <SFML/Graphics.hpp>

/*
void field::draw_field(sf::RenderWindow& window, int width, int height) {
	for (int ii = 20; ii <= width - 20; ii += 20) { // горизонтальные
		sf::RectangleShape line(sf::Vector2f(width - 40, 1));
		line.setFillColor(sf::Color::Green);
		line.setPosition(20, ii);
		line.rotate(0);
		window.draw(line);
	}
	for (int ii = 20; ii <= height - 20; ii += 20) { // вертикальные
		sf::RectangleShape line(sf::Vector2f(height - 40, 1));
		line.setFillColor(sf::Color::Green);
		line.setPosition(ii, 20);
		line.rotate(90);
		window.draw(line);
	}
}
*/

void field::draw_field(sf::RenderWindow& window, field &field) {
	sf::RectangleShape line(sf::Vector2f(30, 30));
	for (int ii = 1; ii < 31; ++ii) {
		for (int jj = 1; jj < 31; ++jj) {
			if ((jj + ii) % 2 == 0) {
				line.setFillColor(sf::Color(41, 228, 45));
			}
			else {
				line.setFillColor(sf::Color(41, 158, 45));
			}
			line.setPosition(field.coord_cell[ii][jj].coord_x, field.coord_cell[ii][jj].coord_y);
			window.draw(line);
		}
	}
}


void field::draw_field_border(sf::RenderWindow& window, int width, int height) {
	sf::RectangleShape line(sf::Vector2f(height, 30));
	line.setFillColor(sf::Color(41, 63, 45));
	line.setPosition(0, 0);
	line.rotate(0);
	window.draw(line);

	sf::RectangleShape line2(sf::Vector2f(height, 30));
	line2.setFillColor(sf::Color(41, 63, 45));
	line2.setPosition(0, 930);
	line2.rotate(0);
	window.draw(line2);

	sf::RectangleShape line3(sf::Vector2f(height - 20, 30));
	line3.setFillColor(sf::Color(41, 63, 45));
	line3.setPosition(30, 20);
	line3.rotate(90);
	window.draw(line3);
	
	sf::RectangleShape line4(sf::Vector2f(height, 30));
	line4.setFillColor(sf::Color(41, 63, 45));
	line4.setPosition(960, 0);
	line4.rotate(90);
	window.draw(line4);
}
