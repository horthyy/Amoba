#ifndef WIDGET_HPP_INCLUDED
#define WIDGET_HPP_INCLUDED

#include "graphics.hpp"

class Application;

class Widget
{
    public:
        Widget(Application* parent, int x,int y,int sx,int sy);
        virtual ~Widget();
        bool is_selected();
        void select();
        void deselect();

        virtual void draw() const = 0;
        virtual void handle(genv::event ev) = 0;
        virtual bool is_inside(int mx, int my);
        virtual void on_selection();
        virtual void on_deselection();

    protected:
        int _x, _y, _sx, _sy;
        bool _selected = 0;
        Application* _parent;

};

// const-ok

const genv::color WHITE = genv::color(255,255,255);
const genv::color BLACK = genv::color(0,0,0);
const genv::color LIGHT_GREY = genv::color(240,240,240);
const genv::color GREY = genv::color(120,120,120);
const genv::color FOCUS = genv::color(255,255,137);
const genv::color GREEN = genv::color(0,255,0);
const genv::color BG = WHITE;

#endif // WIDGET_HPP_INCLUDED
