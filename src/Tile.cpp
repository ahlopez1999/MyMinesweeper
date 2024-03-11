#include "Tile.h"

Tile::Tile()
{
	backround.setTexture(TextureManager::GetTexture("tile_revealed"));
	setTexture(TextureManager::GetTexture("tile_hidden"));
	isrevealed = false;
	isflagged = false;
	hasBomb = false;
	adjacentBombs = 0;
}

Tile::Tile(bool _hasbomb)
{
	backround.setTexture(TextureManager::GetTexture("tile_hidden"));
	setTexture(TextureManager::GetTexture("tile_hidden"));
	isrevealed = false;
	isflagged = false;
	hasBomb = _hasbomb;
	adjacentBombs = 0;
}

void Tile::DetectMines()
{
	for (unsigned int i = 0; i < neighbors.size(); i++)
	{
		if (neighbors[i]->hasBomb)
		{
			adjacentBombs++;
		}
	}
}

void Tile::Reveal()
{
	if (isflagged || isrevealed)
	{
		return;
	}
	else if (hasBomb)
	{
		isrevealed = true;
		setTexture(TextureManager::GetTexture("mine"));
	}
	else if (adjacentBombs == 0)
	{
		isrevealed = true;
		setTexture(TextureManager::GetTexture("tile_revealed"));
		for (unsigned int i = 0; i < neighbors.size(); i++)
		{
			neighbors[i]->Reveal();
		}
	}
	else if (adjacentBombs > 0)
	{
		isrevealed = true;
		string texturefile = "number_";
		texturefile += std::to_string(adjacentBombs);
		setTexture(TextureManager::GetTexture(texturefile));
	}
}

void Tile::Flagged()
{
	if (isflagged)
	{
		isflagged = false;
		backround.setTexture(TextureManager::GetTexture("tile_revealed"));
		setTexture(TextureManager::GetTexture("tile_hidden"));
	}
	else
	{
		isflagged = true;
		backround.setTexture(TextureManager::GetTexture("tile_hidden"));
		setTexture(TextureManager::GetTexture("flag"));
	}
}
