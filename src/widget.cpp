#include "widget.hpp"
#include "application.hpp"

Widget::Widget(Application* parent, int x,int y,int sx,int sy) : _x(x), _y(y), _sx(sx), _sy(sy), _parent(parent), _visible(1), _enabled(1)
{
    _parent->register_widget(this);
}
Widget::~Widget() {}

bool Widget::is_selected() {return _selected;}

void Widget::select() {_selected = 1; on_selection();}
void Widget::deselect() {_selected = 0; on_deselection();}

void Widget::on_selection() {};
void Widget::on_deselection() {};

bool Widget::is_inside(int mx, int my)
{
    return (_x <= mx && mx <= _x+_sx) && (_y <= my && my <= _y+_sy);
}

bool Widget::is_visible() const
{
    return _visible;
}

void Widget::show()
{
    _visible = 1;
}

void Widget::hide()
{
    _visible = 0;
}

void Widget::toggle()
{
    _visible = !_visible;
}


bool Widget::is_enabled() const
{
    return _enabled;
}

void Widget::make_unselectable()
{
    _enabled = 0;
}

void Widget::make_selectable()
{
    _enabled = 1;
}
