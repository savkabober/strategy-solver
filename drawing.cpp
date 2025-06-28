#include <SFML/Graphics.hpp>
#include <cmath>
#include "drawing.h"
#include "aux.h"
using namespace sf;

RenderWindow window;
Risovalka::Risovalka(int w, int h): window(VideoMode(w,h),"venom") {}
void Risovalka::drawCircle(Point pos, float radius, Color color) {
    CircleShape circle(radius);
    circle.setFillColor(color);
    circle.setPosition(pos.x-radius, pos.y-radius);
    window.draw(circle);
}
void Risovalka::drawRectangle(Point pos, float width, float height, Color color) {
    RectangleShape rect(Vector2f(width, height));
    rect.setFillColor(color);
    rect.setPosition(pos.x, pos.y);
    window.draw(rect);
}
void Risovalka::drawLine(Point p1, Point p2, float thickness, Color color) {

    float dx = p2.x - p1.x;
    float dy = p2.y - p1.y;
    float length = std::sqrt(dx * dx + dy * dy);
    float angle = std::atan2(dy, dx) * 180 / 3.14159265f;

    RectangleShape line(Vector2f(length, thickness));
    line.setFillColor(color);
    line.setPosition(p1.x, p1.y);
    line.setRotation(angle);

    window.draw(line);
}
void Risovalka::update()
{
    window.display();        
    Event event;
    while (window.pollEvent(event)) {
        if (event.type == Event::Closed)
            window.close();
    }
    window.clear();
}


