#include "Board.h"
#include "Tile.h"
#include "TextureManager.h"
#include <SFML/Graphics.hpp>
using sf::RenderWindow;
using sf::Window;
using sf::Texture;
using sf::Sprite;
using sf::Mouse;
using sf::Vector2f;
using sf::Vector2i;
using sf::Vector2u;

int main()
{
	TextureManager::LoadTexture("tile_hidden");
	TextureManager::LoadTexture("tile_revealed");
	TextureManager::LoadTexture("test_1");
	TextureManager::LoadTexture("test_2");
	TextureManager::LoadTexture("test_3");
	TextureManager::LoadTexture("mine");
	TextureManager::LoadTexture("flag");
	TextureManager::LoadTexture("debug");
	TextureManager::LoadTexture("digits");
	TextureManager::LoadTexture("face_happy");
	TextureManager::LoadTexture("face_lose");
	TextureManager::LoadTexture("face_win");
	TextureManager::LoadTexture("number_1");
	TextureManager::LoadTexture("number_2");
	TextureManager::LoadTexture("number_3");
	TextureManager::LoadTexture("number_4");
	TextureManager::LoadTexture("number_5");
	TextureManager::LoadTexture("number_6");
	TextureManager::LoadTexture("number_7");
	TextureManager::LoadTexture("number_8");

	RenderWindow window(sf::VideoMode(800, 600), "Minesweeper");
	Board board = Board();
	board.RandomReset();

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}

			if (event.type == sf::Event::MouseButtonReleased)
			{
				Vector2i buffer = Mouse::getPosition(window);
				Vector2f mousepos = Vector2f((float)buffer.x, (float)buffer.y);
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					board.LeftClick(mousepos);
					if (board.VictoryCheck() == true)
					{
						board.Victory();
					}
					else if (board.DefeatCheck() == true)
					{
						board.Defeat(window);
					}
				}
				if (event.mouseButton.button == sf::Mouse::Right)
				{
					board.RightClick(mousepos);
				}
			}
		}

		window.clear();
		board.DrawBoard(window);
		window.display();
	}
	TextureManager::Clear();
	return 0;
}