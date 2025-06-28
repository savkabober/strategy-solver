#pragma once
#include <SFML/Graphics.hpp>
#include "aux.h"
using namespace sf;
class Risovalka {
public:
    sf::RenderWindow window;
    Risovalka(int w, int h);
    void drawCircle(Point pos, float radius, Color color);
    void drawRectangle(Point pos, float width, float height, Color color);
    void drawLine(Point p1, Point p2, float thickness, Color color);
    void update();
};
