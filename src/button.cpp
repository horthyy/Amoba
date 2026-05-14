#include "button.hpp"

using namespace genv;

Button::Button(Application *parent,
        int x, int y, int sx, int sy,
        std::string label,
        std::function<void()> f)
    : Widget(parent, x, y, sx, sy),
      _label(label), _f(f)
{

}

Button::~Button()
{

}

void Button::draw() const
{
    gout.load_font("Fonts/LiberationSans-Regular.ttf", 20);

    gout << move_to(_x, _y) << color(200, 200, 200) << box(_sx, _sy)
         << move_to(_x + (_sx - gout.twidth(_label))/2, _y + (_sy - gout.cascent() - gout.cdescent())/2)
         << color(0,0,0) << text(_label);
}

void Button::handle(event ev)
{
    if (ev.type == ev_mouse)
    {
        if (ev.button == btn_left)
        {
            action();
        }
    }
}

void Button::action()
{
    _f();
}
