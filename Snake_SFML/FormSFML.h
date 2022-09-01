#pragma once

#include <SFML/Graphics.hpp>
#include <string>
//#include "EllipseShape.h"

using namespace std;
using namespace sf;

namespace form {
	Font None;				// ����� ��������� �������������

	class Label {
	public:
		string text;	//�����
	protected:
		double x;		//���������� x
		double y;		//���������� y

		Text TXT;		//������������ �����
		int size = 20;

	public:
		Label(double _x = 0, double _y = 0, string _text = "Label")
		{
			None.loadFromFile("arial.ttf");			//�������� ������ ������ ���� ������
			x = _x;
			y = _y;
			text = _text;	
			//size = _size;// ��������� �����
			TXT.setFont(None);							// ��������� �����
			TXT.setCharacterSize(size); 					// � ��������, � �� ������!
			//TXT.setColor(Color::White);					// ������������� ���� ���������� ������
			TXT.setPosition(x, y);						// ������� ������
		}
		Text displayText(int ss)
		{
			TXT.setString(text);						// ��������� � ��������� ����� ����������� �����
			TXT.setCharacterSize(ss);
			return TXT;
		}
		void setText(string change_text) {
			text = change_text;
		}
	};

	class Button : public Label {
	protected:
		double width;		// ������ ������
		double height;		// ������ ������
		RectangleShape BOX;	// ������� ������������� � �������� width, height
		sf::Color color;
		int size_text;
	public:
		Button(double _x = 0, double _y = 0, double _width = 150, double _height = 30, string _text = "Hello", sf::Color _color = sf::Color::Blue, int _size_text = 40)
		{
			None.loadFromFile("arial.ttf");			//�������� ������ ������ ���� ������
			x = _x;
			y = _y;
			width = _width;
			height = _height;
			text = _text;		
			color = _color;
			size_text = _size_text;
			TXT.setFont(None);							// ��������� �����
			TXT.setCharacterSize(size_text); 					// � ��������, � �� ������!
			TXT.setPosition(x, y);						// ������� ������

			BOX.setSize(Vector2f(width, height));		// ������ ������
			BOX.setPosition(x, y);						// ���������� ������
			BOX.setFillColor(color);	// ���� ������
			BOX.setOutlineThickness(2);					// ������ X ��������
			BOX.setOutlineColor(color);		// ���� �������
		}
		//�������� ������� �� ������
		bool select(Vector2i _mouse)
		{
			if ((_mouse.x > x&& _mouse.x < x + width) && (_mouse.y > y&& _mouse.y < y + height)) {
				return  true;
			}
			else {
				return false;
			}
		}
		//����� ������
		Text displayText()
		{
			TXT.setString(text);  // ��������� � ��������� ����� ����������� �����
			return TXT;
		}
		//����� ������
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
			text = _text;								// ��������� �����
			focus = false;								// ����� ���� �����

			TXT.setFont(None);							// ��������� �����
			TXT.setCharacterSize(20); 					// � ��������, � �� ������!
			//TXT.setColor(Color::Black);					// ������������� ���� ���������� ������
			TXT.setPosition(x, y);						// ������� ������

			BOX.setSize(Vector2f(width, height));		// ������ ���� �����
			BOX.setPosition(x, y);						// ���������� ���� �����
			BOX.setFillColor(Color::White);	// ���� ������
		}
		//����� .reText( char ) �������� ����� ������ ������ ���� ������ Input
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

		// �������� ������ Input
		bool select()
		{
			return focus;
		}

		// ��������� ������ Input
		bool select(Vector2i _mouse)
		{
			if ((_mouse.x > x&& _mouse.x < x + width) && (_mouse.y > y&& _mouse.y < y + height)) { 	//���� ����� ������ ��� �������� Input...
				focus = true;																	   	// ����� true
				text += "|";																		// � ����� ������ �������� | (��� �� �������� ��� input � ������)
			}
			else {																				//...����� ���� ������� ��������� �� ��� ��������, ��...
				if (text.size() > 0) {																// �������� ���������� �������(����� ��������)
					if (text[text.size() - 1] == 124) {													// ���� ������ | ...
						text.erase(text.size() - 1);														// ... �� ������� ���
					}
				}
				focus = false;																		// ������������� ����� false
			}
			return focus;
		}

		//����� ������
		Text displayText()
		{
			TXT.setString(text);						// ��������� � ��������� ����� ����������� �����
			return TXT;
		}

		//����� ���� Input
		RectangleShape displayBOX()
		{
			return BOX;
		}

		//��� ����, ��� �� ������� ����� � ���� Ipnut ���������� ���������  readText() ������� ���������� string
		string readText()
		{
			if (text[text.size() - 1] == 124) { 	// ������� (���� ����) ������ |
				text.erase(text.size() - 1);
			}
			return text;
		}
	};

} /* namespace form */
