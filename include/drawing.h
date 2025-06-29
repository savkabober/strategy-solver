#pragma once
#include <SFML/Graphics.hpp>
#include "aux.h"
#include "field.h"
using namespace sf;
class Risovalka {
    public:
    RenderWindow window;
    float scale = 0.1;
    Risovalka(int w, int h): window(VideoMode(w,h),"venom") {}
    void drawCircle(Point pos, float radius, Color color) {
        pos.y *=-1;
        pos += Point(FIELD_DX+FIELD_MARGIN,FIELD_DY+FIELD_MARGIN);
        pos *=scale;
        radius *=scale;
        CircleShape circle(radius);
        circle.setFillColor(color);
        circle.setPosition(pos.x-radius, pos.y-radius);
        window.draw(circle);
    }
    void drawRectangle(Point pos, float width, float height, Color color) {
        RectangleShape rect(Vector2f(width, height));
        rect.setFillColor(color);
        rect.setPosition(pos.x, pos.y);
        window.draw(rect);
    }
    void drawLine(Point p1, Point p2, float thickness, Color color) {

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
    void update()
    {
        window.display();        
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }
        window.clear(FIELD_COLOR);
    }
};

