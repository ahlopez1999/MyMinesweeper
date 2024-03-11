#include "Tile.h"
#include "Board.h"
using namespace std;

Board::Board()
{
	//set textures for board sprites
	test1.setTexture(TextureManager::GetTexture("test_1"));
	test2.setTexture(TextureManager::GetTexture("test_2"));
	test3.setTexture(TextureManager::GetTexture("test_3"));
	debug.setTexture(TextureManager::GetTexture("debug"));
	face.setTexture(TextureManager::GetTexture("face_happy"));

	digit1.setTexture(TextureManager::GetTexture("digits"));
	digit1.setTextureRect(sf::IntRect(0, 0, 21, 32));
	digit2.setTexture(TextureManager::GetTexture("digits"));
	digit2.setTextureRect(sf::IntRect(0, 0, 21, 32));
	digit3.setTexture(TextureManager::GetTexture("digits"));
	digit3.setTextureRect(sf::IntRect(0, 0, 21, 32));

	bombcount = 0;
	//initialize some default tiles WITH NO BOMBS
	for (unsigned int i = 0; i < 400; i++)
	{
		tiles.push_back(Tile());
	}
	//link these tiles
	LinkTiles();
	debugmode = false;
	remainingbombs = 0;
}

void Board::LinkTiles()
{
	int index = 0;
	int length = 25;
	int height = 16;
	for (unsigned int y = 0; y < 16; y++)
	{
		for (unsigned int x = 0; x < 25; x++)
		{
			//top left tile
			if (x == 0 && y == 0)
			{
				tiles[index].neighbors.push_back(&tiles[index + 1]);
				tiles[index].neighbors.push_back(&tiles[index + length]);
				tiles[index].neighbors.push_back(&tiles[index + length + 1]);
			}
			//top right tile
			else if (x == 24 && y == 0)
			{
				tiles[index].neighbors.push_back(&tiles[index - 1]);
				tiles[index].neighbors.push_back(&tiles[index + length]);
				tiles[index].neighbors.push_back(&tiles[index + length - 1]);
			}
			//bottom left tile
			else if (x == 0 && y == 15)
			{
				tiles[index].neighbors.push_back(&tiles[index + 1]);
				tiles[index].neighbors.push_back(&tiles[index - length]);
				tiles[index].neighbors.push_back(&tiles[index - length + 1]);
			}
			//bottom right tile
			else if (x == 24 && y == 15)
			{
				tiles[index].neighbors.push_back(&tiles[index - 1]);
				tiles[index].neighbors.push_back(&tiles[index - length]);
				tiles[index].neighbors.push_back(&tiles[index - length - 1]);
			}
			//top edge
			else if (y == 0)
			{
				tiles[index].neighbors.push_back(&tiles[index + 1]);
				tiles[index].neighbors.push_back(&tiles[index - 1]);
				tiles[index].neighbors.push_back(&tiles[index + length]);
				tiles[index].neighbors.push_back(&tiles[index + length + 1]);
				tiles[index].neighbors.push_back(&tiles[index + length - 1]);
			}
			//bottom edge
			else if (y == 15)
			{
				tiles[index].neighbors.push_back(&tiles[index + 1]);
				tiles[index].neighbors.push_back(&tiles[index - 1]);
				tiles[index].neighbors.push_back(&tiles[index - length]);
				tiles[index].neighbors.push_back(&tiles[index - length + 1]);
				tiles[index].neighbors.push_back(&tiles[index - length - 1]);
			}
			//left edge
			else if (x == 0)
			{
				tiles[index].neighbors.push_back(&tiles[index + 1]);
				tiles[index].neighbors.push_back(&tiles[index + length]);
				tiles[index].neighbors.push_back(&tiles[index + length + 1]);
				tiles[index].neighbors.push_back(&tiles[index - length]);
				tiles[index].neighbors.push_back(&tiles[index - length + 1]);
			}
			//right edge
			else if (x == 24)
			{
				tiles[index].neighbors.push_back(&tiles[index - 1]);
				tiles[index].neighbors.push_back(&tiles[index + length]);
				tiles[index].neighbors.push_back(&tiles[index + length - 1]);
				tiles[index].neighbors.push_back(&tiles[index - length]);
				tiles[index].neighbors.push_back(&tiles[index - length - 1]);
			}
			//everything else
			else
			{
				tiles[index].neighbors.push_back(&tiles[index + 1]);
				tiles[index].neighbors.push_back(&tiles[index - 1]);
				tiles[index].neighbors.push_back(&tiles[index + length]);
				tiles[index].neighbors.push_back(&tiles[index - length]);
				tiles[index].neighbors.push_back(&tiles[index + length + 1]);
				tiles[index].neighbors.push_back(&tiles[index + length - 1]);
				tiles[index].neighbors.push_back(&tiles[index - length + 1]);
				tiles[index].neighbors.push_back(&tiles[index - length - 1]);
			}
			index++;
		}
	}
}

void Board::DrawBoard(sf::RenderWindow& window)
{
	//draw tiles
	int i = 0;
	for (unsigned int y = 0; y < 16; y++)
	{
		for (unsigned int x = 0; x < 25; x++)
		{
			window.draw(tiles[i].backround);
			tiles[i].backround.setPosition(sf::Vector2f((float)x * 32.f, (float)y * 32.f));
			window.draw(tiles[i]);
			tiles[i].setPosition(sf::Vector2f((float)x * 32.f, (float)y * 32.f));
			i++;
		}
	}
	//draw everything else
	window.draw(test1);
	test1.setPosition(sf::Vector2f(688.f, 512.f));
	window.draw(test2);
	test2.setPosition(sf::Vector2f(624.f, 512.f));
	window.draw(test3);
	test3.setPosition(sf::Vector2f(560.f, 512.f));
	window.draw(face);
	face.setPosition(sf::Vector2f(368.f, 512.f));
	window.draw(debug);
	debug.setPosition(sf::Vector2f(496.f, 512.f));
	window.draw(digit1);
	digit1.setPosition(sf::Vector2f(0, 512));
	window.draw(digit2);
	digit2.setPosition(sf::Vector2f(21, 512));
	window.draw(digit3);
	digit3.setPosition(sf::Vector2f(42, 512));

}

void Board::SetCounter()
{
	string counter = to_string(remainingbombs);
	if (counter.size() == 3)
	{
		int middledigit = counter[1] - '0';
		int rightdigit = counter[2] - '0';
		digit1.setTextureRect(sf::IntRect(21 * 10, 0, 21, 32));
		digit2.setTextureRect(sf::IntRect(21 * middledigit, 0, 21, 32));
		digit3.setTextureRect(sf::IntRect(21 * rightdigit, 0, 21, 32));
	}
	else if (counter.size() == 2 && remainingbombs < 0)
	{
		int rightdigit = counter[1] - '0';
		digit1.setTextureRect(sf::IntRect(0, 0, 21, 32));
		digit2.setTextureRect(sf::IntRect(21 * 10, 0, 21, 32));
		digit3.setTextureRect(sf::IntRect(21 * rightdigit, 0, 21, 32));
	}
	else if (counter.size() == 2)
	{
		int middledigit = counter[0] - '0';
		int rightdigit = counter[1] - '0';
		digit1.setTextureRect(sf::IntRect(0, 0, 21, 32));
		digit2.setTextureRect(sf::IntRect(21 * middledigit, 0, 21, 32));
		digit3.setTextureRect(sf::IntRect(21 * rightdigit, 0, 21, 32));
	}
	else if (counter.size() == 1)
	{
		int rightdigit = counter[0] - '0';
		digit1.setTextureRect(sf::IntRect(0, 0, 21, 32));
		digit2.setTextureRect(sf::IntRect(0, 0, 21, 32));
		digit3.setTextureRect(sf::IntRect(21 * rightdigit, 0, 21, 32));
	}
	else
	{
		cout << "counter error" << endl;
	}
}

void Board::LoadTestBoard(string filename)
{
	face.setTexture(TextureManager::GetTexture("face_happy"));
	bombcount = 0;
	remainingbombs = 0;
	cout << filename << " Loaded" << endl;
	//shutoff debugmode and assign tiles based on infile
	debugmode = false;
	ifstream infile(filename);
	for (unsigned int i = 0; i < tiles.size(); i++)
	{
		char buffer = 'n';
		infile.get(buffer);
		if (buffer == '1')
		{
			tiles[i] = Tile(true);
			bombcount++;
			remainingbombs++;
		}
		else if (buffer == '0')
		{
			tiles[i] = Tile(false);
		}
		else
		{
			i--;
		}
	}
	infile.close();
	//link tiles and set their adjacentmines
	LinkTiles();
	for (unsigned int i = 0; i < tiles.size(); i++)
	{
		tiles[i].DetectMines();
	}
	SetCounter();
}

void Board::RandomReset()
{
	cout << "New game" << endl;
	//rest texture for face and bombcounter
	face.setTexture(TextureManager::GetTexture("face_happy"));

	debugmode = false;
	//Initialize current tiles to fresh ones WITH NO BOMBS
	for (unsigned int i = 0; i < tiles.size(); i++)
	{
		tiles[i] = Tile();
	}
	//randomly assign mines to tiles until there are 50 of them
	bombcount = 0;
	remainingbombs = 0;
	srand(time(NULL));
	while (bombcount < 50)
	{
		int index = rand() % 400;
		if (tiles[index].hasBomb)
		{

		}
		else
		{
			tiles[index].hasBomb = true;
			bombcount++;
			remainingbombs++;
		}
	}
	//Relink tiles and reset adjacentmines for each tile
	LinkTiles();
	for (unsigned int i = 0; i < tiles.size(); i++)
	{
		tiles[i].DetectMines();
	}
	SetCounter();
}

void Board::ToggleDebug()
{
	if (debugmode)
	{
		debugmode = false;
		for (unsigned int i = 0; i < tiles.size(); i++)
		{
			if (tiles[i].hasBomb)
			{
				tiles[i].setTexture(TextureManager::GetTexture("tile_hidden"));
			}
		}
	}
	else if (debugmode == false)
	{
		debugmode = true;
		for (unsigned int i = 0; i < tiles.size(); i++)
		{
			if (tiles[i].hasBomb)
			{
				tiles[i].setTexture(TextureManager::GetTexture("mine"));
			}
		}
	}
}

void Board::LeftClick(sf::Vector2f mousepos)
{
	sf::FloatRect test1box = test1.getGlobalBounds();
	sf::FloatRect test2box = test2.getGlobalBounds();
	sf::FloatRect test3box = test3.getGlobalBounds();
	sf::FloatRect facebox = face.getGlobalBounds();
	sf::FloatRect debugbox = debug.getGlobalBounds();

	if (test1box.contains(mousepos))
	{
		LoadTestBoard("boards/testboard1.brd");
	}
	else if (test2box.contains(mousepos))
	{
		LoadTestBoard("boards/testboard2.brd");
	}
	else if (test3box.contains(mousepos))
	{
		LoadTestBoard("boards/testboard3.brd");
	}
	else if (facebox.contains(mousepos))
	{
		RandomReset();
	}
	else if (debugbox.contains(mousepos))
	{
		ToggleDebug();
	}
	else
	{
		for (unsigned int i = 0; i < tiles.size(); i++)
		{
			sf::FloatRect current = tiles[i].getGlobalBounds();
			if (current.contains(mousepos))
			{
				tiles[i].Reveal();
				break;
			}
		}
	}
}

void Board::RightClick(sf::Vector2f mousepos)
{
	for (unsigned int i = 0; i < tiles.size(); i++)
	{
		sf::FloatRect current = tiles[i].getGlobalBounds();
		if (current.contains(mousepos))
		{
			if (tiles[i].isflagged)
			{
				remainingbombs++;
				SetCounter();
			}
			else
			{
				remainingbombs--;
				SetCounter();
			}
			tiles[i].Flagged();
			break;
		}
	}
}

bool Board::VictoryCheck()
{
	int revealed = 0;
	for (unsigned int i = 0; i < tiles.size(); i++)
	{
		if (tiles[i].isrevealed)
		{
			revealed++;
		}
	}
	if ((400 - revealed) == bombcount)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Board::Victory()
{
	cout << "Victory" << endl;
	face.setTexture(TextureManager::GetTexture("face_win"));
	for (unsigned int i = 0; i < tiles.size(); i++)
	{
		if (tiles[i].hasBomb)
		{
			tiles[i].setTexture(TextureManager::GetTexture("flag"));
			tiles[i].isrevealed = true;
		}
	}
}

bool Board::DefeatCheck()
{
	bool defeat = false;
	for (unsigned int i = 0; i < tiles.size(); i++)
	{
		if (tiles[i].isrevealed && tiles[i].hasBomb)
		{
			defeat = true;
			break;
		}
		else
		{
			defeat = false;
		}
	}
	return defeat;
}

void Board::Defeat(sf::RenderWindow& window)
{
	cout << "Lose state" << endl;
	face.setTexture(TextureManager::GetTexture("face_lose"));
	bool losestate = true;
	for (unsigned int i = 0; i < tiles.size(); i++)
	{
		if (tiles[i].hasBomb)
		{
			tiles[i].setTexture(TextureManager::GetTexture("mine"));
		}
	}
	sf::Event event;
	while (losestate == true)
	{
		window.pollEvent(event);
		if (event.type == sf::Event::Closed)
		{
			window.close();
		}
		if (event.type == sf::Event::MouseButtonReleased)
		{
			sf::Vector2i buffer = sf::Mouse::getPosition(window);
			sf::Vector2f mousepos = sf::Vector2f((float)buffer.x, (float)buffer.y);
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				sf::FloatRect facebox = face.getGlobalBounds();
				if (facebox.contains(mousepos))
				{
					losestate = false;
					RandomReset();
				}
			}
		}
		window.clear();
		DrawBoard(window);
		window.display();
	}
}
