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

        bool is_visible() const; // visibility getter
        void show();
        void hide();
        void toggle();

        bool is_enabled() const;
        void make_unselectable();
        void make_selectable();

    protected:
        int _x, _y, _sx, _sy;

        bool _visible;
        // True value means it will be drawn and selectable if '_enabled == 1'.
        // Otherwise not drawn and not selectable.


        bool _enabled;
        // True value means it is selectable if '_visible == 1'.
        // False means not selectable.
        // Set to True in all Widgets by default.
        // If the widget is designed not to be interactable, this
        // bit needs to be set manually to False at initialization.

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
