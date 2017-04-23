#include "Game.h"

Game::Game()
{
	read_score.open("score.txt");
	read_score >> high_score;
	read_score.close();

	window.create(sf::VideoMode(500, 600), "Bird Jump", sf::Style::Close);
	window.setFramerateLimit(60);

	bird_texture.loadFromFile("Resources/Bird.png");
	bird.setup(bird_texture, window);

	pipe_texture.loadFromFile("Resources/Pipe.png");
	for (int i = 1; i < 4; i++)
		pipes.emplace_back(pipe_texture, static_cast<float>((i + 1) * 400), window);

	font.loadFromFile("Resources/Font.ttf");
	score.setFont(font);
	score.setPosition(20, 20);
	score.setCharacterSize(24);
	score.setFillColor(sf::Color::Blue);
	score.setString("Score: 0");

	instructions.setFont(font);
	instructions.setCharacterSize(24);
	instructions.setFillColor(sf::Color::Blue);
	instructions.setString("Press SPACE to begin!");
	instructions.setOrigin(
		instructions.getGlobalBounds().left + (instructions.getGlobalBounds().width / 2.0f),
		instructions.getGlobalBounds().top + (instructions.getGlobalBounds().height / 2.0f)
	);
	instructions.setPosition(static_cast<sf::Vector2f>(window.getSize()) / 2.0f);
	instructions.move(0.0, 50.0f);

	high_score_text.setFont(font);
	high_score_text.setPosition(20, 50);
	high_score_text.setCharacterSize(24);
	high_score_text.setFillColor(sf::Color::Blue);
	high_score_text.setString("High Score: " + std::to_string(high_score));
}

void Game::run()
{
	while (window.isOpen())
	{
		delta = clock.restart();

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			else if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Space)
				{
					if (playing)
					{
						bird.jump();
					}
					else playing = true;
				}
			}
		}

		if (playing)
		{
			for (auto& pipe_pair : pipes) pipe_pair.update(delta.asSeconds(), window);
			if (bird.update(delta.asSeconds(), window, pipes))
			{
				bird.reset(window);
				pipes.clear();
				for (int i = 1; i < 4; i++)
					pipes.emplace_back(pipe_texture, static_cast<float>((i + 1) * 400), window);
				playing = false;
			}

			if (bird.getScore() != current_score)
			{
				current_score = bird.getScore();
				score.setString("Score: " + std::to_string(bird.getScore()));

				if (current_score > high_score)
				{
					high_score = current_score;
					out_score.open("score.txt");
					out_score << high_score;
					out_score.close();
					high_score_text.setString("High Score: " + std::to_string(high_score));
				}
			}
		}

		window.clear(sf::Color::Cyan);
		window.draw(bird);
		for (auto& pipe_pair : pipes) window.draw(pipe_pair);
		if (!playing)
		{
			window.draw(instructions);
		}
		window.draw(score);
		window.draw(high_score_text);
		window.display();
	}
}