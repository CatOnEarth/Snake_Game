#pragma once

#include <SFML/Graphics.hpp>
#include <string>
//#include "EllipseShape.h"

using namespace std;
using namespace sf;

namespace form {
	Font None;				// Шрифт первичная инициализация

	class Label {
	public:
		string text;	//Текст
	protected:
		double x;		//Координата x
		double y;		//Координата y

		Text TXT;		//Отображаемый текст
		int size = 20;

	public:
		Label(double _x = 0, double _y = 0, string _text = "Label")
		{
			None.loadFromFile("arial.ttf");			//передаем нашему шрифту файл шрифта
			x = _x;
			y = _y;
			text = _text;	
			//size = _size;// загружает текст
			TXT.setFont(None);							// загружаем фрифт
			TXT.setCharacterSize(size); 					// в пикселях, а не точках!
			//TXT.setColor(Color::White);					// устанавливаем цвет выводимого текста
			TXT.setPosition(x, y);						// позиция текста
		}
		Text displayText(int ss)
		{
			TXT.setString(text);						// загружаем в выводимый текст загружаемый текст
			TXT.setCharacterSize(ss);
			return TXT;
		}
		void setText(string change_text) {
			text = change_text;
		}
	};

	class Button : public Label {
	protected:
		double width;		// Ширина Кнопки
		double height;		// Высота Кнопки
		RectangleShape BOX;	// Создаем прямоугольник с размером width, height
		sf::Color color;
		int size_text;
	public:
		Button(double _x = 0, double _y = 0, double _width = 150, double _height = 30, string _text = "Hello", sf::Color _color = sf::Color::Blue, int _size_text = 40)
		{
			None.loadFromFile("arial.ttf");			//передаем нашему шрифту файл шрифта
			x = _x;
			y = _y;
			width = _width;
			height = _height;
			text = _text;		
			color = _color;
			size_text = _size_text;
			TXT.setFont(None);							// загружаем фрифт
			TXT.setCharacterSize(size_text); 					// в пикселях, а не точках!
			TXT.setPosition(x, y);						// позиция текста

			BOX.setSize(Vector2f(width, height));		// размер кнопки
			BOX.setPosition(x, y);						// координаты кнопки
			BOX.setFillColor(color);	// цвет кнопки
			BOX.setOutlineThickness(2);					// Контур X пикселей
			BOX.setOutlineColor(color);		// Цвет контура
		}
		//Проверка нажатия на кнопку
		bool select(Vector2i _mouse)
		{
			if ((_mouse.x > x&& _mouse.x < x + width) && (_mouse.y > y&& _mouse.y < y + height)) {
				return  true;
			}
			else {
				return false;
			}
		}
		//Вывод Текста
		Text displayText()
		{
			TXT.setString(text);  // загружаем в выводимый текст загружаемый текст
			return TXT;
		}
		//Вывод кнопки
		RectangleShape displayButton()
		{
			return BOX;
		}


	};

	class Input : public Button {
	protected:
		bool focus;
	public:
		Input(double _x = 0, double _y = 0, double _width = 150, double _height = 30, string _text = "")
		{
			x = _x;
			y = _y;
			width = _width;
			height = _height;
			text = _text;								// загружает текст
			focus = false;								// фокус поля ввода

			TXT.setFont(None);							// загружаем фрифт
			TXT.setCharacterSize(20); 					// в пикселях, а не точках!
			//TXT.setColor(Color::Black);					// устанавливаем цвет выводимого текста
			TXT.setPosition(x, y);						// позиция текста

			BOX.setSize(Vector2f(width, height));		// размер поля ввода
			BOX.setPosition(x, y);						// координаты поля ввода
			BOX.setFillColor(Color::White);	// цвет кнопки
		}
		//метод .reText( char ) изменяет текст внутри класса Типа данных Input
		void reText(char _tmp)
		{
			text.erase(text.size() - 1);

			if (_tmp != 8) {
				text += _tmp;
			}
			else {
				if (text.size() > 0) {
					text.erase(text.size() - 1);
				}

			}
			text += "|";
			TXT.setString(text);
		}

		// Проверка Фокуса Input
		bool select()
		{
			return focus;
		}

		// Установка Фокуса Input
		bool select(Vector2i _mouse)
		{
			if ((_mouse.x > x&& _mouse.x < x + width) && (_mouse.y > y&& _mouse.y < y + height)) { 	//Если нажат клаиша над объектом Input...
				focus = true;																	   	// Фокус true
				text += "|";																		// В конец строки добаляем | (что бы понимать что input в фокусе)
			}
			else {																				//...Иначе если нажатие произошло не над объектом, то...
				if (text.size() > 0) {																// проверка последнего символа(иначе вылетает)
					if (text[text.size() - 1] == 124) {													// если символ | ...
						text.erase(text.size() - 1);														// ... то удаляем его
					}
				}
				focus = false;																		// устанавливаем фокус false
			}
			return focus;
		}

		//Вывод Текста
		Text displayText()
		{
			TXT.setString(text);						// загружаем в выводимый текст загружаемый текст
			return TXT;
		}

		//Вывод фона Input
		RectangleShape displayBOX()
		{
			return BOX;
		}

		//Для того, что бы считать текст с поля Ipnut необходимо пременить  readText() который возвращает string
		string readText()
		{
			if (text[text.size() - 1] == 124) { 	// удаляем (если есть) символ |
				text.erase(text.size() - 1);
			}
			return text;
		}
	};

} /* namespace form */
