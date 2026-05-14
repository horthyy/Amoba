#include "spinbox.hpp"
#include "graphics.hpp"

using namespace genv;

Spinbox::Spinbox(Application* parent, int x, int y, int sx, int sy, int value, int lowlimit, int uplimit)
                 : Widget(parent,x,y,sx,sy), _value(value), _lowlimit(lowlimit), _uplimit(uplimit)
{
clamp_value();
}

void Spinbox::draw() const
{
    int h = gout.cascent() + gout.cdescent();
    gout << move_to(_x, _y) << BLACK << box(_sx, _sy)
         << move_to(_x+1, _y+1) << (_selected ? FOCUS : WHITE) << box(_sx-2, _sy-2)
         << move_to(_x+10, _y+_sy/2 - h/2) << BLACK << text(std::to_string(_value))
         << move_to(_x + _sx - 20, _y) << line(0, _sy) << genv::move(0, -_sy/2) << line(20,0)
         << move_to(_x + _sx - 15, _y + _sy/4 - h/2) << text("+") << move_to(_x + _sx - 13, _y + 3*_sy/4 - h/2) << text("-")
    ;
}

void Spinbox::handle(event ev)
{
    // számlálót változtató gombok kezelése
    if (ev.type == ev_key)
    {
        switch (ev.keycode)
        {
        case key_up:
            _value++;
            break;
        case key_down:
            _value--;
            break;
        case key_pgup:
            _value+=10;
            break;
        case key_pgdn:
            _value-=10;
            break;
        }
    }
    if (ev.type == ev_mouse)
    {
        if (ev.button == btn_wheelup) {_value++;}
        if (ev.button == btn_wheeldown) {_value--;}
    }

    if (ev.type == ev_mouse && ev.button == btn_left && (_x+_sx-20 < ev.pos_x && ev.pos_x < _x+_sx) )
    {
        if (_y<ev.pos_y && ev.pos_y<_y+_sy/2) {_value++;}
        else if (_y+_sy/2<ev.pos_y && ev.pos_y<_y+_sy) {_value--;}
    }

    // az érték a megengedett intervallumon belül lesz tartva
    clamp_value();
}

int Spinbox::get_value() const
{
    return _value;
}

void Spinbox::clamp_value()
{
    if (_value <= _lowlimit) {_value = _lowlimit;}
    if (_value >= _uplimit) {_value = _uplimit;}
}

Spinbox::~Spinbox() {}
