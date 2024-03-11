#pragma once
#include <map>
#include <string>
#include <SFML/Graphics.hpp>
using std::map;
using std::string;

class TextureManager
{
	static map<string, sf::Texture> textures;
public:
	static void LoadTexture(string textureName);
	static sf::Texture& GetTexture(string texturename);
	static void Clear();
};

