#include <SFML/Graphics.hpp>
#include <thread>
#include <iostream>
#include "Snake_player.h"
#include "field.h"
#include "food.h"
#include "Bot_Snake.h"
#include "FormSFML.h"
#include <fstream>
#include <string>

using namespace sf;
bool Is_Game_end = false;
bool Is_Player_loose = false;
bool Is_Bot_loose = false;
int Total_Score_Player = 0;
int Total_Score_Bot = 0;


// обновление рекорда в файле


void Player_Record_Update() {
	std::fstream record("record.txt");
	string record_str;
	std::getline(record, record_str);
	int record_int = std::stoi(record_str);
	record.close();
	if (record_int < Total_Score_Player) {
		ofstream fout("record.txt");
		fout << std::to_string(Total_Score_Player);
		fout.close();
	}
}


// ѕауза

int Game_Pause(RenderWindow &window, Event &event, bool &Is_Game_pause, Sprite &button_restart, Sprite& button_back, Sprite& pause_button, Thread& thread_ChangeDirection) {
	sf::Sprite play_button;
	play_button.setPosition(1050, 200);

	form::Label click(1000, 350, "Click the arrow");

	sf::Texture play_texture;
	play_texture.loadFromFile("layouts/Play_button.png");

	play_button.setTexture(play_texture);

	window.draw(play_button);
	window.display();
	Is_Game_pause = true;
	window.pollEvent(event);
	sf::sleep(sf::milliseconds(200));
	Vector2i Pos_mouse = Mouse::getPosition(window);
	while (Is_Game_pause) {
		while (window.pollEvent(event)) {

			Pos_mouse = Mouse::getPosition(window);

			if (event.type == Event::Closed) {
				Is_Game_end = true;
				window.close();
			}

			if (event.type == sf::Event::MouseButtonPressed) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					if (button_restart.getGlobalBounds().contains(Pos_mouse.x, Pos_mouse.y)) {
						thread_ChangeDirection.terminate();
						Is_Game_end = false;
						return 1;
					}
					else if (button_back.getGlobalBounds().contains(Pos_mouse.x, Pos_mouse.y)) {
						thread_ChangeDirection.terminate();
						Is_Game_end = true;
						return 0;
					}
					else if (pause_button.getGlobalBounds().contains(Pos_mouse.x, Pos_mouse.y)) {
						Is_Game_pause = false;
					}
				}
			}
		}
	}
	window.draw(pause_button);
	window.draw(click.displayText(40));
	window.display();
	while (!(event.key.code == Keyboard::Up || event.key.code == Keyboard::Down || event.key.code == Keyboard::Left || event.key.code == Keyboard::Right)) {
		window.pollEvent(event);
		Pos_mouse = Mouse::getPosition(window);
		if (event.type == Event::Closed) {
			Is_Game_end = true;
			window.close();
		}
		else if (event.mouseButton.button == sf::Mouse::Left) {
			if (button_restart.getGlobalBounds().contains(Pos_mouse.x, Pos_mouse.y)) {
				thread_ChangeDirection.terminate();
				Is_Game_end = false;
				return 1;
			}
			else if (button_back.getGlobalBounds().contains(Pos_mouse.x, Pos_mouse.y)) {
				thread_ChangeDirection.terminate();
				Is_Game_end = true;
				return 0;
			}
		}
	}
	return 2;
}



// экран основной игры


void Game(RenderWindow &window)
{
	// инициализаци€ начальных переменных
	string score;
	Is_Game_end = false;
	Is_Player_loose = false;
	Is_Bot_loose = false;
	bool Is_Game_pause = false;
	Total_Score_Player = 0;
	Total_Score_Bot = 0;
	bool launched_thread = true;
	sf::Sprite button_restart;
	sf::Texture texture_button_restart;
	texture_button_restart.loadFromFile("layouts/button_restart.png");
	button_restart.setTexture(texture_button_restart);
	button_restart.setPosition(1050, 30);

	sf::Sprite button_back;
	sf::Texture texture_button_back;
	texture_button_back.loadFromFile("layouts/button_back.png");
	button_back.setTexture(texture_button_back);
	button_back.setPosition(1120, 810);

	form::Label score_player_text(1000, 460, "Player: ");
	form::Label score_player(1150, 460, "0");

	form::Label score_bot_text(1000, 580, "Bot: ");
	form::Label score_bot(1100, 580, "0");

	sf::Sprite pause_button;
	pause_button.setPosition(1050, 200);

	sf::Texture pause_texture;
	pause_texture.loadFromFile("layouts/Pause_button.png");

	pause_button.setTexture(pause_texture);

	sf::Sprite play_button;
	play_button.setPosition(1050, 200);

	sf::Texture play_texture;
	play_texture.loadFromFile("layouts/Play_button.png");

	play_button.setTexture(play_texture);

	// »нициализаци€ игрока
	
	Snake_player player_1;
	
	player_1.num_cell_snake[0].coord_x = 17;
	player_1.num_cell_snake[0].coord_y = 15;
	player_1.num_cell_snake[1].coord_x = 16;
	player_1.num_cell_snake[1].coord_y = 15;
	player_1.num_cell_snake[2].coord_x = 15;
	player_1.num_cell_snake[2].coord_y = 15;
	
	// поток считывани€ стелочек
	sf::Thread thread_ChangeDirection(&Snake_player::change_direction_player_snake, &player_1);
	player_1.is_thread_start = false;
	thread_ChangeDirection.launch();
	
	
	while (!player_1.is_thread_start) { // ждемс пока запуститс€ поток(Release не работает туть)
	}


	// инициализаци€ бота
	
	Bot_Snake bot_snake;
	bot_snake.num_cell_bot_snake[0].coord_x = 8;
	bot_snake.num_cell_bot_snake[0].coord_y = 20;
	bot_snake.num_cell_bot_snake[1].coord_x = 9;
	bot_snake.num_cell_bot_snake[1].coord_y = 20;
	bot_snake.num_cell_bot_snake[2].coord_x = 10;
	bot_snake.num_cell_bot_snake[2].coord_y = 20;


	// инциализаци€ пол€
	field field;
	field.fill_cell();
	field.coord_cell[15][15].status = -1;
	field.coord_cell[16][15].status = -1;
	field.coord_cell[17][15].status = -1;
	field.coord_cell[8][20].status = -1;
	field.coord_cell[9][20].status = -1;
	field.coord_cell[10][20].status = -1;
	

	// инициализаци€ еды
	food food;

	sf::Event event;


	while (window.isOpen())	{
		while (window.pollEvent(event))	{
			Vector2i Pos_mouse = Mouse::getPosition(window);

			if (event.type == Event::Closed) {
				Is_Game_end = true;
				window.close();
			}

			if (event.type == Event::LostFocus) {

				window.clear(Color(41, 93, 45));
				field.draw_field(window, field);
				field.draw_field_border(window, field.width, field.height);
				player_1.draw_player_snake(window, field);
				player_1.draw_eyes_player_snake(window, field);
				food.draw_food(window, field);
				bot_snake.draw_bot_snake(window, field);
				bot_snake.draw_eyes_bot_snake(window, field);
				window.draw(button_restart);
				window.draw(button_back);
				window.draw(score_player_text.displayText(40));
				window.draw(score_player.displayText(40));
				window.draw(score_bot_text.displayText(40));
				window.draw(score_bot.displayText(40));
				window.draw(pause_button);
				window.display();

				int result_game_pause = Game_Pause(window, event, Is_Game_pause, button_restart, button_back, pause_button, thread_ChangeDirection);
				if (result_game_pause == 0 || result_game_pause == 1) {
					return;
				}
			}

			if (event.mouseButton.button == sf::Mouse::Left) {
				if (button_restart.getGlobalBounds().contains(Pos_mouse.x, Pos_mouse.y)) {
					thread_ChangeDirection.terminate();
					Is_Game_end = false;
					return;
				} else if (button_back.getGlobalBounds().contains(Pos_mouse.x, Pos_mouse.y)) {
					thread_ChangeDirection.terminate();
					Is_Game_end = true;
					return;
				}
				else if (pause_button.getGlobalBounds().contains(Pos_mouse.x, Pos_mouse.y)) {

					window.clear(Color(41, 93, 45));
					field.draw_field(window, field);
					field.draw_field_border(window, field.width, field.height);
					player_1.draw_player_snake(window, field);
					player_1.draw_eyes_player_snake(window, field);
					food.draw_food(window, field);
					bot_snake.draw_bot_snake(window, field);
					bot_snake.draw_eyes_bot_snake(window, field);
					window.draw(button_restart);
					window.draw(button_back);
					window.draw(score_player_text.displayText(40));
					window.draw(score_player.displayText(40));
					window.draw(score_bot_text.displayText(40));
					window.draw(score_bot.displayText(40));
					window.draw(pause_button);
					window.display();

					int result_game_pause = Game_Pause(window, event, Is_Game_pause, button_restart, button_back, pause_button, thread_ChangeDirection);
					if (result_game_pause == 0 || result_game_pause == 1) {
						return;
					}
				}
				
			}
		}

		window.clear(Color(41, 93, 45));

		field.draw_field(window, field);
		field.draw_field_border(window, field.width, field.height);

		if (launched_thread) {
			launched_thread = false;
			thread_ChangeDirection.terminate();
		}
		player_1.move_player_snake(window, field, Is_Player_loose);
		if (Is_Player_loose) {
			Is_Game_end = true;
			thread_ChangeDirection.terminate();
			Total_Score_Bot = bot_snake.length_bot_snake - 3;
			Total_Score_Player = player_1.length_snake - 3;
			return;
		}
		player_1.eat_food_player_snake(food, field);
		player_1.draw_player_snake(window, field);
		player_1.draw_eyes_player_snake(window, field);
		score_player.setText(std::to_string(player_1.length_snake - 3));

		
		food.spawn_food(field);
		food.draw_food(window, field);
		
		bot_snake.move_bot_snake(window, field, food, Is_Bot_loose);
		if (Is_Bot_loose) {
			Is_Game_end = true;
			thread_ChangeDirection.terminate();
			Total_Score_Bot = bot_snake.length_bot_snake - 3;
			Total_Score_Player = player_1.length_snake - 3;
			return;
		}
		bot_snake.eat_food_bot_snake(food, field);
		bot_snake.draw_bot_snake(window, field);
		bot_snake.draw_eyes_bot_snake(window, field);
		score_bot.setText(std::to_string(bot_snake.length_bot_snake - 3));

		window.draw(button_restart);
		window.draw(button_back);

		window.draw(score_player_text.displayText(40));
		window.draw(score_player.displayText(40));

		window.draw(score_bot_text.displayText(40));
		window.draw(score_bot.displayText(40));
		
		window.draw(pause_button);

		window.display();
		if (!launched_thread) {
			launched_thread = true;
			thread_ChangeDirection.launch();
		}
		sf::sleep(sf::milliseconds(200));
	}
	thread_ChangeDirection.terminate();
}



// экран проигрыша



int loose_game(RenderWindow& window) {
	

	sf::Texture snake_1_texture;
	sf::Texture snake_2_texture;
	snake_2_texture.loadFromFile("layouts/snake_picture_right.png");
	snake_1_texture.loadFromFile("layouts/snake_picture_left.png");

	sf::Sprite snake_image_1;
	sf::Sprite snake_image_2;
	snake_image_1.setPosition(20, 100);
	snake_image_1.setTexture(snake_1_texture);
	snake_image_2.setPosition(770, 100);
	snake_image_2.setTexture(snake_2_texture);
	string name_win, name_loose;
	if (Is_Player_loose) {
		name_win = "Bot Win!";
		name_loose = "Player Dead!";
	}
	else if (Is_Bot_loose) {
		name_win = "Player Win!";
		name_loose = "Bot Dead!";
	}

	form::Label Who_loose(530, 280, name_loose);
	form::Label Who_win(530, 360, name_win);
	form::Label Player_total_score(100, 610, "Total score Player: " + std::to_string(Total_Score_Player));
	form::Label Bot_total_score(900, 610, "Total score Bot: " + std::to_string(Total_Score_Bot));

	sf::Color menu_restart_button(80, 131, 255);
	form::Button menu_button(300, 750, 170, 55, " Main menu", menu_restart_button);
	form::Button restart_button(810, 750, 235, 55, " Restart Game", menu_restart_button);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			Vector2i Pos_mouse = Mouse::getPosition(window);

			if (event.type == sf::Event::Closed)
				window.close();

			if (event.key.code == Mouse::Left) {
				if (menu_button.select(Pos_mouse)) {
					Is_Game_end = true;
					return 1;
				}

				if (restart_button.select(Pos_mouse)) {
					return 0;
				}
				
			}
		}

		window.clear(Color(41, 93, 45));

		window.draw(menu_button.displayButton());
		window.draw(menu_button.displayText());

		window.draw(snake_image_1);
		window.draw(snake_image_2);
		window.draw(Who_win.displayText(60));

		window.draw(Bot_total_score.displayText(40));
		window.draw(Player_total_score.displayText(40));
		window.draw(Who_loose.displayText(40));

		window.draw(restart_button.displayButton());
		window.draw(restart_button.displayText());
		window.display();
	}
}


// начальный экран игры


void main() {
	sf::Color color_start_button(80, 131, 255);
	form::Button button_start(260, 200, 330, 75, " Start Game", color_start_button, 60);
	sf::Sprite back_image;
	sf::Texture texture_back_image;

	sf::Color color_exit_button(80, 131, 255);
	form::Button button_exit(1100, 50, 140, 75, " Exit", color_exit_button, 60);

	texture_back_image.loadFromFile("layouts/snake_start_win_2.png");
	back_image.setTexture(texture_back_image);

	std::fstream record("record.txt");
	string record_str;
	std::getline(record, record_str);
	form::Label record_label(1020, 450, record_str);
	form::Label record_text(1020, 420, "Record:");

	sf::RenderWindow window(sf::VideoMode(1280, 960), "Snake", sf::Style::Close);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {

			Vector2i Pos_mouse = Mouse::getPosition(window);

			if (event.type == sf::Event::Closed) {
				window.close();
			}

			if (event.key.code == Mouse::Left) {
				if (button_start.select(Pos_mouse)) {
					while (!Is_Game_end) {
						Game(window);
						if (Is_Player_loose || Is_Bot_loose) {
							Player_Record_Update();
							std::getline(record, record_str);
							record_label.setText(record_str);
							if (loose_game(window) == 1) {
								break;
							}
							else {
								Is_Player_loose = false;
								Is_Bot_loose = false;
								Is_Game_end = false;
							}
						}
					}
					Is_Player_loose = false;
					Is_Bot_loose = false;
					Is_Game_end = false;
				}

				if (button_exit.select(Pos_mouse)) {
					window.close();
					exit(0);
				}
			}

		}

		window.clear();

		window.draw(back_image);

		window.draw(button_start.displayButton());
		window.draw(button_start.displayText());

		window.draw(button_exit.displayButton());
		window.draw(button_exit.displayText());

		window.draw(record_label.displayText(70));
		window.draw(record_text.displayText(35));

		window.display();
	}
}
