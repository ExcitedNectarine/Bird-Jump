#pragma once

#include "PipePair.h"
#include <vector>

class Bird : public sf::Drawable
{
public:
	void setup(sf::Texture& texture, const sf::RenderWindow& window);
	void reset(const sf::RenderWindow& window);
	bool update(const float delta, const sf::RenderWindow& window, std::vector<PipePair>& pipes);
	void jump();
	int getScore() const;

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	sf::Sprite sprite;
	sf::Vector2f movement;
	sf::FloatRect rect;
	sf::Texture* texture;
	float gravity = 980.0f;
	float jump_height = -500.0f;
	float rotation_speed = 55.0f;
	int score = 0;
};