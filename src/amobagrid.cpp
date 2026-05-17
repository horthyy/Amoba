#include "amobagrid.hpp"
#include "gamemaster.hpp"
#include <iostream>

#include <vector>

using namespace std;
using namespace genv;

AmobaGrid::AmobaGrid(Application* parent, int x, int y, GameMaster* gmptr) : Widget(parent, x, y, 600, 600), _gmptr(gmptr)
{
    fill_empty(_gmptr->get_length()); // initial values to prevent crashing.
}

AmobaGrid::~AmobaGrid()
{

}

void AmobaGrid::handle(genv::event ev)
{
    if (ev.type == ev_mouse)
    {
        if (ev.button == btn_left)
        {
            int w = 20 * 30 / _amobatiles.size();
            //cout << "bal klikk, " << ev.pos_x << ", " << ev.pos_y << " : ";
            if (_x <= ev.pos_x && ev.pos_x <= _x+_sx && _y <= ev.pos_y && ev.pos_y <= _y + _sy)
            {
                size_t i = (ev.pos_x - _x)/w;
                size_t j = (ev.pos_y - _y)/w;
                //cout << j << ". sor, " << i << ". osz" << endl;
                _gmptr->test_move(j,i);

            }
        }
    }
}

void AmobaGrid::draw() const
{
    int w = 20 * 30 / _amobatiles.size();
    char symbol;
    for (size_t i=0; i<_amobatiles.size(); ++i)
    {
        for (size_t j=0; j<_amobatiles.size(); ++j)
        {
            symbol = _amobatiles[j][i];
            gout << BLACK << move_to(_x+i*w,_y+j*w) << box(w,w) << move_to(_x+i*w+2, _y+j*w+2) << WHITE << box(w-4, w-4)
                 << move_to(_x+i*w+4, _y+j*w+4);

            //gout << BLACK << move_to(_x+i*w+5,_y+j*w+15) << text(to_string(j) + '\n' + to_string(i)); // DEBUG

            if (symbol == 'x')
            {
                gout << BLACK << move_to(_x+i*w+6,_y+j*w+6) << line(w-12, w-12) << move_to(_x+i*w+6,_y+(j+1)*w-6) << line(w-12, -w+12);
            }
            else if (symbol == 'o')
            {
                gout << BLACK << move_to(_x+i*w+6,_y+j*w+6) << line(w-12,0) << line(0, w-12) << line(-w+12,0) << line(0, -w+12);
            }
        }
    }
}

void AmobaGrid::update_tiles(vector<vector<char>> v)
{
    if (v.size() != _amobatiles.size()) {cout << "_amobatiles.size() updated from " << _amobatiles.size() << " to " << _amobatiles.size() << endl;}
    _amobatiles = v;
    //_sx = v.size()*20; _sy = v.size()*20;
}

void AmobaGrid::set_symbol(size_t i, size_t j, char symbol)
{
    if (symbol == 'o' || symbol == 'x')
    {
        _amobatiles[j][i] = symbol;
    }
    else
    {
        _amobatiles[j][i] = 'e';
    }

}

char AmobaGrid::get_symbol(size_t i, size_t j) const
{
    return _amobatiles[i][j];
}

void AmobaGrid::fill_empty(int w)
{
    _amobatiles = vector<vector<char>>(w, vector<char>(w, 'e'));
}


// DEBUG
void AmobaGrid::debug_print()
    {
        cout << "_amobatiles.size() = " << _amobatiles.size() << endl;
        for (size_t i=0; i<_amobatiles.size(); ++i)
        {
            for (size_t j=0; j<_amobatiles.size(); ++j)
            {
                cout << _amobatiles[i][j] << " ";
            }
            cout << endl;
        }
    }
