#include "Game.h"
#include "Entity.h"

Entity::Entity(std::string textureName, sf::Vector2f pos)
{
  sprite.setTexture(*(Game::getGame().getTexture(textureName).get()));
  sprite.setOrigin(
      sf::Vector2f(
          sprite.getLocalBounds().width * 0.5f,
          sprite.getLocalBounds().height * 0.5f));

  sprite.setPosition(pos);
}

sf::FloatRect Entity::getBounds() const
{
  return sprite.getGlobalBounds();
}

void Entity::draw()
{
  Game::getGame().getRenderTarget().draw(sprite);
}

bool Entity::isOutsideWindow()
{
  auto pos = sprite.getPosition();
  auto viewSize = Game::getGame().getRenderTarget().getView().getSize();
  auto bounds = getBounds();

  return pos.x - bounds.width / 2 < 0.f ||
         pos.x + bounds.width / 2 > viewSize.x ||
         pos.y - bounds.height / 2 < 0.f ||
         pos.y + bounds.height / 2 > viewSize.y;
}
