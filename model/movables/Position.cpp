#include "Position.h"

Position::Position(float x, float y) {
    this->coordinateX = x;
    this->coordinateY = y;
}

Position::~Position() {

}

void Position::setCoordinateX(float x) {
    this->coordinateX = x;
}

void Position::setCoordinateY(float y) {
    this->coordinateY = y;
}

float Position::getCoordinateX() {
    return this->coordinateX;
}

float Position::getCoordinateY() {
    return this->coordinateY;
}

void Position::move() {

}
