#pragma once
#include "SFML/Graphics.hpp"

#define MAX_ITEMS 3

class Menu
{
public:
	Menu(float widht, float height);
	~Menu();

	void draw(sf::RenderWindow& window);
	void MoveUp();
	void MoveDown();
	int GetSelected() { return selectedItem; };

private:
	int selectedItem;
	sf::Font font;
	sf::Text menu[MAX_ITEMS];
};

