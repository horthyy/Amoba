#ifndef GAMEMASTER_HPP
#define GAMEMASTER_HPP

/*
Játéklogika vezérlő osztály.
Inicializálása meg kell történjen AmobaGrid létrehozása előtt.
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

    char check_char(char) const;

    void set_length(int);
    int get_length() const;

    // valid lépés tesztelő. ha a lépés valid, akkor megtörténik és a számláló ('_moves') növelve lesz.
    void test_move(int,int); // A bemenetként kapott mezőt nézi meg, hogy üres-e. Ha igen, igaz értékkel tér vissza és lép egyet. Hamis érték esetén nem történik semmi.

    // DEBUG //
    void debug_print();


    // DEBUG //

protected:
    Amoba* _amoba;
    std::vector<std::vector<char>> _tiles;
    size_t _length; // mennyi mezõ van. a pálya mindig _length*_length méretű.
    size_t _moves;  // eddigi lépések száma. legfeljebb _length*_length lépés lehetséges.
};

#endif // GAMEMASTER_HPP
