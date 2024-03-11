#pragma once
#include "Tile.h"
#include "TextureManager.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include "SFML/Graphics.hpp"
#include <stdlib.h>
#include <time.h>

class Board
{
	signed int remainingbombs;
	bool debugmode;
public:
	sf::Sprite test1;
	sf::Sprite test2;
	sf::Sprite test3;
	sf::Sprite debug;
	sf::Sprite face;
	sf::Sprite digit1;
	sf::Sprite digit2;
	sf::Sprite digit3;
	vector<Tile> tiles;
	int bombcount = 0;

	Board();
	void LinkTiles();
	void DrawBoard(sf::RenderWindow& window);
	void SetCounter();
	void RandomReset();
	void LoadTestBoard(string file);
	void ToggleDebug();
	void LeftClick(sf::Vector2f mousepos);
	void RightClick(sf::Vector2f mousepos);
	bool VictoryCheck();
	void Victory();
	bool DefeatCheck();
	void Defeat(sf::RenderWindow& window);
};