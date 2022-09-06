#pragma once
#include"Game.h"
#include<SFML/Graphics.hpp>

struct Envierement 
{
	sf::RectangleShape background;
	sf::RectangleShape field;
	sf::VertexArray line;
	sf::Sprite btns;
	sf::Font font;
	sf::Text score;
	sf::Texture textur_btns;
	Envierement();
};

class Cube :public sf::Drawable,public sf::Transformable{
public:
	sf::RectangleShape cub;
	sf::Vector2f size;
	sf::Vector2f translate = sf::Vector2f(50,50);
	
	bool been;
	Cube(sf::Vector2f size = sf::Vector2f(20, 20));

	void draw(sf::RenderTarget& target,sf::RenderStates states)const;


	operator int() { return been; }
	void operator =(int a) { if (a != 0)been = true; else been = false; }
	void operator =(sf::Color color) { cub.setFillColor(color); }
};

class Tetris
{
private:
	sf::Clock time_to_down;
	int time_down;
	sf::Vector2f size;
	sf::RenderWindow window;
	sf::Event even;
	Envierement env;
public:

	void setter(Game<Cube, Tetris>* game);

	static void draw(Game<Cube,Tetris>& game,Tetris& me);
	static void ev(Game<Cube,Tetris>& game,Tetris& me);
	void draw_envierement();
};

