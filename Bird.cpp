#include "Bird.h"

void Bird::setup(sf::Texture& texture, const sf::RenderWindow& window)
{
	this->texture = &texture;
	sprite.setTexture(texture);
	sprite.setOrigin(static_cast<sf::Vector2f>(texture.getSize()) / 2.0f);
	sprite.setPosition(static_cast<sf::Vector2f>(window.getSize()) / 2.0f);
	rect = sprite.getGlobalBounds();
}

void Bird::reset(const sf::RenderWindow& window)
{
	sprite.setPosition(static_cast<sf::Vector2f>(window.getSize()) / 2.0f);
	sprite.setRotation(0.0f);
	movement *= 0.0f;
	score = 0;
}

bool Bird::update(const float delta, const sf::RenderWindow& window, std::vector<PipePair>& pipes)
{
	movement.y += gravity * delta;
	sprite.move(movement * delta);
	sprite.rotate(rotation_speed * delta);
	
	if (sprite.getRotation() >= 60.0f && sprite.getRotation() <= 330.0f)
		sprite.setRotation(60.0f);

	if (sprite.getPosition().y <= 0.0f || sprite.getPosition().y >= window.getSize().y)
	{
		return true;
	}

	rect.left = sprite.getPosition().x - (texture->getSize().x / 2.0f);
	rect.top = sprite.getPosition().y - (texture->getSize().y / 2.0f);

	for (auto& pair : pipes)
	{
		if (pair.intersects(rect)) return true;
		if (!pair.passed && sprite.getPosition().x > pair.getPosition())
		{
			pair.passed = true;
			score++;
		}
	}

	return false;
}

void Bird::jump()
{
	movement.y = jump_height;
	sprite.setRotation(330.0f);
}

int Bird::getScore() const
{
	return score;
}

void Bird::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(sprite);
}