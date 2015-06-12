#include "Button.h"

Button::Button(string aName, bool isSelected, int x, int y, int w, int h) {
	this->selected = isSelected;
	this->name = aName;

	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
}

Button::~Button() {
	
}

bool Button::isSelected() {
	return this->selected;
}

void Button::setSelected(bool select) {
	this->selected = select;
}

string Button::getName() {
	return this->name;
}

int Button::getX() {
	return this->x;
}

int Button::getY() {
	return this->y;
}

int Button::getWidth() {
	return this->w;
}

int Button::getHeight() {
	return this->h;
}

bool Button::checkBoundaries(unsigned short x, unsigned short y) {
	return (x > this->x && x < this->x + this->w && y > this->y && y < this->y + this->h);
}