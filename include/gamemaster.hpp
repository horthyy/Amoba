#ifndef GAMEMASTER_HPP
#define GAMEMASTER_HPP

#include <vector>

class Amoba;

class GameMaster
{
public:
    GameMaster(Amoba*);
    virtual ~GameMaster();

    void clear_tiles();
    void set_length(int);
    int get_length() const;
    std::vector<std::vector<char>> get_tiles() const;

protected:
    Amoba* _parent;
    std::vector<std::vector<char>> _tiles;
    int _length; // mennyi mezõ van. a pálya mindig _length*_length méretû.
};

#endif // GAMEMASTER_HPP
