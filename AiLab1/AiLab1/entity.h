#pragma once

#include<SFML/Graphics.hpp>
#include<iostream>
#include<math.h>

class entity
{
public:

	entity(bool t_type, sf::RenderWindow & t_window);
	~entity();

	void update();
	void render();

private:
	
	bool m_type;
	
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	
	sf::Vector2f m_velocity;

	sf::CircleShape m_velocityPos;


	void rotate(float t_angle);
	void boundaryCheck(sf::Vector2f speed);
	float distance(sf::Vector2f p1, sf::Vector2f p2);

	float m_speed{ 10.0f };

	sf::Vector2f vUnit(sf::Vector2f t_v);
	float vLength(sf::Vector2f t_v);

	sf::RenderWindow & m_window;
};