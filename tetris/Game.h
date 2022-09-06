#pragma once
#include"Figure.h"

template<class T,class M>
class Game{
private:
	Figure<T>* fig;
	Figure<T>* fig_half;
	void (*draw)(Game<T, M>&, M&);
	void (*go_events)(Game<T, M>&, M&);
	bool playing = true;
	int score = 0;

	friend M;
	T** cubes;
	int x_len, y_len;
	int hard = 1;
public:
	M obj;

	Game(int x = 8, int y = 17) :x_len(x), y_len(y) {
		cubes = new  T*[x];

		for (int i = 0; i < x_len; i++)
			cubes[i] = new T[y];
		new_fig();
		fig_in_matri();
	}
	void rotate_right() {
		del_from_matri();
		Figure<T> tmp(fig->y, fig->x, false,fig->color);
		tmp.pos = fig->pos;
		for (int i = 0; i < fig->x; i++) 
			for (int j = 0; j < fig->y; j++) 
				tmp.figure[j][fig->x - i - 1] = fig->figure[i][j];
			
		if (correct(tmp)) {
			*fig = tmp;
			*fig_half = tmp;
			down_half();
		}
		fig_in_matri();
	}
	void rotate_left() {
		del_from_matri();
		Figure<T> tmp(fig->y, fig->x, false, fig->color);
		tmp.pos = fig->pos;
		
		for (int i = 0; i < fig->x; i++) 
			for (int j = 0; j < fig->y; j++) 
				tmp.figure[fig->y - j - 1][i] = fig->figure[i][j];

		if (correct(tmp)) {
			*fig = tmp;
			*fig_half = tmp;
			down_half();
		}
		fig_in_matri();
	}

	bool correct(Figure<T>& tmp) {
		if (tmp.pos.x < 0)
			tmp.pos.x = 0;
		if (tmp.pos.y < 0)
			tmp.pos.y = 0;
		if (tmp.pos.y + tmp.y >= y_len)
			tmp.pos.y -= (tmp.pos.y + tmp.y - y_len);
		if (tmp.pos.x + tmp.x >= x_len)
			tmp.pos.x -= (tmp.pos.x + tmp.x - x_len);

		for (int i = tmp.pos.x; i < tmp.pos.x + tmp.x; i++) 
			for (int j = tmp.pos.y; j < tmp.pos.y + tmp.y; j++) 
				if (tmp.figure[i - tmp.pos.x][j - tmp.pos.y] != 0)
					if (cubes[i][j] != 0)
						return false;
		return true;
		

	}

	void del_from_matri() {
		int x, y;
		x = fig->pos.x;
		y = fig->pos.y;
		for (int i = x; i < x + fig->x; i++)
			for (int j = y; j < y + fig->y; j++)
				if(fig->figure[i - fig->pos.x][j - fig->pos.y]!=0)
					cubes[i][j] = 0;
	}
	void fig_in_matri() {
		int x, y;
		x = fig->pos.x;
		y = fig->pos.y;
		for (int i = x; i < x + fig->x; i++)
			for (int j = y; j < y + fig->y; j++)
				if (fig->figure[i - fig->pos.x][j - fig->pos.y] != 0)
					cubes[i][j] = fig->figure[i - fig->pos.x][j - fig->pos.y];
	}

	bool check_under(Figure<T> *fig = nullptr) {
		if (fig == nullptr)
			fig = this->fig;
		for (int i = fig->pos.x; i < fig->pos.x + fig->x; i++) {
			if (fig->Y_pos(i - fig->pos.x) != -1) {

				if (fig->Y_pos(i - fig->pos.x) + 1 < y_len) {
					if (cubes[i][fig->Y_pos(i - fig->pos.x) + 1] != 0)
						return false;
				}
				else {
					return false;
				}

			}
		}
		return true;
	}
	bool check_left() {
		for (int i = fig->pos.y; i < fig->pos.y + fig->y; i++) {
			if (fig->X_left_pos(i - fig->pos.y) != -1) {

				if (fig->X_left_pos(i - fig->pos.y) - 1 >= 0) {
					if (cubes[fig->X_left_pos(i - fig->pos.y) - 1][i] != 0)
						return false;
				}
				else {
					return false;
				}

			}
		}
		return true;
	}
	bool check_right() {
		for (int i = fig->pos.y; i < fig->pos.y + fig->y; i++) {
			if (fig->X_right_pos(i - fig->pos.y) != -1) {

				if (fig->X_right_pos(i - fig->pos.y) + 1 < x_len) {
					if (cubes[fig->X_right_pos(i - fig->pos.y) + 1][i] != 0) 
						return false;
				}
				else {
					return false;
				}

			}
		}
		return true;
	}

	void translate_pos(int x,int y) {
		fig->pos += sf::Vector2i(x, y);
		fig_in_matri();
	}

	void rows_check_delete() {
		for (int j = y_len - 1; j >= 0; j--) {
			bool del = true;
			for (int i = 0; i < x_len; i++) 
				if (cubes[i][j] == 0) {
					del = false;
					break;
				}
			if (del) {
				del_row(j);
				j++;
			}
			
		}
	}
	void del_row(int y) {
		for (int j = y; j > 0; j--)
			for (int i = 0; i < x_len; i++) {
				cubes[i][j] = cubes[i][j - 1];
			}
		for (int i = 0; i < x_len; i++)
			cubes[i][0] = 0;
		score += 100;
	}

	void new_fig() {
		fig = new Figure<T>;
		fig_half = new Figure<T>;
		rows_check_delete();

		if (!correct(*fig)) 
			playing = false;
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < x_len; j++)
				if (cubes[j][i] != 0)
					playing = false;
		
	}

	void down() {
		del_from_matri();
		while (check_under()) {
			fig->pos.y += 1;
		}
		fig_in_matri();
	}
	void down_half() {
		while (check_under(fig_half )) {
			fig_half->pos.y += 1;
		}
	}

	void main_loop() {
		while (playing) {
			this->go_events(*this, obj);
			this->draw(*this, obj);
		}
	}
};