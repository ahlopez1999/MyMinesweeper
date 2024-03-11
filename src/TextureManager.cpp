#include "TextureManager.h"

map<string, sf::Texture> TextureManager::textures;

void TextureManager::LoadTexture(string texturename)
{
	system("dir");
	string path = "images/";
	path += texturename;
	path += ".png";
	textures[texturename].loadFromFile(path);
}
//stack overflow?
sf::Texture& TextureManager::GetTexture(string texturename)
{
	if (textures.find(texturename) == textures.end())
	{
		LoadTexture(texturename);
	}
	return textures[texturename];
}

void TextureManager::Clear()
{
	textures.clear();
}