#include "dropdown.hpp"
#include "graphics.hpp"

using namespace genv;
using namespace std;

Dropdown::Dropdown(Application* parent, int x, int y, int sx, int sy, std::vector<std::string> values,
                   int max_height /* = 3 */, int _index /* = 0 */ )
                   : Widget(parent,x,y,sx,sy), _values(values), _max_height(max_height), _index(_index)
{
_number_of_pages = _values.size()/_max_height + (_values.size()%_max_height > 0) -1;
_page_index = _index/_max_height;
}

bool Dropdown::is_inside(int mx, int my)
{
    // ez a widget méretet tud változtatni, ezért alakjától függõen változik a figyelt terület
    if (!_dropdown) {return (_x <= mx && mx <= _x+_sx) && (_y <= my && my <= _y+_sy);}
    else
    {
        int height;
        //cout << "va " << _values.size()%_max_height << " es " << _values.size()%_max_height<<endl;
        if (_page_index == _number_of_pages && _values.size()%_max_height)
            {height = _sy * ( 1 + _values.size()%_max_height);}
        else
            {height = _sy + _sy*_max_height;}

        return (_x <= mx && mx <= _x+_sx) && (_y < my && my <= _y + height);
    }
}

void Dropdown::draw_unit(int px, int py, std::string txt) const
{
    int h = gout.cascent() + gout.cdescent();
    gout << move_to(_x + px, _y + py) << BLACK << box(_sx, _sy)
         << move_to(_x+px+1, _y+py+1) << ((_selected && py==0) ? FOCUS : WHITE) << box(_sx-2, _sy-2)
         << move_to(_x+px+10, _y+py+_sy/2 - h/2) << BLACK << text(txt)
    ;

}

void Dropdown::draw_page() const
{

    gout << LIGHT_GREY << move_to(_x, _y+_sy) << box(_sx, _sy*_max_height);
    int idx, i;
    for (i = 0; i<_max_height; ++i)
    {
        idx = i + _page_index*_max_height;
        if (idx>=_values.size()) {break;}
        draw_unit(0, (1+i)*_sy, _values[idx]);
    }

    // plusz dekoracio
    gout << BLACK << move_to(_x,_y) << line(0,_sy*(1+_max_height))
         << line(_sx,0)
         << move_to(_x,_y+(1+i)*_sy) << line(_sx,0)
    ;
}

void Dropdown::draw_scollbar() const
{
    // ha csak egy oldal van nincs scrollbar
    if (_number_of_pages == 0) {return;}

    // scrollbar y-size
    double h = (double)(_sy*_max_height -8) / (1+_number_of_pages);

    gout << move_to(_x + _sx - 20, _y + _sy) << BLACK << box(20, _max_height*_sy)
         << move_to(_x + _sx - 20+2, _y + _sy+2) << WHITE << box(20-4, _max_height*_sy-4)
         << move_to(_x + _sx - 20+4, _y + _sy+4 + h*_page_index) << GREY << box(20-8, h)
    ;
}

void Dropdown::draw() const
{
    // kis háromszög orientation az alapján, hogy meg van-e nyitva a menü
    draw_unit(0,0,get_value());
    if (!_dropdown) // lefele nezo haromszog
    {gout << move_to(_x + _sx -32, _y + _sy/2 -4) << BLACK << line(16,0) << line(-8,8) << line(-8,-8);}
    else //felfele nezo haromszog
    {gout << move_to(_x + _sx -32, _y + _sy/2 +4) << BLACK << line(16,0) << line(-8,-8) << line(-8,8);}

    if (_dropdown) {draw_page();draw_scollbar();}
}


void Dropdown::handle(event ev)
{
    // fel/le gombok és görgő fel/le tekerés kezelése
    if (_dropdown)
    {
        if ((ev.type == ev_key && ev.keycode == key_up) || (ev.type == ev_mouse && ev.button == btn_wheelup))
            {_page_index = clamp(_page_index-1, 0, _number_of_pages);}
        if ((ev.type == ev_key && ev.keycode == key_down) || (ev.type == ev_mouse && ev.button == btn_wheeldown))
            {_page_index = clamp(_page_index+1, 0, _number_of_pages);}
    }
    if (!_dropdown)
    {
        if (ev.type == ev_key && ev.keycode == key_down) {_dropdown = 1;}
    }

    // annak meghatározása, hogy a listának melyik elemét választottuk ki.
    if (ev.type == ev_mouse && ev.button == btn_left && is_inside(ev.pos_x, ev.pos_y))
    {
        _dropdown = !_dropdown;

        if (!_dropdown) {
        // speciális eset: ha a widget azon részére kattintunk, amin a jelenleg kiválasztott elem látható,
        // akkor egyszerûen összecsukódik a menü, a kiválasztás nem változik.
        if (ev.pos_y <= _y + _sy)
        {

        }
        // speciális eset: ha az utolsó oldal van megjelenítve és az nem teljes tételszámú, mert van maradék
        else if (_page_index == _number_of_pages && _values.size()%_max_height)
        {

            for (int i = 0; i < _values.size()%_max_height; ++i)
            {
                if (_y + _sy*(1+i) <= ev.pos_y && ev.pos_y <= _y + _sy*(2+i))
                {
                    _index = _page_index*_max_height + i;
                }
            }
        }
        else // ha teljes ('_max_height' db elemet tartalmazó) oldal van megjelenítve
        {

            for (int i = 0; i < _max_height; ++i)
            {
                if (_y + _sy*(1+i) <= ev.pos_y && ev.pos_y <= _y + _sy*(2+i))
                {
                    _index = _page_index*_max_height + i;
                }
            }

        } // nagy if statement vege
        _page_index = _index/_max_height;
        } // if dropdown vege
    }
}

void Dropdown::on_deselection() {_dropdown = 0;}

std::string Dropdown::get_value() const
{
    return _values[_index];
}

Dropdown::~Dropdown() {}

double Dropdown::clamp(double x, double a, double b) const
{
    if (x<a) {return a;}
    if (x>b) {return b;}
    return x;
}
