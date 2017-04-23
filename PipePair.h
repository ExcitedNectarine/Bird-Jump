#pragma once

#include <SFML/Graphics.hpp>
#include "Tools.h"

class PipePair : public sf::Drawable
{
public:
	PipePair(const sf::Texture& texture, const float position, const sf::RenderWindow& window);
	void update(const float delta, const sf::RenderWindow& window);
	bool intersects(const sf::FloatRect& rect) const;
	const float getPosition() const;

public:
	bool passed = false;

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	sf::Sprite top;
	sf::Sprite bottom;
	const sf::Texture* texture;
	float speed = 200.0f;
	float original_position;
};