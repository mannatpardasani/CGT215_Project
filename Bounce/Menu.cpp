#include "Menu.h"
#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <SFPhysics.h>

Menu::Menu(float width, float height) {
	if (!font.loadFromFile("glories.ttf")) {
		cout << "File not found\n";
	}
	menu[0].setFont(font);
	menu[0].setFillColor(sf::Color::Black);
	menu[0].setString("Play Easy");
	menu[0].setPosition(sf::Vector2f(width / 2  - 80, height / (MAX_ITEMS + 1) * 1));

	menu[1].setFont(font);
	menu[1].setFillColor(sf::Color::White);
	menu[1].setString("Play Hard");
	menu[1].setPosition(sf::Vector2f(width / 2 - 80, height / (MAX_ITEMS + 1) * 2));

	menu[2].setFont(font);
	menu[2].setFillColor(sf::Color::White);
	menu[2].setString("Exit");
	menu[2].setPosition(sf::Vector2f(width / 2 - 80, height / (MAX_ITEMS + 1) * 3));

	selectedItem = 0;

}

Menu::~Menu() {

}

void Menu::draw(sf::RenderWindow &window) {
	for (int i = 0; i < MAX_ITEMS; i++) {
		window.draw(menu[i]);
	}
}

void Menu::MoveUp() {
	if (selectedItem - 1 >= 0) {
		menu[selectedItem].setFillColor(sf::Color::White);
		selectedItem--;
		menu[selectedItem].setFillColor(sf::Color::Black);
	}
}

void Menu::MoveDown() {
	if (selectedItem + 1 < MAX_ITEMS) {
		menu[selectedItem].setFillColor(sf::Color::White);
		selectedItem++;
		menu[selectedItem].setFillColor(sf::Color::Black);
	}
}