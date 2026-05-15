#include "gamemaster.hpp"

class Amoba;

GameMaster::GameMaster(Amoba* parent) : _parent(parent)
{
    //ctor
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
    _tiles.clear(); // EZ VALSZEG ROSSZ !!!!!
    for (size_t j=0; j<_length; ++j)
    {
        for (size_t i=0; i<_length; ++i)
        {
            _tiles[j][i] = 'e';
        }
    }
}
