#include "gamemaster.hpp"
#include "amoba.hpp"

using namespace std;
#include <vector>


GameMaster::GameMaster(Amoba* amoba) : _amoba(amoba), _length(15), _moves(0), _running(0), _player2_com(0)
{
    clear_tiles();
}

GameMaster::~GameMaster()
{
    //dtor
}

void GameMaster::new_game(size_t new_length, bool is_player2_com)
{
    /*
    paraméterek:
     - size_t new_length: a pálya mérete
     - bool is_player2_com: igaz, ha gépi játékossal játszunk, és hamis, ha a másik játékos is ember.

    */
    set_length(new_length);
    _running = 1;
    _player2_com = is_player2_com;
    _amoba->update_grid();


}

void GameMaster::set_length(int n)
{
    _length = n;
    clear_tiles();
}

size_t GameMaster::get_length() const
{
    return _length;
}

size_t GameMaster::get_moves() const
{
    return _moves;
}

void GameMaster::clear_tiles()
{
    _tiles = vector<vector<char>>(_length, vector<char>(_length, 'e'));
}

vector<vector<char>> GameMaster::get_tiles() const
{
    return _tiles;
}


void GameMaster::next_move(int j, int i)
{
    if (_running == 0) {return;}

    // lépés elhelyezése teszt
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

        _last_x = j;
        _last_y = i;

        // teszteljük, hogy van-e egymás mellett 5 valamelyikbõl
        char testfor_x = check_char('x');
        char testfor_o = check_char('o');


        if (testfor_x == 'x') // X WON
        {
            _running = 0;
            _amoba->game_over('x');
            return;
        }
        else if (testfor_o == 'o') // O WON
        {
            _running = 0;
            _amoba->game_over('o');
            return;
        }

        // pálya betelésének esete
        if (_moves == _length*_length) // DONTETLEN
        {
            _amoba->game_over('e');
            return;
        }


        // gépi játékos lépése
        if (_moves%2 == 1 && _player2_com)
        {
            vector<size_t> com =  generate_next_com_move();
            next_move(com[0], com[1]);
        }

    }
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

    // átló teszt 1 (főátlóval párhuzamosak)
    for (size_t i=0; i<_length-5+1; ++i)
    {
        for (size_t j=0; j<_length-5+1; ++j)
        {
            if (
                _tiles[i][j] == s &&
                _tiles[i+1][j+1] == s &&
                _tiles[i+2][j+2] == s &&
                _tiles[i+3][j+3] == s &&
                _tiles[i+4][j+4] == s
                )
                {return s;}
        }
    }


    // átló teszt 2 (mellékátlóval párhuzamosak)
    for (size_t i=0; i<_length-5+1; ++i)
    {
        for (size_t j=0; j<_length-5+1; ++j)
        {
            if (
                _tiles[i+4][j] == s &&
                _tiles[i+3][j+1] == s &&
                _tiles[i+2][j+2] == s &&
                _tiles[i+1][j+3] == s &&
                _tiles[i][j+4] == s
                )
                {return s;}
        }
    }

    // nincs 5 egymás mellett
    return 'e';
}

// gépi játékos függvények
void GameMaster::set_player2(bool b)
{
    _player2_com = b;
}

vector<size_t> GameMaster::generate_next_com_move() const
{
    /*
    Gépi játékos működése:
    Nem tudunk brute forceolni vagy minimax algoritmusozni (mondjuk az ugyanaz) mert
    a 15x15 és 30x30 közötti táblaméret nem triviális.
    Helyette megnézem a legutóbbi lépés környékén a lehetséges lépéseket mindkét fél számára,
    és egy számot rendelek minden lehetőséghez.
    Minél nagyobb ez a szám, annál jobb a gépi játékos számára, és minél kisebb,
    annál rosszabb ez a lehetőség.
    Ezt a számot az alapján döntöm el, hogy
    meg lehet-e csinálni egy 2-es, 3-as, 4-es vagy 5-ös sort/oszlopot/átlót az adott lépéssel.

    Megvalósítás:
    - A "legutóbbi lépés környékének" választottam a legutóbbi move 5x5 környezetét.
    - Ezeket a pontokat a 'get_nearby_empty_tiles()' függvény megkeresi.
    - Az 'evaluation()' függvény egy számot rendel mindegyik közeli ponthoz.
    - A végén a legnagyobb értéket kapott pontra lép a gépi játékos. Több maximum esetén az elsőre lép.

    */

    vector<vector<size_t>> nearby = get_nearby_empty_tiles();

    vector<size_t> best_move = {0, 0};
    int best_score = -9999999999;
    int x_score, o_score, total;
    for (vector<size_t> p : nearby)
    {
        x_score = evaluation(p[0], p[1], 'x');
        o_score = evaluation(p[0], p[1], 'o');
        total = o_score + 0.5*x_score;
        if (total > best_score)
        {
            best_score = total;
            best_move[0] = p[0];
            best_move[1] = p[1];
        }
    }



    return best_move;
}

vector<vector<size_t>> GameMaster::get_nearby_empty_tiles() const
{
    // get 5x5 slice of board centered at the last move point (_last_x, _last_y).
    vector<vector<size_t>> v;
    int x, y;
    int depth = _length/2 +1;
    for (int i=-depth; i<=depth; ++i)
    {
        for (int j=-depth; j<=depth; ++j)
        {
            x = _last_x + i;
            y = _last_y + j;
            if (0 <= x && x < _length && 0 <= y && y < _length)
            {
                if ('e' == _tiles[x][y]) {v.push_back(vector<size_t> {x, y});}
            }
        }
    }

    return v;
}


int GameMaster::evaluation(size_t p0, size_t p1, char c) const
{
    vector<vector<char>> cpy; // copy of _tiles
    vector<char> sor;
    for (size_t i=0; i<_length; ++i)
    {
        sor.clear();
        for (size_t j=0; j<_length; ++j)
        {
            sor.push_back(_tiles[i][j]);
        }
        cpy.push_back(sor);
    }

    // evaluating (i,j) point
    cpy[p0][p1] = c;
    size_t ctr;
    size_t max_row = 0;
    size_t max_col = 0;
    size_t max_dg1 = 0;
    size_t max_dg2 = 0;

    // sor teszt
    for (size_t i=0; i<_length; ++i)
    {
        ctr = 0;
        for (size_t j=0; j<_length; ++j)
        {
            if (cpy[i][j] == c) {
                ++ctr;
            } else {
                if (ctr > max_row) {max_row = ctr;}
                ctr=0;
            }
        }
    }

    //oszlop teszt
    for (size_t i=0; i<_length; ++i)
    {
        ctr = 0;
        for (size_t j=0; j<_length; ++j)
        {
            if (cpy[j][i] == c) {
                ++ctr;
            } else {
                if (ctr > max_col) {max_col = ctr;}
                ctr=0;
            }
        }
    }


    // átló teszt 1 (főátlóval párhuzamosak)
    for (size_t i=0; i<_length-5+1; ++i)
    {
        for (size_t j=0; j<_length-5+1; ++j)
        {
            ctr = (cpy[i][j]==c) + (cpy[i+1][j+1]==c) + (cpy[i+2][j+2]==c) + (cpy[i+3][j+3]==c) + (cpy[i+4][j+4]==c);
            if (ctr > max_dg1) {max_dg1 = ctr;}
        }
    }


    // átló teszt 2 (mellékátlóval párhuzamosak)
    for (size_t i=0; i<_length-5+1; ++i)
    {
        for (size_t j=0; j<_length-5+1; ++j)
        {
            ctr = (cpy[i+4][j]==c) + (cpy[i+3][j+1]==c) + (cpy[i+2][j+2]==c) + (cpy[i+1][j+3]==c) + (cpy[i][j+4]==c);
            if (ctr > max_dg2) {max_dg2 = ctr;}
        }
    }

    size_t eval = 0;
    if (eval < max_row) {eval = max_row;}
    if (eval < max_col) {eval = max_col;}
    if (eval < max_dg1) {eval = max_dg1;}
    if (eval < max_dg2) {eval = max_dg2;}

    if (eval > 5) {eval = 5;}
    vector<int> scores = {0, 0, 10, 100, 100000, 1000000000};
    return scores[eval];

}
