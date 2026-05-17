#include "rect2.hpp"
using namespace genv;

Rect2::Rect2(Application* parent, int x, int y, int sx, int sy, color clr)
                : Widget(parent, x, y, sx, sy), _color(clr)
{
    make_unselectable();
}

Rect2::~Rect2()
{
    //dtor
}

void Rect2::handle(genv::event ev)
{

}

void Rect2::draw() const
{
    gout << BLACK << move_to(_x,_y) << box(_sx,_sy) << move_to(_x+2, _y+2) << _color << box(_sx-4, _sy-4);
}

void Rect2::set_color(color c)
{
    _color = c;
}

color Rect2::get_color() const
{
    return _color;
}
