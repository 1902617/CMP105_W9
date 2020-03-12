#include "BallManager.h"

BallManager::BallManager()
{
	spawnPoint = sf::Vector2f(350, 250); 
	texture.loadFromFile("gfx/Beach_Ball.png"); 

	for (int i = 0; i < 5000; i++) 
	{
		balls.push_back(Ball());
		balls[i].setAlive(false);
		balls[i].setTexture(&texture);
		balls[i].setSize(sf::Vector2f(100, 100));
	}
}

BallManager::~BallManager()
{

}

void BallManager::spawn()
{
	for (int i = 0; i < balls.size(); i++)
	{
		if (!balls[i].isAlive())
		{
			balls[i].setAlive(true);
			balls[i].setVelocity(rand() % 200 - 100, rand() % 200 - 100);
			balls[i].setPosition(spawnPoint);
			return;
		}
	}
}

void BallManager::update(float dt, sf::Vector2u windowDim)
{
	spawnPoint = sf::Vector2f(windowDim.x / 2, windowDim.y / 2);

	for (int i = 0; i < balls.size(); i++)
	{
		if (balls[i].isAlive())
		{
			balls[i].update(dt);
		}
	}

	deathCheck();
}

void BallManager::handleInput(float dt, Input* in)
{
	if (in->isKeyDown(sf::Keyboard::P))
	{
		spawn();
		in->setKeyUp(sf::Keyboard::P);
	}
}

void BallManager::deathCheck()
{
	for (int i = 0; i < balls.size(); i++)
	{
		if (balls[i].isAlive())
		{
			if (balls[i].getPosition().x < -100)
			{
				balls[i].setAlive(false);
			}
			if (balls[i].getPosition().x > 800)
			{
				balls[i].setAlive(false);
			}
			if (balls[i].getPosition().y < -100)
			{
				balls[i].setAlive(false);
			}
			if (balls[i].getPosition().y > 600)
			{
				balls[i].setAlive(false);
			}
		}
	}
}

void BallManager::render(sf::RenderWindow* window)
{
	{
		for (int i = 0; i < balls.size(); i++)
		{
			if (balls[i].isAlive())
			{
				window->draw(balls[i]);
				balls[i].rotate(90);
			}
		}
	}
}