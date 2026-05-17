#include "statictext.hpp"


using namespace genv;
using namespace std;

StaticText::StaticText(Application* parent, int x, int y, int sx, int sy, string text,
            color pcolor /* = BLACK */, size_t font_size /* = 20 */,
            string font /* = LiberationMono_Regular */)
            : Widget(parent,x,y,sx,sy), _text(text), _color(pcolor), _font(font), _font_size(font_size)
{
    make_unselectable();
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
    gout << move_to(_x+(_sx-gout.twidth(_text))/2, _y + (_sy -gout.cascent() - gout.cdescent())/2) << _color << text(_text);
}

void StaticText::set_text(string text)
{
    _text = text;
}

string StaticText::get_text() const
{
    return _text;
}
