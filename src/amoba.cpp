#include "amoba.hpp"
#include "gamemaster.hpp"

#include <iostream>

#include <vector>
using namespace std;

Amoba::Amoba() : Application(640, 640, "Amoba")
{
    _gamemaster = new GameMaster(this);

    //_gamemode_dropdown = new Dropdown(this, 300, 200, 250, 50, vector<string> {"Player1 vs Player2", "Player vs Computer"}, 2);
    //_size_spinbox = new Spinbox(this, 20, 20, 120, 40, 20, 15, 30);

    //_start_btn = new Button(this, 300, 300, 100, 40, "Start", [](){});
    //_restart_btn = new Button(this, 300, 400, 100, 40, "New Game", [](){});
    //_backtomenu_btn = new Button(this, 300, 500, 100, 40, "Back to Menu", [](){});

    _grid = new AmobaGrid(this, 20, 20);


}

Amoba::~Amoba()
{
    //dtor
}

void Amoba::set_grid()
{

}
