#pragma once
#include "SFML/Graphics.hpp"
#include "TextureManager.h"
#include <vector>
#include <string>
using std::vector;

class Tile : public sf::Sprite
{
	sf::Texture texture;
	int adjacentBombs;

public:
	sf::Sprite backround;
	bool hasBomb;
	bool isflagged;
	bool isrevealed;
	vector<Tile*> neighbors;

	Tile();
	Tile(bool _hasbomb);
	void DetectMines();
	void Reveal();
	void Flagged();
};