#ifndef GAMEMASTER_HPP
#define GAMEMASTER_HPP

/*
Játéklogika vezérlő osztály.
*/

#include <vector>

class Amoba;

class GameMaster
{
public:
    GameMaster(Amoba*);
    virtual ~GameMaster();

    // vektort kezelő függvények
    void clear_tiles();
    std::vector<std::vector<char>> get_tiles() const;
    void set_length(int);
    size_t get_length() const;
    size_t get_moves() const;

    // játékszabály vezérlés függvények
    // valid lépés tesztelő. ha a lépés valid, akkor megtörténik és a számláló ('_moves') növelve lesz.
    void next_move(int,int); // A bemenetként kapott mezőt nézi meg, hogy üres-e. Ha igen, igaz értékkel tér vissza és lép egyet. Hamis érték esetén nem történik semmi.
    char check_char(char) const;
    void new_game(size_t);
    // DEBUG //
    void debug_print();

    // DEBUG //

protected:
    Amoba* _amoba;
    std::vector<std::vector<char>> _tiles;
    size_t _length; // mennyi mezõ van. a pálya mindig _length*_length méretű.
    size_t _moves;  // eddigi lépések száma. legfeljebb _length*_length lépés lehetséges.
    bool _running;
};

#endif // GAMEMASTER_HPP
