#include "amobatile.hpp"
using namespace genv;
using namespace std;

AmobaTile::AmobaTile(Application* parent, int x, int y)
                : Rect2(parent, x, y, 20, 20, color(225,125,0)), _symbol('e')
{
    //ctor
}

AmobaTile::~AmobaTile()
{
    //dtor
}

void AmobaTile::handle(genv::event ev)
{

}

void AmobaTile::draw() const
{
    gout << BLACK << move_to(_x,_y) << box(_sx,_sy) << move_to(_x+2, _y+2) << _color << box(_sx-4, _sy-4)
         << move_to(_x+4, _y+4);
    if (_symbol == 'x')
    {
        // draw x
    }
    else if (_symbol == 'o')
    {
        // draw o
    }
}

void AmobaTile::set_symbol(char symbol)
{
    if (symbol == 'o' || symbol == 'x')
    {
        _symbol = symbol;
    }
    else
    {
        _symbol = 'e';
    }

}

char AmobaTile::get_symbol() const
{
    return _symbol;
}
