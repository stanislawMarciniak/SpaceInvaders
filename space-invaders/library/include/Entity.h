#ifndef ENTITY_H
#define ENTITY_H

#include <string>

#include <SFML/Graphics.hpp>

class Entity
{
protected:
  sf::Sprite sprite;

public:
  Entity(std::string textureName, sf::Vector2f pos);
  virtual ~Entity() = default;

  sf::FloatRect getBounds() const;
  bool isOutsideWindow();

  void draw();
  virtual void update() = 0;
};

#endif