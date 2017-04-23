#pragma once

#include "Bird.h"
#include "PipePair.h"
#include <vector>
#include <fstream>

class Game
{
public:
	Game();
	void run();

private:
	sf::RenderWindow window;
	sf::Event event;
	sf::Clock clock;
	sf::Time delta;

	sf::Texture bird_texture;
	sf::Texture pipe_texture;

	sf::Font font;
	sf::Text score;
	sf::Text instructions;
	sf::Text high_score_text;

	Bird bird;
	std::vector<PipePair> pipes;

	std::ifstream read_score;
	std::ofstream out_score;
	int high_score;

	bool playing = false;
	int current_score;
};