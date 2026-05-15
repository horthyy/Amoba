#include "application.hpp"
#include "gamemaster.hpp"

#include <iostream>

/*
Amõba játék megvalósítása:
- GUI: kirajzolást az 'Amoba' class végzi, ami egy 'Application' leszármazott.
- Játék: a játék logikáját a 'GameMaster' singleton class vezérli, ami 'Amoba' mezõjeként szerepel ('_gamemaster').

A GUI vezérlés csak a Widgetek kirajzolását és a billentyû/egér eseményeket kezeli,
esetleg továbbítja '_gamemaster'-nek.


*/

using namespace std;

class Amoba : public Application
{
public:
    Amoba(int width, int height, string title) : Application(width, height, title)
    {
        _gamemaster = new GameMaster(this);

        _gamemode_dropdown = new Dropdown(this, 300, 200, 250, 50, vector<string> {"Player1 vs Player2", "Player vs Computer"}, 2);
        _size_spinbox = new Spinbox(this, 20, 20, 120, 40, 20, 15, 30);

        _start_btn = new Button(this, 300, 300, 100, 40, "Start", [](){});
        _restart_btn = new Button(this, 300, 400, 100, 40, "New Game", [](){});
        _backtomenu_btn = new Button(this, 300, 500, 100, 40, "Back to Menu", [](){});


    }

    void viccces() {cout << "gelbi" << endl;}

protected:
    // statictext, gombok meg egyeb cuccok mert MINDENT widgetekkel kell kirajzolni!!!!

    GameMaster *_gamemaster;

    // option selector widgets
    Dropdown *_gamemode_dropdown;
    Spinbox *_size_spinbox;

    // menu buttons
    Button  *_start_btn,      // main menu, new game
            *_restart_btn, // game over menu, new game
            *_backtomenu_btn;    // game over menu, go back to main menu


    // ------ Static Gui Elements ------
    // text elements
    StaticText *_title_txt, // main menu, game title
               *_spinbox_txt, // main menu, label above '_size_spinbox'
               *_dropdown_txt; // main menu, label above '_gamemode_dropdown'
    // background stuff
    Rect2 *_title_bg, // main menu, background box
          *_gameover_bg; // game over popup window background


};

int main()
{
    Amoba my_app(740,740,"Amoba");
    my_app.event_loop();
    return 0;
}
