#ifndef AMOBAGRID_HPP
#define AMOBAGRID_HPP

#include "widget.hpp"

#include <vector>
class AmobaTile;

class AmobaGrid : public Widget
{
    public:
        AmobaGrid(Application*, int, int);
        virtual ~AmobaGrid();

        void handle(genv::event) override;
        void draw() const override;

    protected:
        std::vector<std::vector<AmobaTile*>> _amobatiles;
};

#endif // AMOBAGRID_HPP
