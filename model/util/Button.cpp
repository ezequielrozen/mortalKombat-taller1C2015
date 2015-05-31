#include "Button.h"

Button::Button(string aName, bool isSelected) {
	this->selected = isSelected;
	this->name = aName;
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
