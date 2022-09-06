#pragma once
#include<SFML/Graphics.hpp>
#include <ctime>

template<class T>
struct Figure {
	sf::Vector2i pos;
	int x, y;

	T** figure;
	sf::Color color;
	Figure(int x = 2, int y = 2,bool n = true,sf::Color color = sf::Color::Green) :x(x), y(y) {
		std::srand(std::time(0));
		if (n) {

			switch (rand() % 6)
			{
			case 0: {
				this->x = 2;
				this->y = 3;
				figure = new  T * [this->x];
				pos = sf::Vector2i(0, 0);
				for (int i = 0; i < this->x; i++) {
					figure[i] = new T[this->y];
				}
				int gg[2][3] = { {1,1,1},
								 {0,1,0}
				};
				for (int i = 0; i < this->x; i++)
					for (int j = 0; j < this->y; j++)
						if (gg[i][j] != 0)
							figure[i][j] = 1;
				break;
			}
			case 1: {
				this->x = 2;
				this->y = 3;
				figure = new  T * [this->x];
				pos = sf::Vector2i(0, 0);
				for (int i = 0; i < this->x; i++) {
					figure[i] = new T[this->y];
				}
				int gg[2][3] = { {1,1,1},
								{1,0,0}
				};
				for (int i = 0; i < this->x; i++)
					for (int j = 0; j < this->y; j++)
						if (gg[i][j] != 0)
							figure[i][j] = 1;
				break;
			}
			case 2: {
				this->x = 2;
				this->y = 3;
				figure = new  T * [this->x];
				pos = sf::Vector2i(0, 0);
				for (int i = 0; i < this->x; i++) {
					figure[i] = new T[this->y];
				}
				int gg[2][3] = { {1,1,1},
								 {0,0,1}
				};
				for (int i = 0; i < this->x; i++)
					for (int j = 0; j < this->y; j++)
						if (gg[i][j] != 0)
							figure[i][j] = 1;
				break;
			}
			case 3: {
				this->x = 2;
				this->y = 2;
				figure = new  T * [this->x];
				pos = sf::Vector2i(0, 0);
				for (int i = 0; i < this->x; i++) {
					figure[i] = new T[this->y];
				}
				int gg[2][2] = { {1,1},
								 {1,1}
				};
				for (int i = 0; i < this->x; i++)
					for (int j = 0; j < this->y; j++)
						if (gg[i][j] != 0)
							figure[i][j] = 1;
				break;
			}
			case 4: {
				this->x = 1;
				this->y = 4;
				figure = new  T * [this->x];
				pos = sf::Vector2i(0, 0);
				for (int i = 0; i < this->x; i++) {
					figure[i] = new T[this->y];
				}
				int gg[1][4] = { {1,1,1,1}
				};
				for (int i = 0; i < this->x; i++)
					for (int j = 0; j < this->y; j++)
						if (gg[i][j] != 0)
							figure[i][j] = 1;
				break;
			}
			case 5: {
				this->x = 3;
				this->y = 2;
				figure = new  T * [this->x];
				pos = sf::Vector2i(0, 0);
				for (int i = 0; i < this->x; i++) {
					figure[i] = new T[this->y];
				}
				int gg[3][2] = { {0,1},
								 {1,1},
								 {1,0}
				};
				for (int i = 0; i < this->x; i++)
					for (int j = 0; j < this->y; j++)
						if (gg[i][j] != 0)
							figure[i][j] = 1;
				break;
			}
/*
			case 6: {
				this->x = 3;
				this->y = 3;
				figure = new  T * [this->x];
				pos = sf::Vector2i(0, 0);
				for (int i = 0; i < this->x; i++) {
					figure[i] = new T[this->y];
				}
				int gg[3][3] = { {0,1,0},
								 {1,1,1},
								 {0,1,0}
				};
				for (int i = 0; i < this->x; i++)
					for (int j = 0; j < this->y; j++)
						if (gg[i][j] != 0)
							figure[i][j] = 1;
				break;
			}*/
			}

			set_color();

		}
		else {
			figure = new  T * [x];
			pos = sf::Vector2i(0, 0);
			for (int i = 0; i < x; i++) {
				figure[i] = new T[y];
			}
			this->color = color;
			for (int i = 0; i < x; i++)
				for (int j = 0; j < y; j++)
					figure[i][j] = color;
		}
		
	}

	int Y_pos(int x_pos);
	int X_left_pos(int y_pos);
	int X_right_pos(int y_pos);

	void set_color() {
		color = sf::Color(rand() % 255, rand() % 255, rand() % 255);
		for (int i = 0; i < x; i++)
			for (int j = 0; j < y; j++)
				figure[i][j] = color;
	}

};

template<class T>
inline int Figure<T>::Y_pos(int x_pos)
{
	bool yes = false;
	int last = 0;
	for (int i = 0; i < y; i++) 
		if (figure[x_pos][i] != 0) {
			last = i;
			yes = true;
		}
	if(yes)
		return last + pos.y;
	return -1;
	
}

template<class T>
inline int Figure<T>::X_left_pos(int y_pos)
{
	bool yes = false;
	int last = x - 1;
	for (int i = x - 1; i >= 0; i--)
		if (figure[i][y_pos] != 0) {
			last = i;
			yes = true;
		}
	if(yes)
		return last + pos.x;
	return -1;
}

template<class T>
inline int Figure<T>::X_right_pos(int y_pos)
{
	bool yes = false;
	int last = 0;
	for (int i = 0; i < x; i++)
		if (figure[i][y_pos] != 0) {
			last = i;
			yes = true;
		}
	if(yes)
		return last + pos.x;
	return -1;
}
