#ifndef AMOBAGRID_HPP
#define AMOBAGRID_HPP

#include "widget.hpp"

#include <vector>

class GameMaster;

class AmobaGrid : public Widget
{
    public:
        AmobaGrid(Application*, int, int, GameMaster*);
        virtual ~AmobaGrid();

        void handle(genv::event) override;
        void draw() const override;

        void update_tiles(std::vector<std::vector<char>>);
        void set_symbol(size_t, size_t, char);
        char get_symbol(size_t, size_t) const;

        void fill_empty(int);

        // DEBUG
        void debug_print();
        // DEBUG

    protected:
        std::vector<std::vector<char>> _amobatiles;
        GameMaster *_gmptr; // ez az egyetlen játék-specifikus widget, és tud kommunikálni a GameMaster-rel.
};

#endif // AMOBAGRID_HPP
