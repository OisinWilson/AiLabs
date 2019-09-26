#include "Game.h"

Game::Game() 
	:
	m_window{ sf::VideoMode((sf::VideoMode::getDesktopMode().width / 1.5f),(sf::VideoMode::getDesktopMode().height / 1.5f), 32), "Ai Lab 1" }
{
}

Game::~Game()
{
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Time timePerFrame = sf::seconds(1.f / 60.f); // 60 fps
	while (m_window.isOpen())
	{
		processEvents();
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents();
			update(timePerFrame);
		}
		render();
	}
}

void Game::processEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (sf::Event::Closed == event.type)
		{
			m_window.close();
		}
	}
}

void Game::update(sf::Time t_deltaTime)
{
	m_player.update();
	m_enemy.update();
}

void Game::render()
{
	m_window.clear();

	m_enemy.render();
	m_player.render();

	m_window.display();
}
