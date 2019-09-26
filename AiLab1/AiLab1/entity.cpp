#include "entity.h"

entity::entity(bool t_type, sf::RenderWindow& t_window)
	:
	m_type{t_type},
	m_window{t_window}
{
	m_sprite.setPosition(sf::Vector2f(200.0f, 200.0f));
	sf::Vector2f startingVel = { m_sprite.getPosition().x, m_sprite.getPosition().y - 100 };
	sf::Vector2f startingScale = {0.25f,0.25f};

	if (t_type) { 
		if (!m_texture.loadFromFile("ASSETS/SPRITES/player.png"))
		{
			std::cout << "Frog Sprite Loading Error" << std::endl;
		}
	}
	else { 
		if (!m_texture.loadFromFile("ASSETS/SPRITES/alien.png"))
		{
			std::cout << "Lilly Pad Sprite Loading Error" << std::endl;
		}
		startingVel = sf::Vector2f(sf::Vector2f(m_sprite.getPosition().x + 100, m_sprite.getPosition().y + 100));
		startingScale = sf::Vector2f(0.5f,0.5f);
	}


	m_sprite.setTexture(m_texture);
	m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2.0f, m_sprite.getGlobalBounds().height / 2.0f);
	m_sprite.setScale(startingScale);
	

	m_velocityPos.setPosition(startingVel);
	m_velocityPos.setRadius(25);
	m_velocityPos.setOrigin(m_velocityPos.getGlobalBounds().width / 2.0f, m_velocityPos.getGlobalBounds().height / 2.0f);
	m_velocityPos.setFillColor(sf::Color::Red);

}

entity::~entity()
{
}

void entity::update()
{
	sf::Vector2f tempV(m_velocityPos.getPosition().x - m_sprite.getPosition().x, m_velocityPos.getPosition().y - m_sprite.getPosition().y);
	sf::Vector2f unit = vUnit(tempV);

	m_sprite.setPosition(sf::Vector2f(m_sprite.getPosition().x + (unit.x * m_speed), m_sprite.getPosition().y + (unit.y * m_speed)));
	m_velocityPos.setPosition(sf::Vector2f(m_velocityPos.getPosition().x + (unit.x * m_speed), m_velocityPos.getPosition().y + (unit.y * m_speed)));

	boundaryCheck(sf::Vector2f((unit.x * m_speed), (unit.y * m_speed)));

	if (m_type) {

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			if (m_speed < 20.0f){
				m_speed += 0.2;
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			
			if (m_speed > 0.0f)
			{
				m_speed -= 0.5;
			}
			else
			{
				m_speed = 0.0f;
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			rotate(-10.0f);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			rotate(10.0f);
		}
	}

}

void entity::render()
{
	m_window.draw(m_sprite);
	m_window.draw(m_velocityPos);
}

void entity::rotate(float t_angle)
{
	float tempAngle = t_angle * (3.14159265359f / 180.0f);

	float roteX = cos(tempAngle) * (m_velocityPos.getPosition().x - m_sprite.getPosition().x) - sin(tempAngle) * (m_velocityPos.getPosition().y - m_sprite.getPosition().y) + m_sprite.getPosition().x;
	float roteY = sin(tempAngle) * (m_velocityPos.getPosition().x - m_sprite.getPosition().x) + cos(tempAngle) * (m_velocityPos.getPosition().y - m_sprite.getPosition().y) + m_sprite.getPosition().y;

	m_velocityPos.setPosition(sf::Vector2f(roteX, roteY));
	m_sprite.rotate(t_angle);
}

void entity::boundaryCheck(sf::Vector2f speed)
{
	float heightCheck = m_sprite.getGlobalBounds().height / 2.0f;
	float widthCheck = m_sprite.getGlobalBounds().width / 2.0f;

	float distanceX = distance(sf::Vector2f(m_sprite.getPosition().x, 0), sf::Vector2f(m_velocityPos.getPosition().x, 0));
	float distanceY = distance(sf::Vector2f(0, m_sprite.getPosition().y), sf::Vector2f(0, m_velocityPos.getPosition().y));

	if ((m_sprite.getPosition().y - heightCheck) <=  -200) {
		m_sprite.setPosition(sf::Vector2f(m_sprite.getPosition().x, m_window.getSize().y - 100));
		m_velocityPos.setPosition(sf::Vector2f(m_velocityPos.getPosition().x, m_sprite.getPosition().y - distanceY));
	}
	else if ((m_sprite.getPosition().y + heightCheck) > m_window.getSize().y + 200) {
		m_sprite.setPosition(sf::Vector2f(m_sprite.getPosition().x, 100));
		m_velocityPos.setPosition(sf::Vector2f(m_velocityPos.getPosition().x, m_sprite.getPosition().y + distanceY));
	}

	if ((m_sprite.getPosition().x - widthCheck) <= -200) {
		m_sprite.setPosition(sf::Vector2f(m_window.getSize().x - 100, m_sprite.getPosition().y));
		m_velocityPos.setPosition(sf::Vector2f(m_sprite.getPosition().x - distanceX, m_velocityPos.getPosition().y ));
	}
	else if ((m_sprite.getPosition().x + widthCheck) > m_window.getSize().x + 200) {
		m_sprite.setPosition(sf::Vector2f(100, m_sprite.getPosition().y));
		m_velocityPos.setPosition(sf::Vector2f(m_sprite.getPosition().x + distanceX, m_velocityPos.getPosition().y));
	}
}

float entity::distance(sf::Vector2f p1, sf::Vector2f p2)
{
	float tempX = (p2.x - p1.x) * (p2.x - p1.x);
	float tempY = (p2.y - p1.y) * (p2.y - p1.y);

	return sqrt(tempX + tempY);
}

sf::Vector2f entity::vUnit(sf::Vector2f t_v)
{
	float lenght = vLength(t_v);
	return sf::Vector2f(t_v.x / lenght , t_v.y / lenght);
}

float entity::vLength(sf::Vector2f t_v)
{
	return sqrt(t_v.x * t_v.x + t_v.y * t_v.y);
}
