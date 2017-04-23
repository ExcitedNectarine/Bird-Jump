#include "PipePair.h"

PipePair::PipePair(const sf::Texture& texture, const float position, const sf::RenderWindow& window) : original_position(3 * 400)
{	
	this->texture = &texture;
	float offset = randomFloat(-(texture.getSize().y / 3.0f), texture.getSize().y / 3.0f);

	top.setTexture(texture);
	top.setOrigin(static_cast<float>(texture.getSize().x), static_cast<float>(texture.getSize().y / 2.0f));
	top.setScale(1.0f, -1.0f);
	top.setPosition(position, offset);

	bottom.setTexture(texture);
	bottom.setOrigin(static_cast<float>(texture.getSize().x), static_cast<float>(texture.getSize().y / 2.0f));
	bottom.setPosition(position, static_cast<float>(window.getSize().y) + offset);
}

void PipePair::update(const float delta, const sf::RenderWindow& window)
{
	top.move(-speed * delta, 0.0f);
	bottom.move(-speed * delta, 0.0f);

	if (top.getPosition().x <= 0)
	{
		float offset = randomFloat(-(texture->getSize().y / 3.0f), texture->getSize().y / 3.0f);
		top.setPosition(original_position, offset);
		bottom.setPosition(original_position, static_cast<float>(window.getSize().y) + offset);
		passed = false;
	}
}

bool PipePair::intersects(const sf::FloatRect& rect) const
{
	return top.getGlobalBounds().intersects(rect) || bottom.getGlobalBounds().intersects(rect);
}

const float PipePair::getPosition() const
{
	return top.getPosition().x;
}

void PipePair::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(top);
	target.draw(bottom);
}