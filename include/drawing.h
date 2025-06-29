#pragma once
#include <SFML/Graphics.hpp>
#include "aux.h"
#include "field.h"
using namespace sf;
class Risovalka {
    public:
    RenderWindow window;
    float scale = 0.3;
    Risovalka(int w, int h): window(VideoMode(w,h),"venom") {}
    void drawField(Field field){
        drawHull(field.hull,10,Color(0,255,0));
        // for(int i;i<MAX_ROBOT_COUNT;i++)
        // {
        //     drawCircle(field.allies[i].pos,ROBOT_R,Color(0,255,0));
        // }
        
    }
    void drawHull(Point *hull,float thickness,Color color)
    {
        int hull_len = int(sizeof(hull)/sizeof(hull[0]));
        for(int i;i<hull_len;i++)
        {
            if(i!=hull_len-1)
                drawLine(hull[i],hull[i+1],thickness,color);
            else
                drawLine(hull[i],hull[0],thickness,color);
        }
    }
    void drawCircle(Point pos, float radius, Color color) {
        pos += Point(FIELD_DX,FIELD_DY);
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
        window.clear();
    }
};

