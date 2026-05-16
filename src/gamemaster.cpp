#include "gamemaster.hpp"
#include "amoba.hpp"

using namespace std;
#include <vector>
#include <iostream>


GameMaster::GameMaster(Amoba* parent) : _parent(parent), _length(15)
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
}

vector<vector<char>> GameMaster::get_tiles() const
{
    return _tiles;
}
