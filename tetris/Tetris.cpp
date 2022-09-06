#include "Tetris.h"
#pragma warning(disable : 4996)
Cube::Cube(sf::Vector2f size) :size(size)
{
	been = false;
	cub.setSize(size);
	cub.setFillColor(sf::Color::Green);
}

void Cube::draw(sf::RenderTarget& target, sf::RenderStates states)const {
	if (been) {
		states.transform.translate(translate);
		target.draw(cub, states);
	}
}


void Tetris::draw(Game<Cube,Tetris>& game,Tetris& me) {
	me.window.clear();
	me.window.draw(me.env.background);
	me.window.draw(me.env.field);
	for (int i = 0; i < game.x_len; i++)
		for (int j = 0; j < game.y_len; j++) {
			sf::RenderStates states;
			states.transform.translate(me.size.x * i, me.size.y * j);
			me.window.draw(game.cubes[i][j],states);
		}
	/*
	for (int i = 0; i < game.fig_half->x; i++) {
		for (int j = 0; j < game.fig_half->y; j++) {
			sf::RenderStates states;
			states.transform.translate(me.size.x * i+game.fig_half->pos.x * me.size.x,
				me.size.y * j + game.fig_half->pos.y * me.size.y);
			states.blendMode.alphaDstFactor = sf::BlendMode::Factor::Zero;
			me.window.draw(game.fig_half->figure[i][j], states);
		}
	}
	*/
	me.window.draw(me.env.score);
	me.window.draw(me.env.line);
	me.window.display();
	

}

void Tetris::ev(Game<Cube, Tetris>& game, Tetris& me) {
	while (me.window.pollEvent(me.even)) {
		if (me.even.type == sf::Event::KeyPressed) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
				if (game.check_right()) { 
					game.del_from_matri();
					game.translate_pos(1, 0); 
					game.fig_in_matri(); }
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
				if (game.check_left()) { 
					game.del_from_matri(); 
					game.translate_pos(-1, 0); 
					game.fig_in_matri(); }
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
				if (game.check_under()) { 
					game.del_from_matri(); 
					game.translate_pos(0, 1); 
					game.fig_in_matri(); }
				else { 
					game.fig_in_matri(); 
					game.new_fig(); }
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
				game.down();
				game.new_fig();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
				game.rotate_left();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
				game.rotate_right();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
				game.rotate_right();
			}
		}
		if (me.even.type == sf::Event::Closed) {
			game.playing = false;
			me.window.close();
		}
	}
	if (me.time_to_down.getElapsedTime().asMilliseconds() >= me.time_down) {
		me.time_to_down.restart();
		if (game.check_under()) {
			game.del_from_matri();
			game.translate_pos(0, 1);
			game.fig_in_matri();
		}
		else {
			game.fig_in_matri();
			game.new_fig();
		}
	}
	me.env.score.setString(std::to_string(game.score));
}

void Tetris::setter(Game<Cube, Tetris>* game) {
	time_down = 500;
	game->draw = Tetris::draw;
	game->go_events = Tetris::ev;
	
	window.create(sf::VideoMode(260, 500), "TETRIS");
	size = sf::Vector2f(20, 20);
	
}

Envierement::Envierement()
{
	line.setPrimitiveType(sf::Lines);
	line.resize(2);
	line[0].position = sf::Vector2f(50, 130);
	line[1].position = sf::Vector2f(210, 130);
	line[0].color = sf::Color::Green;
	line[1].color = sf::Color::Green;

	field.setFillColor(sf::Color::Black);
	field.setSize(sf::Vector2f(160, 340));
	field.setPosition(sf::Vector2f(50, 50));

	background.setFillColor(sf::Color::Blue);
	background.setSize(sf::Vector2f(260, 500));

	font.loadFromFile("font.ttf");

	score.setColor(sf::Color::Black);
	score.setFont(font);
	score.setPosition(sf::Vector2f(10, 10));
	
}

