#include "amobagrid.hpp"
#include "amobatile.hpp"
#include <iostream>

using namespace std;

AmobaGrid::AmobaGrid(Application* parent, int x, int y) : Widget(parent, x, y, 20*30, 20*30)
{
    //ctor
}

AmobaGrid::~AmobaGrid()
{
    for (size_t i=0; i<_amobatiles.size(); ++i)
    {
        for (AmobaTile* a : _amobatiles[i])
        {
            delete a;
        }
    }
}

void AmobaGrid::handle(genv::event ev)
{

}

void AmobaGrid::draw() const
{
    //cout << "AmobaGRID::draw()" << endl;
    for (size_t j=0; j<_amobatiles.size(); ++j)
    {
        for (size_t i=0; i<_amobatiles.size(); ++i)
        {
            _amobatiles[j][i]->draw();
        }
    }
}
