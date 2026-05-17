#include "gamemaster.hpp"
#include "amoba.hpp"

using namespace std;
#include <vector>
#include <iostream>


GameMaster::GameMaster(Amoba* amoba) : _amoba(amoba), _length(15), _moves(0)
{
    clear_tiles();
}

GameMaster::~GameMaster()
{
    //dtor
}

void GameMaster::set_length(int n)
{
    _length = n;
    clear_tiles();
}

int GameMaster::get_length() const
{
    return _length;
}

void GameMaster::clear_tiles()
{
    if (_tiles.size() < _length)
    {
    vector<char> uj;
    for (size_t j=0; j<_length; ++j)
    {
        uj.clear();
        for (size_t i=0; i<_length; ++i)
        {
            uj.push_back('e');
        }
        _tiles.push_back(uj);
    }
    }
    else
    {
    _tiles.clear();
    for (size_t j=0; j<_length; ++j)
    {
        for (size_t i=0; i<_length; ++i)
        {
            _tiles[j][i] = 'e';
        }
    }

    }

    _amoba->update_grid();
}

vector<vector<char>> GameMaster::get_tiles() const
{
    return _tiles;
}


// DEBUG
void GameMaster::debug_print()
    {
        cout << "_gamemaster._length = " << _length << endl;
        for (size_t i=0; i<_length; ++i)
        {
            for (size_t j=0; j<_length; ++j)
            {
                cout << _tiles[i][j] << " ";
            }
            cout << endl;
        }
    }

// DEBUG END

void GameMaster::test_move(int j, int i)
{

    if (_tiles[j][i] == 'e')
    {
        // eldönti hogy x vagy o legyen lerakva
        if (0 == _moves%2)
        {
            _tiles[j][i] = 'x';
        }
        else
        {
            _tiles[j][i] = 'o';
        }
        ++_moves;
        _amoba->update_grid();

        // teszteljük, hogy van-e egymás mellett 5 valamelyikbõl
        char testfor_x = check_char('x');
        char testfor_o = check_char('o');

        // DEBUG
        //cout << "teszt eredmenye: " << endl << "testfor_x = " << testfor_x << ", " << endl << "testfor_o = " << testfor_o << endl;

        if      (testfor_x == 'x') {cout << "x nyert" << endl;}
        else if (testfor_o == 'o') {cout << "o nyert" << endl;}

    }
    cout << "GameMaster: moves = " << _moves << endl;
}

char GameMaster::check_char(char s) const
{
    // teszteli, hogy van-e 5 darab egymás mellett sorban vagy oszlopban az 's' karakterbõl.
    // futásidõben kizárólag 'o' vagy 'x' paraméterrel lesz meghívva.
    // visszatérési értéke 'x', ha van 5db x, 'o', ha van 5db o, és ha egyik sem, akkor 'e' karakterrel tér vissza (akkor is, ha abból sincs 5db).

    size_t ctr;

    // sor teszt
    for (size_t i=0; i<_length; ++i)
    {
        ctr = 0;
        for (size_t j=0; j<_length; ++j)
        {
            if (_tiles[i][j] == s) {++ctr;} else {ctr=0;}
            if (5==ctr) {return s;}
        }
    }

    //oszlop teszt
    for (size_t i=0; i<_length; ++i)
    {
        ctr = 0;
        for (size_t j=0; j<_length; ++j)
        {
            if (_tiles[j][i] == s) {++ctr;} else {ctr=0;}
            if (5==ctr) {return s;}
        }
    }

    // nincs 5 egymás mellett
    return 'e';
}
