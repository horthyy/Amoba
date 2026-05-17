#ifndef AMOBA_HPP
#define AMOBA_HPP

#include "application.hpp"
#include "gamemaster.hpp"
#include <vector>


/*
==============================
Amõba játék megvalósítása:
- GUI: kirajzolást az 'Amoba' class végzi, ami egy 'Application' leszármazott.
- Játék: a játékszabályokat a 'GameMaster' singleton class vezérli, ami 'Amoba' mezõjeként szerepel.

Player1 jele X, Player2 jele O.
Az nyer, aki először rak le a saját szimbólumából 5 darabot egymás mellé sorban vagy oszlopban.
Ha betelik a pálya, és senki nem nyert az utolsó lépésben sem, akkor döntetlen a játék.

==============================
*/

class Amoba : public Application
{
public:
    Amoba();
    virtual ~Amoba();

    virtual void action(genv::event);

    void update_grid();
    void test_move(int,int);

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

    // game-specific tiling grid widget
    AmobaGrid *_grid;


};

#endif // AMOBA_HPP
