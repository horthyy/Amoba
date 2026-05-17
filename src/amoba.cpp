#include "amoba.hpp"
#include "gamemaster.hpp"

#include <iostream>

#include <vector>
using namespace std;
using namespace genv;

Amoba::Amoba() : Application(640, 640, "Amoba", color(125, 125, 125))
{
    _gamemode_dropdown = new Dropdown(this, 310, 460, 280, 40, vector<string> {"Player1 vs Player2", "Player vs Computer"}, 2);
    _size_spinbox = new Spinbox(this, 120, 460, 80, 40, 15, 15, 30);

    _title_label = new StaticText(this, 50, 50, 540, 70, "TIC-TAC-TOE", BLACK, 50);
    _size_label = new StaticText(this, 90, 410, 140, 30, "Level Size");
    _gamemode_label = new StaticText(this, 385, 410, 130, 30, "Game Mode");
    _options_label = new StaticText(this, 240, 330, 160, 40, "- Options -");

    _gamemaster = new GameMaster(this);
    _grid = new AmobaGrid(this, 20, 20, _gamemaster);
    _grid->hide();

    _popup_window = new Rect2(this, 120, 170, 400, 300, color(255,125,0));
    _popup_label = new StaticText(this, 220, 190, 200, 80, "andor", BLACK, 40);

    _btn_start = new Button(this, 260, 240, 120, 60, "Start",             [=](){btn_handler("Start");});
    _btn_restart = new Button(this, 240, 310, 160, 60, "New Game",        [=](){btn_handler("New Game");});
    _btn_backtomenu = new Button(this, 240, 390, 160, 60, "Back to Menu", [=](){btn_handler("Back to Menu");});

    _bg_color_list.push_back(color(255,0,0));
    _bg_color_list.push_back(color(0,255,0));
    _bg_color_list.push_back(color(0,0,255));
    _bg_color_list.push_back(color(0,255,255));
    _bg_color_list.push_back(color(255,255,0));
    _bg_color_list.push_back(color(255,0,255));
    _bg_color_list.push_back(color(255,255,255));

    change_state_to(st_mainmenu);
}

Amoba::~Amoba()
{
    //dtor
}

void Amoba::update_grid()
{
    _grid->update_tiles(_gamemaster->get_tiles());
}

void Amoba::action(event ev)
{
    // DEBUG
    if (ev.keycode == 'p')
    {
        cout << "DEBUG (p): PRINT" << endl;
        cout << "GameMaster data:" << endl; _gamemaster->debug_print();
        cout << "AmobaGrid data:" << endl; _grid->debug_print();

    }
}

void Amoba::change_state_to(State st)
{
    State prev = _state;
    _state = st;
    switch (st)
    {
    case st_mainmenu:
        _gamemode_dropdown->show();
        _size_spinbox->show();
        _btn_start->show();
        _btn_restart->hide();
        _btn_backtomenu->hide();
        _grid->hide();
        _title_label->show();
        _size_label->show();
        _gamemode_label->show();
        _options_label->show();
        _popup_label->hide();
        _popup_window->hide();
        cout << "changed state to MAINMENU" << endl;
        break;
    case st_gameinit:
        _gamemode_dropdown->hide();
        _size_spinbox->hide();
        _btn_start->hide();
        _btn_restart->hide();
        _btn_backtomenu->hide();
        _grid->show();
        _title_label->hide();
        _size_label->hide();
        _gamemode_label->hide();
        _options_label->hide();
        _popup_label->hide();
        _popup_window->hide();

        _gamemaster->new_game(
                              _size_spinbox->get_value(),
                              (_gamemode_dropdown->get_value() == "Player vs Computer" )
                            );

        change_state_to(st_ingame);
        cout << "changed state to GAMEINIT" << endl;
        break;
    case st_ingame:
        cout << "changed state to INGAME" << endl;
        break;
    case st_gameover:
        _gamemode_dropdown->hide();
        _size_spinbox->hide();
        _btn_start->hide();
        _btn_restart->show();
        _btn_backtomenu->show();
        _grid->hide();
        _title_label->hide();
        _size_label->hide();
        _gamemode_label->hide();
        _options_label->hide();
        _popup_label->show();

        _popup_window->set_color(_bg_color_list[_gamemaster->get_moves()%_bg_color_list.size()]);
        _popup_window->show();
        cout << "changed state to GAMEOVER" << endl;
        break;
    }
}

void Amoba::btn_handler(string btn)
{
    //cout << "button pressed. id = " << btn << endl;
    if (btn == "Start")
    {
        change_state_to(st_gameinit);
    }
    else if (btn == "New Game")
    {
        change_state_to(st_gameinit);
    }
    else if (btn == "Back to Menu")
    {
        change_state_to(st_mainmenu);
    }
}

void Amoba::game_over(char winner)
{
    if (winner == 'x')
    {
        _popup_label->set_text("X wins!");
    }
    else if (winner == 'o')
    {
        _popup_label->set_text("O wins!");
    }
    else
    {
        _popup_label->set_text("Tie!");
    }
    change_state_to(st_gameover);
}
