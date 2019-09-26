#pragma once

#include<SFML/Graphics.hpp>
#include<iostream>
#include "entity.h"

class Game
{
public:
	Game();
	~Game();

	void run();

private:

	void processEvents();
	void update(sf::Time t_deltaTime);
	void render();

	sf::RenderWindow m_window;

	entity m_player{ true , m_window };
	entity m_enemy{ false , m_window };
};

