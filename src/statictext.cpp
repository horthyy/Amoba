#include "statictext.hpp"


using namespace genv;
using namespace std;

StaticText::StaticText(Application* parent, int x, int y, int sx, int sy, string text,
            string font /* = LiberationMono_Regular */, int font_size /* = 11 */)
            : Widget(parent,x,y,sx,sy), _text(text), _font(font), _font_size(font_size)
{

}



StaticText::~StaticText()
{
    //dtor
}

void StaticText::handle(genv::event ev)
{

}

void StaticText::draw() const
{
    gout.load_font(_font, _font_size);
    gout << move_to(_x,_y) << WHITE << box(_sx,_sy);
    gout << move_to(_x+_sx-gout.twidth(_text), _y + (_sy -gout.cascent() - gout.cdescent())/2) << BLACK << text(_text);
}

void StaticText::set_text(string text)
{
    _text = text;
}

string StaticText::get_text() const
{
    return _text;
}
